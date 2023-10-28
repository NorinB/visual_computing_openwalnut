//---------------------------------------------------------------------------
//
// Project: OpenWalnut ( http://www.openwalnut.org )
//
// Copyright 2009-2020 OpenWalnut Community, BSV@Uni-Leipzig and CNCF@MPI-CBS
// For more information see http://www.openwalnut.org/copying
//
// This file is part of OpenWalnut.
//
// OpenWalnut is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OpenWalnut is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenWalnut. If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------------------------

#include <algorithm>
#include <memory>
#include <string>
#include <utility>

#include <osg/LineWidth>
#include <osg/MatrixTransform>
#include <osg/Vec3>

#include "WMNavigationSlices.h"
#include "WMNavigationSlices.xpm"
#include "core/common/WPropertyHelper.h"
#include "core/common/math/WMath.h"
#include "core/graphicsEngine/WGEColormapping.h"
#include "core/graphicsEngine/WGEGeodeUtils.h"
#include "core/graphicsEngine/WGEUtils.h"
#include "core/graphicsEngine/WGraphicsEngine.h"
#include "core/graphicsEngine/WPickHandler.h"
#include "core/graphicsEngine/WPickHandler3D.h"
#include "core/graphicsEngine/callbacks/WGELinearTranslationCallback.h"
#include "core/graphicsEngine/callbacks/WGENodeMaskCallback.h"
#include "core/graphicsEngine/callbacks/WGEPropertyUniformCallback.h"
#include "core/graphicsEngine/callbacks/WGEShaderAnimationCallback.h"
#include "core/graphicsEngine/shaders/WGEPropertyUniform.h"
#include "core/graphicsEngine/shaders/WGEShader.h"
#include "core/graphicsEngine/shaders/WGEShaderDefineOptions.h"
#include "core/graphicsEngine/shaders/WGEShaderPropertyDefineOptions.h"
#include "core/kernel/WKernel.h"
#include "core/kernel/WSelectionManager.h"

// This line is needed by the module loader to actually find your module. You need to add this to your module too. Do NOT add a ";" here.
W_LOADABLE_MODULE( WMNavigationSlices )

WMNavigationSlices::WMNavigationSlices():
    WModule()
{
}

WMNavigationSlices::~WMNavigationSlices()
{
    // Cleanup!
}

std::shared_ptr< WModule > WMNavigationSlices::factory() const
{
    return std::shared_ptr< WModule >( new WMNavigationSlices() );
}

const char** WMNavigationSlices::getXPMIcon() const
{
    return WMNavigationSlices_xpm;
}

const std::string WMNavigationSlices::getName() const
{
    return "Navigation Slices";
}

const std::string WMNavigationSlices::getDescription() const
{
    return "This module provides slices, orthogonally oriented in the OpenWalnut coordinate system. They allow the fast and easy exploration of "
           "three-dimensional datasets.";
}

void WMNavigationSlices::connectors()
{
    // call WModule's initialization
    WModule::connectors();
}

void WMNavigationSlices::properties()
{
    m_noTransparency  = m_properties->addProperty( "No transparency", "If checked, transparency is not used. This will show the complete slices.",
                                                   false );

    m_sliceGroup      = m_properties->addPropertyGroup( "Slices",  "Slice Options." );

    // enable slices
    // Flags denoting whether the glyphs should be shown on the specific slice
    m_showonX = m_sliceGroup->addProperty( WKernel::getRunningKernel()->getSelectionManager()->getPropSagittalShow() );
    m_showonY = m_sliceGroup->addProperty( WKernel::getRunningKernel()->getSelectionManager()->getPropCoronalShow() );
    m_showonZ = m_sliceGroup->addProperty( WKernel::getRunningKernel()->getSelectionManager()->getPropAxialShow() );

    // The slice positions.
    m_xPos    = m_sliceGroup->addProperty( WKernel::getRunningKernel()->getSelectionManager()->getPropSagittalPos() );
    m_yPos    = m_sliceGroup->addProperty( WKernel::getRunningKernel()->getSelectionManager()->getPropCoronalPos() );
    m_zPos    = m_sliceGroup->addProperty( WKernel::getRunningKernel()->getSelectionManager()->getPropAxialPos() );

    // call WModule's initialization
    WModule::properties();
}

void WMNavigationSlices::initOSG()
{
    // remove the old slices
    m_output->clear();
    m_axialOutput->clear();
    m_sagittalOutput->clear();
    m_coronalOutput->clear();

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Property Setup
    ///////////////////////////////////////////////////////////////////////////////////////////////

    // no colormaps -> no slices
    bool empty = !WGEColormapping::instance()->size();
    if( empty )
    {
        // hide the slider properties.
        m_xPos->setHidden();
        m_yPos->setHidden();
        m_zPos->setHidden();
        return;
    }

    // grab the current bounding box
    WBoundingBox bb = WGEColormapping::instance()->getBoundingBox();
    WVector3d minV = bb.getMin();
    WVector3d maxV = bb.getMax();
    WVector3d sizes = ( maxV - minV );
    WVector3d midBB = minV + ( sizes * 0.5 );

    // update the properties
    m_xPos->setMin( minV[0] );
    m_xPos->setMax( maxV[0] );
    m_yPos->setMin( minV[1] );
    m_yPos->setMax( maxV[1] );
    m_zPos->setMin( minV[2] );
    m_zPos->setMax( maxV[2] );
    // un-hide the slider properties.
    m_xPos->setHidden( false );
    m_yPos->setHidden( false );
    m_zPos->setHidden( false );

    // always update slice positions if they happen to be outside the bounding box (i.e. after shrinking the box)
    m_xPos->setRecommendedValue( midBB[0] );
    m_yPos->setRecommendedValue( midBB[1] );
    m_zPos->setRecommendedValue( midBB[2] );

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Navigation View Setup
    ///////////////////////////////////////////////////////////////////////////////////////////////

    double maxSizeInv = 1.0 / std::max( sizes[0], std::max( sizes[1], sizes[2] ) );
    m_axialOutput->setMatrix(
        osg::Matrixd::translate( -midBB[0], -midBB[1], -midBB[2] ) *
        osg::Matrixd::scale( maxSizeInv, maxSizeInv, maxSizeInv ) *
        osg::Matrixd::translate( 0.0, 0.0, -0.5 )
    );

    m_coronalOutput->setMatrix(
        osg::Matrixd::translate( -midBB[0], -midBB[1], -midBB[2] ) *
        osg::Matrixd::scale( maxSizeInv, maxSizeInv, maxSizeInv ) *
        osg::Matrixd::rotate( -0.5 * pi(), 1.0, 0.0 , 0.0 ) *
        osg::Matrixd::translate( 0.0, 0.0, -0.5 )
    );

    m_sagittalOutput->setMatrix(
        osg::Matrixd::translate( -midBB[0], -midBB[1], -midBB[2] ) *
        osg::Matrixd::scale( maxSizeInv, maxSizeInv, maxSizeInv ) *
        osg::Matrixd::rotate( -0.5 * pi(), 1.0, 0.0 , 0.0 ) *
        osg::Matrixd::rotate( 0.5 * pi(), 0.0, 1.0 , 0.0 ) *
        osg::Matrixd::translate( 0.0, 0.0, -0.5 )
    );

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Slice Setup
    ///////////////////////////////////////////////////////////////////////////////////////////////

    // create a new geode containing the slices

    // X Slice
    osg::ref_ptr< osg::Node > xSlice = wge::genFinitePlane( minV, osg::Vec3( 0.0, sizes[1], 0.0 ),
                                                                  osg::Vec3( 0.0, 0.0, sizes[2] ) );
    xSlice->setName( "Sagittal Slice" );
    osg::Uniform* xSliceUniform = new osg::Uniform( "u_WorldTransform", osg::Matrixf::identity() );
    xSlice->getOrCreateStateSet()->addUniform( xSliceUniform );

    // Y Slice
    osg::ref_ptr< osg::Node > ySlice = wge::genFinitePlane( minV, osg::Vec3( sizes[0], 0.0, 0.0 ),
                                                                  osg::Vec3( 0.0, 0.0, sizes[2] ) );
    ySlice->setName( "Coronal Slice" );
    osg::Uniform* ySliceUniform = new osg::Uniform( "u_WorldTransform", osg::Matrixf::identity() );
    ySlice->getOrCreateStateSet()->addUniform( ySliceUniform );

    // Z Slice
    osg::ref_ptr< osg::Node > zSlice = wge::genFinitePlane( minV, osg::Vec3( sizes[0], 0.0, 0.0 ),
                                                                  osg::Vec3( 0.0, sizes[1], 0.0 ) );
    zSlice->setName( "Axial Slice" );
    osg::Uniform* zSliceUniform = new osg::Uniform( "u_WorldTransform", osg::Matrixf::identity() );
    zSlice->getOrCreateStateSet()->addUniform( zSliceUniform );

    // disable culling.
    // NOTE: Somehow, this is ignore by OSG. If you know why: tell Sebastian Eichelbaum please
    xSlice->setCullingActive( false );
    ySlice->setCullingActive( false );
    zSlice->setCullingActive( false );

    // Each slice is child of an transformation node
    // These nodes are for the main view
    // Seperate nodes are important to allow hiding of slices in the main view while keeping those in nav views
    osg::ref_ptr< osg::MatrixTransform > matMainViewX = new osg::MatrixTransform();
    matMainViewX->addChild( xSlice );
    osg::ref_ptr< osg::MatrixTransform > matMainViewY = new osg::MatrixTransform();
    matMainViewY->addChild( ySlice );
    osg::ref_ptr< osg::MatrixTransform > matMainViewZ = new osg::MatrixTransform();
    matMainViewZ->addChild( zSlice );

    // Each slice is child of an transformation node
    // These nodes are for the navigation views
    // Seperate nodes are important to allow hiding of slice in the main view while keeping those in nav views
    osg::ref_ptr< osg::MatrixTransform > matNavViewX = new osg::MatrixTransform();
    matNavViewX->addChild( xSlice );
    osg::ref_ptr< osg::MatrixTransform > matNavViewY = new osg::MatrixTransform();
    matNavViewY->addChild( ySlice );
    osg::ref_ptr< osg::MatrixTransform > matNavViewZ = new osg::MatrixTransform();
    matNavViewZ->addChild( zSlice );

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Callback Setup
    ///////////////////////////////////////////////////////////////////////////////////////////////

    // Control transformation node by properties. We use an additional uniform here to provide the shader the transformation matrix used to
    // translate the slice.
    matMainViewX->addUpdateCallback( new WGELinearTranslationCallback< WPropDouble >( osg::Vec3( 1.0, 0.0, 0.0 ), m_xPos, xSliceUniform ) );
    matMainViewY->addUpdateCallback( new WGELinearTranslationCallback< WPropDouble >( osg::Vec3( 0.0, 1.0, 0.0 ), m_yPos, ySliceUniform ) );
    matMainViewZ->addUpdateCallback( new WGELinearTranslationCallback< WPropDouble >( osg::Vec3( 0.0, 0.0, 1.0 ), m_zPos, zSliceUniform ) );
    matNavViewX->addUpdateCallback( new WGELinearTranslationCallback< WPropDouble >( osg::Vec3( 1.0, 0.0, 0.0 ), m_xPos, xSliceUniform ) );
    matNavViewY->addUpdateCallback( new WGELinearTranslationCallback< WPropDouble >( osg::Vec3( 0.0, 1.0, 0.0 ), m_yPos, ySliceUniform ) );
    matNavViewZ->addUpdateCallback( new WGELinearTranslationCallback< WPropDouble >( osg::Vec3( 0.0, 0.0, 1.0 ), m_zPos, zSliceUniform ) );

    // set callbacks for en-/disabling the nodes
    matMainViewX->addUpdateCallback( new WGENodeMaskCallback( m_showonX ) );
    matMainViewY->addUpdateCallback( new WGENodeMaskCallback( m_showonY ) );
    matMainViewZ->addUpdateCallback( new WGENodeMaskCallback( m_showonZ ) );

    // set the pick callbacks for each slice
    m_xSlicePicker = PickCallback::SPtr( new PickCallback( xSlice, m_xPos ) );
    m_ySlicePicker = PickCallback::SPtr( new PickCallback( ySlice, m_yPos, true ) );
    m_zSlicePicker = PickCallback::SPtr( new PickCallback( zSlice, m_zPos ) );

    // transparency property
    osg::ref_ptr< osg::Uniform > transparencyUniform = new osg::Uniform( "u_noTransparency", false );
    transparencyUniform->setUpdateCallback( new WGEPropertyUniformCallback< WPropBool >( m_noTransparency ) );

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Done
    ///////////////////////////////////////////////////////////////////////////////////////////////

    osg::ref_ptr< osg::StateSet > state = m_output->getOrCreateStateSet();
    state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

    // we want some nice animations: add timer
    osg::ref_ptr< osg::Uniform > animationUniform = new osg::Uniform( "u_timer", 0 );
    state->addUniform( animationUniform );
    animationUniform->setUpdateCallback( new WGEShaderAnimationCallback() );

    // transparency property
    state->addUniform( transparencyUniform );
    m_axialOutput->getOrCreateStateSet()->addUniform( transparencyUniform );
    m_sagittalOutput->getOrCreateStateSet()->addUniform( transparencyUniform );
    m_coronalOutput->getOrCreateStateSet()->addUniform( transparencyUniform );

    // add the transformation nodes to the output group
    m_output->insert( matMainViewX );
    m_output->insert( matMainViewY );
    m_output->insert( matMainViewZ );

    // add proxy
    m_output->insert( wge::generateCullProxy( bb ) );

    m_output->dirtyBound();

    m_axialOutput->insert( matNavViewZ );
    m_sagittalOutput->insert( matNavViewX );
    m_coronalOutput->insert( matNavViewY );
}

WMNavigationSlices::PickCallback::PickCallback( osg::ref_ptr< osg::Node > node, WPropDouble property, bool negateDirection ):
    m_node( node ),
    m_property( property ),
    m_pickUniform( new osg::Uniform( "u_picked", 0.0f ) ),
    m_dir( negateDirection ? -1.0 : 1.0 )
{
    std::shared_ptr< WGraphicsEngine > ge = WGraphicsEngine::getGraphicsEngine();
    std::shared_ptr< WGEViewer > viewer = ge->getViewerByName( "Main View" );
    m_camera = viewer->getCamera();
    m_pickConnection = viewer->getPickHandler()->getPickSignal()->connect( boost::bind( &WMNavigationSlices::PickCallback::pick,
                                                                                        this,
                                                                                        boost::placeholders::_1 ) );

    m_pickConnection3D = viewer->getPickHandler3D()->getPickSignal()->connect( boost::bind( &WMNavigationSlices::PickCallback::pick3D,
                                                                                            this,
                                                                                            boost::placeholders::_1 ) );
    node->getOrCreateStateSet()->addUniform( m_pickUniform );
}

void WMNavigationSlices::PickCallback::pick3D( std::pair< WPickInfo3D, WPickInfo3D > pickInfo )
{
    if( pickInfo.first.getButtons() & WPickInfo3D::TRIGGER )
    {
        if( pickInfo.first.getName() == m_node->getName() )
        {
            WVector3d normal = pickInfo.first.getPickNormal();
            // dragging was initialized earlier
            if( m_isPicked3D )
            {
                osg::Matrixd sceneMatrix = osg::Matrixd::inverse( m_node->getWorldMatrices().at( 1 ) );

                osg::Vec3 moveDirWorld = ( pickInfo.first.getPosition() * sceneMatrix ) - ( m_oldPickInfo3D.first.getPosition() * sceneMatrix );
                float diff = moveDirWorld * static_cast< osg::Vec3 >( normal );

                m_property->set( m_property->get() + m_dir * diff );
            }
            // this might have initialized dragging. Keep track of old position
            m_isPicked3D = true;
            m_pickUniform->set( 1.0f );
        }
        else    // someone else got picked.
        {
            m_isPicked3D = false;
            m_pickUniform->set( 0.0f );
        }
    }
    else if( m_isPicked3D )
    {
        m_isPicked3D = false;
        m_pickUniform->set( 0.0f );
    }
    m_oldPickInfo3D = pickInfo;
}

void WMNavigationSlices::PickCallback::pick( WPickInfo pickInfo )
{
    if( pickInfo.getName() == m_node->getName() )
    {
        WVector3d normal = pickInfo.getPickNormal();
        WVector2d newPixelPos = pickInfo.getPickPixel();
        // dragging was initialized earlier
        if( m_isPicked )
        {
            osg::Vec3 startPosScreen( m_oldPixelPosition[ 0 ], m_oldPixelPosition[ 1 ], 0.0 );
            osg::Vec3 endPosScreen( newPixelPos[ 0 ], newPixelPos[ 1 ], 0.0 );

            osg::Vec3 startPosWorld = wge::unprojectFromScreen( startPosScreen, m_camera );
            osg::Vec3 endPosWorld = wge::unprojectFromScreen( endPosScreen, m_camera );

            osg::Vec3 moveDirWorld = endPosWorld - startPosWorld;
            float diff = moveDirWorld * static_cast< osg::Vec3 >( normal );

            m_property->set( m_property->get() + m_dir * diff );
        }
        // this might have initialized dragging. Keep track of old position
        m_oldPixelPosition = newPixelPos;
        m_isPicked = true;
        m_pickUniform->set( 1.0f );
    }
    else    // someone else got picked.
    {
        m_isPicked = false;
        m_pickUniform->set( 0.0f );
    }
}

void WMNavigationSlices::moduleMain()
{
    // get notified about data changes
    m_moduleState.setResetable( true, true );

    // done.
    ready();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Slices Setup
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    // create the root node for all the geometry
    m_output = osg::ref_ptr< WGEManagedGroupNode > ( new WGEManagedGroupNode( m_active ) );

    // create the roots for the nav-views
    m_sagittalOutput = osg::ref_ptr< WGEGroupNode > ( new WGEGroupNode() );
    m_coronalOutput = osg::ref_ptr< WGEGroupNode > ( new WGEGroupNode() );
    m_axialOutput = osg::ref_ptr< WGEGroupNode > ( new WGEGroupNode() );

    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->insert( m_output );

    // add for side-views
    std::shared_ptr< WGEViewer > viewer = WKernel::getRunningKernel()->getGraphicsEngine()->getViewerByName( "Axial View" );
    if( viewer )
    {
        viewer->getScene()->insert( m_axialOutput );
    }
    viewer = WKernel::getRunningKernel()->getGraphicsEngine()->getViewerByName( "Coronal View" );
    if( viewer )
    {
        viewer->getScene()->insert( m_coronalOutput );
    }
    viewer = WKernel::getRunningKernel()->getGraphicsEngine()->getViewerByName( "Sagittal View" );
    if( viewer )
    {
        viewer->getScene()->insert( m_sagittalOutput );
    }

    // disable the pick-coloring for the side views
    m_axialOutput->getOrCreateStateSet()->addUniform( new osg::Uniform( "u_pickColorEnabled", 0.0f ) );
    m_sagittalOutput->getOrCreateStateSet()->addUniform( new osg::Uniform( "u_pickColorEnabled", 0.0f ) );
    m_coronalOutput->getOrCreateStateSet()->addUniform( new osg::Uniform( "u_pickColorEnabled", 0.0f ) );
    m_output->getOrCreateStateSet()->addUniform( new osg::Uniform( "u_pickColorEnabled", 1.0f ) );

    m_output->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
    m_axialOutput->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
    m_sagittalOutput->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
    m_coronalOutput->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );

    // apply colormapping to all the nodes
    osg::ref_ptr< WGEShader > shader = new WGEShader( "WMNavigationSlices", m_localPath );
    WGEColormapping::NodeList nodes;
    nodes.push_back( m_output );
    nodes.push_back( m_axialOutput );
    nodes.push_back( m_sagittalOutput );
    nodes.push_back( m_coronalOutput );
    WGEColormapping::apply( nodes, shader ); // this automatically applies the shader

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Main loop
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    // we need to be informed if the bounding box of the volume containing all the data changes.
    m_moduleState.add( WGEColormapping::instance()->getChangeCondition() );

    // main loop
    while( !m_shutdownFlag() )
    {
        // woke up since the module is requested to finish?
        if( m_shutdownFlag() )
        {
            break;
        }

        // create the slices. This loop is only entered if WGEColormapper was fired or shutdown.
        initOSG();

        // Thats it. Nothing more to do. Slide movement and colormapping is done by the pick handler and WGEColormapper
        debugLog() << "Waiting ...";
        m_moduleState.wait();
    }

    // clean up
    m_xSlicePicker.reset();
    m_ySlicePicker.reset();
    m_zSlicePicker.reset();

    m_xPos->setHidden();
    m_yPos->setHidden();
    m_zPos->setHidden();

    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->remove( m_output );

    viewer = WKernel::getRunningKernel()->getGraphicsEngine()->getViewerByName( "Axial View" );
    if( viewer )
    {
        viewer->getScene()->remove( m_axialOutput );
    }
    viewer = WKernel::getRunningKernel()->getGraphicsEngine()->getViewerByName( "Coronal View" );
    if( viewer )
    {
        viewer->getScene()->remove( m_coronalOutput );
    }
    viewer = WKernel::getRunningKernel()->getGraphicsEngine()->getViewerByName( "Sagittal View" );
    if( viewer )
    {
        viewer->getScene()->remove( m_sagittalOutput );
    }
}
