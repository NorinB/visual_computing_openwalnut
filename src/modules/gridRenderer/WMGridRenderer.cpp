//---------------------------------------------------------------------------
//
// Project: OpenWalnut ( http://www.openwalnut.org )
//
// Copyright 2009 OpenWalnut Community, BSV@Uni-Leipzig and CNCF@MPI-CBS
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

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgText/Text>

#include "WMGridRenderer.h"
#include "WMGridRenderer.xpm"
#include "WMGridRenderer_boundary.xpm"
#include "WMGridRenderer_grid.xpm"
#include "WMGridRenderer_label.xpm"
#include "core/common/WAssert.h"
#include "core/common/WBoundingBox.h"
#include "core/common/WStringUtils.h"
#include "core/common/math/linearAlgebra/WVectorFixed.h"
#include "core/dataHandler/WDataSetFibers.h"
#include "core/dataHandler/WDataSetPoints.h"
#include "core/dataHandler/WDataSetSingle.h"
#include "core/dataHandler/WGridRegular3D.h"
#include "core/graphicsEngine/WGEGeodeUtils.h"
#include "core/graphicsEngine/callbacks/WGENodeMaskCallback.h"
#include "core/kernel/WKernel.h"

// This line is needed by the module loader to actually find your module.
W_LOADABLE_MODULE( WMGridRenderer )

WMGridRenderer::WMGridRenderer():
    WModule(),
    m_recompute( std::shared_ptr< WCondition >( new WCondition() ) )
{
    // WARNING: initializing connectors inside the constructor will lead to an exception.
    // Implement WModule::initializeConnectors instead.
}

WMGridRenderer::~WMGridRenderer()
{
    // cleanup
    removeConnectors();
}

std::shared_ptr< WModule > WMGridRenderer::factory() const
{
    return std::shared_ptr< WModule >( new WMGridRenderer() );
}

const char** WMGridRenderer::getXPMIcon() const
{
    return WMGridRenderer_xpm;
}

const std::string WMGridRenderer::getName() const
{
    return "Grid Renderer";
}

const std::string WMGridRenderer::getDescription() const
{
    return "Shows the bounding box and grid of a data set.";
}

void WMGridRenderer::moduleMain()
{
    // use the m_input "data changed" flag
    m_moduleState.setResetable( true, true );
    m_moduleState.add( m_input->getDataChangedCondition() );
    m_moduleState.add( m_recompute );

    m_shader = new WGEShader( "WMGridRenderer", m_localPath );

    // signal ready state
    ready();

    // loop until the module container requests the module to quit
    while( !m_shutdownFlag() )
    {
        debugLog() << "Waiting for data ...";
        m_moduleState.wait();

        WDataSet::SPtr dataSet = m_input->getData();
        bool dataValid = ( dataSet != NULL );
        bool dataChanged = ( dataSet != m_dataSetOld );
        m_dataSetOld = dataSet;

        if( !dataValid )
        {
            // OK, the output has not yet sent data
            // NOTE: see comment at the end of this while loop for m_moduleState
            WGraphicsEngine::getGraphicsEngine()->getScene()->remove( m_gridNode );
            m_gridNode = NULL;
            continue;
        }

        // do nothing if these are still the same data
        if( !dataChanged )
        {
            continue;
        }

        m_infoProperties->removeProperty( currentDataInfoProperties );
        currentDataInfoProperties = dataSet->getInformationProperties(); // update properties
        m_infoProperties->addProperty( currentDataInfoProperties );

        // the grid to show
        WGridRegular3D::SPtr regGrid;

        // is this a DS with a regular grid?
        WDataSetSingle::SPtr dsSingle = std::dynamic_pointer_cast< WDataSetSingle >( dataSet );
        if( dsSingle )
        {
            regGrid = std::dynamic_pointer_cast< WGridRegular3D >( dsSingle->getGrid() );
        }

        // is this a fiber dataset?
        WDataSetFibers::SPtr dsFibers = std::dynamic_pointer_cast< WDataSetFibers >( dataSet );
        if( dsFibers )
        {
            debugLog() << "Fiber Data.";

            WBoundingBox bb = dsFibers->getBoundingBox();
            // this basically is a fake but we need a grid for WGEGridNode. So we construct one using the BBox
            WGridTransformOrtho gridTransform( bb.xMax() - bb.xMin(), bb.yMax() - bb.yMin(), bb.zMax() - bb.zMin() );
            gridTransform.translate( WVector3d( bb.xMin(), bb.yMin(), bb.zMin() ) );
            regGrid = WGridRegular3D::SPtr( new WGridRegular3D( 2, 2, 2, gridTransform ) );
        }

        // is this a point dataset?
        WDataSetPoints::SPtr dsPoints = std::dynamic_pointer_cast< WDataSetPoints >( dataSet );
        if( dsPoints )
        {
            debugLog() << "Points Data.";

            WBoundingBox bb = dsPoints->getBoundingBox();

            // this basically is a fake but we need a grid for WGEGridNode. So we construct one using the BBox
            const double makeFakeNonZero = 0.000001;
            WGridTransformOrtho gridTransform( bb.xMax() - bb.xMin() + makeFakeNonZero,
                                               bb.yMax() - bb.yMin() + makeFakeNonZero,
                                               bb.zMax() - bb.zMin() + makeFakeNonZero );
            gridTransform.translate( WVector3d( bb.xMin(), bb.yMin(), bb.zMin() ) );
            regGrid = WGridRegular3D::SPtr( new WGridRegular3D( 2, 2, 2, gridTransform ) );
        }

        // create the new grid node if it not exists
        if( !m_gridNode && regGrid )
        {
            debugLog() << "Creating grid geode.";
            m_gridNode = new WGEGridNode( regGrid );
            m_gridNode->addUpdateCallback( new WGENodeMaskCallback( m_active ) );
            m_shader->apply( m_gridNode );
            WGraphicsEngine::getGraphicsEngine()->getScene()->insert( m_gridNode );
        }
        else if( m_gridNode && !regGrid )
        {
            debugLog() << "Removing grid geode.";
            // there is a grid node which needs to be removed as we do NOT have a valid regular grid.
            WGraphicsEngine::getGraphicsEngine()->getScene()->remove( m_gridNode );
            m_gridNode = NULL;
        }

        if( m_gridNode )
        {
            m_gridNode->setBBoxColor( *m_bboxColor );
            m_gridNode->setGridColor( *m_gridColor );
            m_gridNode->setGridLineWidth( m_gridLineWidth->get() );
            m_gridNode->setBoxLineWidth( m_boxLineWidth->get() );
            updateNode( m_mode );
            m_gridNode->setGrid( regGrid );
        }
    }

    WGraphicsEngine::getGraphicsEngine()->getScene()->remove( m_gridNode );
}

void WMGridRenderer::connectors()
{
    // initialize connectors
    m_input = std::shared_ptr< WModuleInputData < WDataSet  > >(
        new WModuleInputData< WDataSet >( shared_from_this(),
                                                               "in", "The dataset to show" )
        );

    // add it to the list of connectors. Please note, that a connector NOT added via addConnector will not work as expected.
    addConnector( m_input );

    // call WModules initialization
    WModule::connectors();
}

void WMGridRenderer::properties()
{
    WPropertyBase::PropertyChangeNotifierType  notifier = boost::bind( &WMGridRenderer::updateNode, this, boost::placeholders::_1 );

    m_bboxColor = m_properties->addProperty( "Bounding box color", "The color of the bounding box.", WColor( 0.3, 0.3, 0.3, 1.0 ), notifier );
    m_boxLineWidth = m_properties->addProperty( "Bounding box line width", "The width of the grid lines.", 4, notifier );
    m_boxLineWidth->setMin( 1 );
    m_boxLineWidth->setMax( 10 );

    m_gridColor = m_properties->addProperty( "Grid color", "The color of the grid.", WColor( 0.1, 0.1, 0.1, 1.0 ), notifier );
    m_gridLineWidth = m_properties->addProperty( "Grid line width", "The width of the grid lines.", 1, notifier );
    m_gridLineWidth->setMin( 1 );
    m_gridLineWidth->setMax( 10 );

    m_possibleModes = WItemSelection::SPtr( new WItemSelection() );
    m_possibleModes->addItem( "Labels", "Show the boundary labels.", WMGridRenderer_label_xpm );          // NOTE: you can add XPM images here.
    m_possibleModes->addItem( "Bounding box", "Show the bounding box.", WMGridRenderer_boundary_xpm );
    m_possibleModes->addItem( "Grid", "Show the inner grid.",  WMGridRenderer_grid_xpm );

    // selecting all at once might be a bad idea since the grid rendering can be very very slow. So, by default, only show bbox and labels.
    WItemSelector sel = m_possibleModes->getSelectorFirst();
    m_mode = m_properties->addProperty( "Mode", "What should be rendered.",  sel.newSelector( 1 ), notifier );
    WPropertyHelper::PC_NOTEMPTY::addTo( m_mode );

    WModule::properties();
}

void WMGridRenderer::updateNode( WPropertyBase::SPtr property )
{
    // only update if there is a grid node
    if( !m_gridNode )
    {
        return;
    }

    // color of bbox changed
    if( property == m_bboxColor )
    {
        m_gridNode->setBBoxColor( *m_bboxColor );
    }

    // color of grid changed
    if( property == m_gridColor )
    {
        m_gridNode->setGridColor( *m_gridColor );
    }

    if( property == m_gridLineWidth )
    {
        m_gridNode->setGridLineWidth( m_gridLineWidth->get() );
    }

    if( property == m_boxLineWidth )
    {
        m_gridNode->setBoxLineWidth( m_boxLineWidth->get() );
    }

    // mode changed
    if( property == m_mode )
    {
        WItemSelector s = m_mode->get( true );

        bool labels = false;
        bool bbox = false;
        bool grid = false;

        // The multi property allows the selection of several items. So, iteration needs to be done here:
        for( size_t i = 0; i < s.size(); ++i )
        {
            size_t idx = s.getItemIndexOfSelected( i );

            // check what was selected
            labels = labels || ( idx == 0 );
            bbox = bbox || ( idx == 1 );
            grid = grid || ( idx == 2 );
        }

        m_gridNode->setEnableLabels( labels );
        m_gridNode->setEnableGrid( grid );
        m_gridNode->setEnableBBox( bbox );
    }
}
