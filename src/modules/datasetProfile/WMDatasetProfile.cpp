//---------------------------------------------------------------------------
//
// Project: OpenWalnut ( http://www.openwalnut.org )
//
// Copyright 2009, 2017 OpenWalnut Community, BSV@Uni-Leipzig and CNCF@MPI-CBS
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

#include <memory>
#include <string>
#include <vector>

#include <osg/LightModel>
#include <osgGA/StateSetManipulator>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgWidget/Util> //NOLINT
#include <osgWidget/ViewerEventHandlers> //NOLINT
#include <osgWidget/WindowManager> //NOLINT

#include "WMDatasetProfile.h"
#include "WMDatasetProfile.xpm"
#include "core/kernel/WKernel.h"
#include "core/kernel/WSelectionManager.h"

// This line is needed by the module loader to actually find your module. Do not remove. Do NOT add a ";" here.
W_LOADABLE_MODULE( WMDatasetProfile )

WMDatasetProfile::WMDatasetProfile():
    WModule(),
    m_dirty( true )
{
}

WMDatasetProfile::~WMDatasetProfile()
{
    // Cleanup!
}

std::shared_ptr< WModule > WMDatasetProfile::factory() const
{
    return std::shared_ptr< WModule >( new WMDatasetProfile() );
}

const char** WMDatasetProfile::getXPMIcon() const
{
    return WMDatasetProfile_xpm;
}
const std::string WMDatasetProfile::getName() const
{
    return "Dataset Profile";
}

const std::string WMDatasetProfile::getDescription() const
{
    return "Show values along a 3D profile through the dataset as a graph.";
}

void WMDatasetProfile::connectors()
{
    // the input dataset is just used as source for resolurtion and transformation matrix
    m_input = std::shared_ptr< WModuleInputData < WDataSetScalar  > >(
        new WModuleInputData< WDataSetScalar >( shared_from_this(), "in", "The input dataset." ) );
    addConnector( m_input );

    WModule::connectors();
}

void WMDatasetProfile::properties()
{
    m_propCondition = std::shared_ptr< WCondition >( new WCondition() );

    m_snapSelectionsList = std::shared_ptr< WItemSelection >( new WItemSelection() );
    m_snapSelectionsList->addItem( "Free", "No snapping." );
    m_snapSelectionsList->addItem( "Axial slice", "Snap to axial slice." );
    m_snapSelectionsList->addItem( "Coronal slice", "Snap to coronal slice." );
    m_snapSelectionsList->addItem( "Sagittal slice", "Snap to sagittal slice." );

    m_snapSelection = m_properties->addProperty( "Snap to", "Snap the profile to one of the slices of the Navigation Slices Module.",
            m_snapSelectionsList->getSelectorFirst(), m_propCondition );
    WPropertyHelper::PC_SELECTONLYONE::addTo( m_snapSelection );

    m_propAddKnobTrigger = m_properties->addProperty( "Add knob",
                                                      "Add a segment and a corresponding manipulator knob to profile.",
                                                      WPVBaseTypes::PV_TRIGGER_READY,
                                                      m_propCondition );

    m_graphColor = m_properties->addProperty( "Graph color",
                                              "Color of the curve representing the data profile graph.",
                                              WColor( 0.2, 0.2, 0.2, 1.0 ) );

    m_propLength = m_properties->addProperty( "Length",
                                              "Length of profile segments. Needs to activated by Use Length property",
                                              60.0 );
    m_propLength->setMin( 1 );
    m_propLength->setMax( 500 );
    m_propUseLength = m_properties->addProperty( "Use length", "Apply the value of the Length property.", false );

    m_propInterpolate = m_properties->addProperty( "Interpolate",
                                                   "Use value of voxel closest to sample or interpolate between surrounding values.",
                                                   true );

    m_propNumSamples = m_properties->addProperty( "Number of sample points", "Number of samples along the overall profile.", 100 );
    m_propNumSamples->setMin( 1 );
    m_propNumSamples->setMax( 500 );

    WModule::properties();
}

void WMDatasetProfile::requirements()
{
    // Put the code for your requirements here. See "src/modules/template/" for an extensively documented example.
}

void WMDatasetProfile::moduleMain()
{
    m_moduleState.setResetable( true, true );
    m_moduleState.add( m_input->getDataChangedCondition() );
    m_moduleState.add( m_propCondition );
    m_moduleState.add( m_active->getUpdateCondition() );

    init();

    ready();

    m_dirty = true;

    // wait for a dataset to be connected, most likely an anatomy dataset
    while( !m_shutdownFlag() )
    {
        m_moduleState.wait();

        if( m_shutdownFlag() )
        {
            break;
        }

        std::shared_ptr< WDataSetScalar > newDataSet = m_input->getData();
        bool dataChanged = ( m_dataSet != newDataSet );
        bool dataValid = ( newDataSet != NULL );

        if( dataValid )
        {
            if( dataChanged )
            {
                m_dataSet = newDataSet;
                m_grid = std::dynamic_pointer_cast< WGridRegular3D >( m_dataSet->getGrid() );
            }
        }

        if( m_snapSelection->changed( true ) )
        {
            m_dirty = true;
        }

        if( m_propAddKnobTrigger->changed( true ) )
        {
            WPosition center = WKernel::getRunningKernel()->getSelectionManager()->getCrosshair()->getPosition();
            addKnob( center );

            m_propAddKnobTrigger->set( WPVBaseTypes::PV_TRIGGER_READY, true );
        }


        if( m_propUseLength->changed() || m_propLength->changed() || m_propInterpolate->changed( true ) || m_propNumSamples->changed( true ) )
        {
            m_dirty = true;
        }
    }

    for( size_t i = 0; i < knobs.size(); ++i )
    {
        WGraphicsEngine::getGraphicsEngine()->getScene()->remove( &( *knobs[i] ) );
        knobs[i]->removeROIChangeNotifier( m_changeRoiSignal );
    }

    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->remove( m_rootNode );
}

void WMDatasetProfile::updateCallback()
{
    WPosition center = WKernel::getRunningKernel()->getSelectionManager()->getCrosshair()->getPosition();

    for( size_t i = 0; i < knobs.size(); ++i )
    {
        knobs[i]->setLockX( false );
        knobs[i]->setLockY( false );
        knobs[i]->setLockZ( false );
    }
    switch( m_snapSelection->get( true ).getItemIndexOfSelected( 0 ) )
    {
        case 0:
            break;
        case 1:
            for( size_t i = 0; i < knobs.size(); ++i )
            {
                knobs[i]->setZ( center[2] );
                knobs[i]->setLockZ( true );
            }
            break;
        case 2:
            for( size_t i = 0; i < knobs.size(); ++i )
            {
                knobs[i]->setY( center[1] );
                knobs[i]->setLockY( true );
            }
            break;
        case 3:
            for( size_t i = 0; i < knobs.size(); ++i )
            {
                knobs[i]->setX( center[0] );
                knobs[i]->setLockX( true );
            }
            break;
        default:
            break;
    }

        if( m_propUseLength->get( true ) )
        {
            for( size_t i = 0; i < knobs.size() - 1; ++i )
            {
                WPosition p1 = knobs[i]->getPosition();
                WPosition p2 = knobs[i+1]->getPosition();

                float l = sqrt( ( p1[0] - p2[0] ) * ( p1[0] - p2[0] ) +
                                ( p1[1] - p2[1] ) * ( p1[1] - p2[1] ) +
                                ( p1[2] - p2[2] ) * ( p1[2] - p2[2] ) );

                float mult = m_propLength->get( true ) / l;

                WPosition vec = p2 - p1;

                if( ( fabs( l - static_cast<float>( m_propLength->get( true ) ) ) ) > 0.001 )
                {
                    knobs[i+1]->setPosition( p1 + vec * mult );
                }
            }
        }

    m_dirty = true;
    update();
}

void WMDatasetProfile::setDirty()
{
    m_dirty = true;
}


void WMDatasetProfile::init()
{
    m_rootNode = new WGEManagedGroupNode( m_active );
    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->insert( m_rootNode );
    m_lineGeode = osg::ref_ptr< osg::Geode >( new osg::Geode() );
    m_lineGeode->setName( "_line" );
    m_rootNode->insert( m_lineGeode );

    m_changeRoiSignal
            = std::shared_ptr< boost::function< void() > >( new boost::function< void() >( boost::bind( &WMDatasetProfile::setDirty, this ) ) );

    WPosition center = WKernel::getRunningKernel()->getSelectionManager()->getCrosshair()->getPosition();

    addKnob( WPosition( center[0] + 30, center[1], center[2] ) );
    addKnob( WPosition( center[0] - 30, center[1], center[2] ) );

    osg::ref_ptr<osgViewer::View> viewer = WKernel::getRunningKernel()->getGraphicsEngine()->getViewer()->getView();

    int height = viewer->getCamera()->getViewport()->height();
    int width = viewer->getCamera()->getViewport()->width();

    m_oldViewHeight = height;
    m_oldViewWidth = width;

    m_graphNode = osg::ref_ptr< WGEManagedGroupNode >( new WGEManagedGroupNode( m_active ) );
    m_rootNode->insert( m_graphNode );

    m_wm = new osgWidget::WindowManager( viewer, 0.0f, 0.0f, MASK_2D );

    m_camera = new WGECamera();
    m_camera->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF );

    m_camera->setProjectionMatrix( osg::Matrix::ortho2D( 0.0, width, 0.0f, height ) );
    m_camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
    m_camera->setViewMatrix( osg::Matrix::identity() );
    m_camera->setClearMask( GL_DEPTH_BUFFER_BIT );
    m_camera->setRenderOrder( WGECamera::POST_RENDER );

    m_graphNode->addChild( m_camera );
    m_camera->addChild( m_wm );

    viewer->addEventHandler( new osgWidget::MouseHandler( m_wm ) );
    viewer->addEventHandler( new osgWidget::KeyboardHandler( m_wm ) );
    viewer->addEventHandler( new osgWidget::ResizeHandler( m_wm, m_camera ) );
    viewer->addEventHandler( new osgWidget::CameraSwitchHandler( m_wm, m_camera ) );
    viewer->addEventHandler( new osgViewer::StatsHandler() );
    viewer->addEventHandler( new osgViewer::WindowSizeHandler() );
    viewer->addEventHandler( new osgGA::StateSetManipulator( viewer->getCamera()->getOrCreateStateSet() ) );

    m_wm->resizeAllWindows();

    m_rootNode->addUpdateCallback( new WGEFunctorCallback< osg::Node >( boost::bind( &WMDatasetProfile::updateCallback, this ) ) );
}

void WMDatasetProfile::addKnob( WPosition pos )
{
    osg::ref_ptr<WROISphere> s = osg::ref_ptr<WROISphere>( new WROISphere( pos, 2.5 ) );
    WGraphicsEngine::getGraphicsEngine()->getScene()->addChild( &( *s ) );
    knobs.push_back( s );
    s->addROIChangeNotifier( m_changeRoiSignal );

    for( size_t i = 0; i < knobs.size(); ++i )
    {
        knobs[i]->setColor( osg::Vec4( 0.0, 1.0, 1.0, 1.0 ) );
    }
    knobs[0]->setColor( osg::Vec4( 0.0, 1.0, 0.0, 1.0 ) );
    knobs[knobs.size()- 1]->setColor( osg::Vec4( 1.0, 0.0, 0.0, 1.0 ) );
}

void WMDatasetProfile::update()
{
    m_lineGeode->removeDrawables( 0, 1 );

    if( m_active->get() )
    {
        osg::ref_ptr< osg::Vec3Array > vertices = osg::ref_ptr< osg::Vec3Array >( new osg::Vec3Array );
        osg::ref_ptr< osg::Vec4Array > colors = osg::ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
        osg::ref_ptr< osg::Geometry > geometry = osg::ref_ptr< osg::Geometry >( new osg::Geometry );

        for( size_t i = 0; i < knobs.size(); ++i )
        {
            vertices->push_back( osg::Vec3( knobs[i]->getPosition() ) );
        }

        geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINE_STRIP, 0, vertices->size() ) );
        geometry->setVertexArray( vertices );

        colors->push_back( m_graphColor->get() );
        geometry->setColorArray( colors );
        geometry->setColorBinding( osg::Geometry::BIND_OVERALL );

        // disable light for this geode as lines can't be lit properly
        osg::StateSet* state = m_lineGeode->getOrCreateStateSet();
        state->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );

        m_lineGeode->addDrawable( geometry );

        osg::ref_ptr<osgViewer::View> viewer = WKernel::getRunningKernel()->getGraphicsEngine()->getViewer()->getView();

        int height = viewer->getCamera()->getViewport()->height();
        int width = viewer->getCamera()->getViewport()->width();

        if( ( height != m_oldViewHeight ) || width != m_oldViewWidth || m_active->changed( true ) )
        {
            m_oldViewHeight = height;
            m_oldViewWidth = width;

            m_camera->removeChild( m_graphGridGeode );
            m_graphGridGeode = createGraphGridGeode();
            m_camera->addChild( m_graphGridGeode );
        }

        m_camera->removeChild( m_graphGeode );
        m_graphGeode = createGraphGeode();
        m_camera->addChild( m_graphGeode );

        for( size_t i = 0; i < knobs.size(); ++i )
        {
            knobs[i]->unhide();
        }

        m_dirty = false;
    }
    else
    {
        for( size_t i = 0; i < knobs.size(); ++i )
        {
            knobs[i]->hide();
        }
        m_camera->removeChild( m_graphGridGeode );
        m_camera->removeChild( m_graphGeode );
    }
}

osg::ref_ptr< osg::Geode > WMDatasetProfile::createGraphGridGeode()
{
    osg::ref_ptr< osg::Geode > newGeode = osg::ref_ptr< osg::Geode >( new osg::Geode() );

    osg::ref_ptr< osg::Vec3Array > vertices = osg::ref_ptr< osg::Vec3Array >( new osg::Vec3Array );
    osg::ref_ptr< osg::Vec4Array > colors = osg::ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
    osg::ref_ptr< osg::Geometry > geometry = osg::ref_ptr< osg::Geometry >( new osg::Geometry );

    int step = ( m_oldViewWidth - 20 ) / 10;
    int i;
    for( i = 10; i < m_oldViewWidth; i += step )
    {
        vertices->push_back( osg::Vec3( i, m_oldViewHeight / 2, 0 ) );
        vertices->push_back( osg::Vec3( i, 10, 0 ) );
    }
    i -= step;
    int yStep = ( m_oldViewHeight / 2 - 10 ) / 4;

    vertices->push_back( osg::Vec3( 10, 10, 0 ) );
    vertices->push_back( osg::Vec3( i, 10, 0 ) );

    vertices->push_back( osg::Vec3( 10, yStep, 0 ) );
    vertices->push_back( osg::Vec3( i, yStep, 0 ) );

    vertices->push_back( osg::Vec3( 10, yStep * 2, 0 ) );
    vertices->push_back( osg::Vec3( i, yStep * 2, 0 ) );

    vertices->push_back( osg::Vec3( 10, yStep * 3, 0 ) );
    vertices->push_back( osg::Vec3( i, yStep * 3, 0 ) );

    vertices->push_back( osg::Vec3( 10, m_oldViewHeight / 2, 0 ) );
    vertices->push_back( osg::Vec3( i, m_oldViewHeight / 2, 0 ) );

    vertices->push_back( osg::Vec3( 10, 10, 0 ) );
    vertices->push_back( osg::Vec3( i, 10, 0 ) );


    geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINES, 0, vertices->size() ) );
    geometry->setVertexArray( vertices );

    WColor color( 0.7, 0.7, 0.7, 1.0 );
    colors->push_back( color );
    geometry->setColorArray( colors );
    geometry->setColorBinding( osg::Geometry::BIND_OVERALL );

    // disable light for this geode as lines can't be lit properly
    osg::StateSet* state = newGeode->getOrCreateStateSet();
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );

    newGeode->addDrawable( geometry );

    return newGeode;
}

osg::ref_ptr< osg::Geode > WMDatasetProfile::createGraphGeode()
{
    if( !m_dataSet )
    {
        return osg::ref_ptr< osg::Geode >();
    }

    osg::ref_ptr< osg::Geode > newGeode = osg::ref_ptr< osg::Geode >( new osg::Geode() );

    osg::ref_ptr< osg::Vec3Array > vertices = osg::ref_ptr< osg::Vec3Array >( new osg::Vec3Array );
    osg::ref_ptr< osg::Vec4Array > colors = osg::ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
    osg::ref_ptr< osg::Geometry > geometry = osg::ref_ptr< osg::Geometry >( new osg::Geometry );

    std::vector<float>knobPositions;

    float max = m_dataSet->getValueSet()->getMaximumValue();
    float value;

    float overallLength = 0;
    std::vector<float> segmentLengths;
    for( size_t k = 0; k < knobs.size() - 1 ; ++k )
    {
        WPosition p = ( knobs[k+1]->getPosition() - knobs[k]->getPosition() );
        segmentLengths.push_back( length( p ) );
        overallLength += length( p );
    }

    float x = 12;
    float y;
    for( size_t k = 0; k < knobs.size() - 1 ; ++k )
    {
        float l1 = segmentLengths[k] / overallLength;
        int steps = m_propNumSamples->get() * l1;

        knobPositions.push_back( x );
        WPosition p1 = ( knobs[k+1]->getPosition() - knobs[k]->getPosition() ) / static_cast<float>( steps );

        for( int i = 0; i < steps; ++i )
        {
            if( m_propInterpolate->get() )
            {
                bool success;
                value = m_dataSet->interpolate( knobs[k]->getPosition() + p1 * i, &success );
            }
            else
            {
                value = m_dataSet->getValueAt( m_grid->getVoxelNum( knobs[k]->getPosition() + p1 * i ) );
            }


            x = x + ( m_oldViewWidth /  m_propNumSamples->get() );
            y = 10 + ( value / max * ( m_oldViewHeight - 20 ) / 2 );
            vertices->push_back( osg::Vec3( x, y, 0 ) );
        }
    }
    knobPositions.push_back( x );

    for( size_t j = 0; j < knobPositions.size(); ++j )
    {
        vertices->push_back( osg::Vec3( knobPositions[j], m_oldViewHeight / 2, 0 ) );
        vertices->push_back( osg::Vec3( knobPositions[j], 10, 0 ) );
    }

    geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINE_STRIP, 0, vertices->size() - knobPositions.size() * 2 ) );
    geometry->setVertexArray( vertices );

    geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINES, vertices->size() - ( knobPositions.size() ) * 2,
            ( knobPositions.size() + 1 ) * 2 ) );

    colors->push_back( m_graphColor->get() );
    geometry->setColorArray( colors );
    geometry->setColorBinding( osg::Geometry::BIND_OVERALL );

    // disable light for this geode as lines can't be lit properly
    osg::StateSet* state = newGeode->getOrCreateStateSet();
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );

    newGeode->addDrawable( geometry );

    return newGeode;
}
