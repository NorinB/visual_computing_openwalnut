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

#include <algorithm>
#include <iomanip>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <osg/Depth>
#include <osg/Geode>
#include <osg/Geometry>

#include "WBresenham.h"
#include "WBresenhamDBL.h"
#include "WCenterlineParameterization.h"
#include "WIntegrationParameterization.h"
#include "WMVoxelizer.h"
#include "WRasterAlgorithm.h"
#include "core/common/WColor.h"
#include "core/common/WLogger.h"
#include "core/common/WPropertyHelper.h"
#include "core/common/datastructures/WFiber.h"
#include "core/dataHandler/WDataSetFiberVector.h"
#include "core/dataHandler/WDataSetScalar.h"
#include "core/dataHandler/WGridTransformOrtho.h"
#include "core/dataHandler/WSubject.h"
#include "core/dataHandler/datastructures/WFiberCluster.h"
#include "core/graphicsEngine/WGEColormapping.h"
#include "core/graphicsEngine/WGEGeodeUtils.h"
#include "core/graphicsEngine/WGEGeometryUtils.h"
#include "core/graphicsEngine/WGEManagedGroupNode.h"
#include "core/graphicsEngine/WGEUtils.h"
#include "core/graphicsEngine/postprocessing/WGEPostprocessingNode.h"
#include "core/graphicsEngine/shaders/WGEPropertyUniform.h"
#include "core/graphicsEngine/shaders/WGEShaderDefineOptions.h"
#include "core/graphicsEngine/shaders/WGEShaderPropertyDefine.h"
#include "core/graphicsEngine/shaders/WGEShaderPropertyDefineOptions.h"
#include "core/kernel/WKernel.h"
#include "core/kernel/WModuleInputData.h"

// This line is needed by the module loader to actually find your module.
W_LOADABLE_MODULE( WMVoxelizer )

WMVoxelizer::WMVoxelizer()
    : WModule(),
      m_fullUpdate( new WCondition() )
{
}

WMVoxelizer::~WMVoxelizer()
{
}

std::shared_ptr< WModule > WMVoxelizer::factory() const
{
    return std::shared_ptr< WModule >( new WMVoxelizer() );
}

void WMVoxelizer::properties()
{
    m_antialiased     = m_properties->addProperty( "Antialiasing", "Enable/disable antialiased rasterization of voxels.", true, m_fullUpdate );
    m_voxelsPerUnit   = m_properties->addProperty( "Voxels per Unit", "Specified the number of voxels per unit in the coordinate system. This "
                                                                       "is useful to increase the resolution of the grid", 1.0, m_fullUpdate );

    m_renderingActive = m_properties->addProperty( "Rendering", "Enable/disable rendering of voxels.", false, m_fullUpdate );

    // for selecting the parameterization method
    m_paramAlgoSelections = std::shared_ptr< WItemSelection >( new WItemSelection() );
    m_paramAlgoSelections->addItem( "No Parameterization", "Disable parameterization." );          // NOTE: you can add XPM images here.
    m_paramAlgoSelections->addItem( "By Longest Line", "Use the longest line and parameterize the bundle along it." );
    m_paramAlgoSelections->addItem( "By Centerline", "Use the centerline and parameterize the bundle along it." );
    m_paramAlgoSelections->addItem( "By Integration", "Integrate along the voxelized line." );
    m_parameterAlgo   = m_properties->addProperty( "Parameterization", "Select the parameterization algorithm.",
                                                   m_paramAlgoSelections->getSelectorFirst(), m_fullUpdate );
    WPropertyHelper::PC_SELECTONLYONE::addTo( m_parameterAlgo );
    WPropertyHelper::PC_NOTEMPTY::addTo( m_parameterAlgo );

    // for selecting the rasterization method
    std::shared_ptr< WItemSelection > rasterAlgos( new WItemSelection() );
    rasterAlgos->addItem( "Bresenham (Max)", "Voxelization with 3D Bresenham and use maximum per voxel" );
    rasterAlgos->addItem( "Bresenham (Sum)", "Voxelization with 3D Bresenham and sum values in voxel" );
    m_rasterAlgo = m_properties->addProperty( "Rasterization", "Which method for rasterizing the tracts", rasterAlgos->getSelectorFirst(),
            m_fullUpdate );
    WPropertyHelper::PC_SELECTONLYONE::addTo( m_rasterAlgo );
    WPropertyHelper::PC_NOTEMPTY::addTo( m_rasterAlgo );

    m_phongShading  = m_properties->addProperty( "Phong shading", "If enabled, Phong shading gets applied on a per-pixel basis.", true );
    m_colorMapping  = m_properties->addProperty( "Colormapping", "If enabled, colormapping gets applied on a per-pixel basis.", false );

    WModule::properties();
}

void WMVoxelizer::connectors()
{
    m_tractIC = WModuleInputData< const WDataSetFibers >::createAndAdd( shared_from_this(), "tractInput", "Deterministic tracts" );
    m_clusterIC = WModuleInputData< const WFiberCluster >::createAndAdd( shared_from_this(), "clusterInput", "A subset (e.g. a cluster) of tracts" );
    m_voxelizedOC = WModuleOutputData< WDataSetScalar >::createAndAdd( shared_from_this(), "voxelOutput", "The voxelized data set" );
    m_paramOC = WModuleOutputData< WDataSetScalar >::createAndAdd( shared_from_this(), "parameterizationOutput",
                                                                                  "The parameter field for the voxelized fibers." );
    WModule::connectors();  // call WModules initialization
}

void WMVoxelizer::moduleMain()
{
    m_moduleState.setResetable();
    m_moduleState.add( m_tractIC->getDataChangedCondition() );
    m_moduleState.add( m_clusterIC->getDataChangedCondition() );
    m_moduleState.add( m_fullUpdate );

    // create the post-processing node which actually does the nice stuff to the rendered image
    osg::ref_ptr< WGEPostprocessingNode > postNode = new WGEPostprocessingNode(
        WKernel::getRunningKernel()->getGraphicsEngine()->getViewer()->getCamera()
    );
    // provide the properties of the post-processor to the user
    m_properties->addProperty( postNode->getProperties() );

    // create the root node containing everything
    m_rootNode = new WGEManagedGroupNode( m_active );

    // create sheader
    osg::ref_ptr< WGEShader > shader( new WGEShader( "WMVoxelizer", m_localPath ) );
    shader->addPreprocessor( WGEShaderPreprocessor::SPtr(
        new WGEShaderPropertyDefineOptions< WPropBool >( m_phongShading, "PHONGSHADING_DISABLED", "PHONGSHADING_ENABLED" ) )
    );
    shader->addPreprocessor( WGEShaderPreprocessor::SPtr(
        new WGEShaderPropertyDefineOptions< WPropBool >( m_colorMapping, "COLORMAPPING_DISABLED", "COLORMAPPING_ENABLED" ) )
    );

    // apply colormapping
    WGEColormapping::apply( m_rootNode, shader );

    // add it to postproc node and register shader
    postNode->insert( m_rootNode, shader );

    // add to scene
    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->insert( postNode );

    ready();

    while( !m_shutdownFlag() ) // loop until the module container requests the module to quit
    {
        bool selectionPresent = ( m_clusterIC->getData() != NULL );

        if( !m_tractIC->getData() )
        {
            continue;
        }

        size_t numTracts = ( selectionPresent ? m_clusterIC->getData()->size() : m_tractIC->getData()->size() );

        infoLog() << "Start voxelization with: " << numTracts << " tracts";

        boost::array< std::shared_ptr< WDataSetScalar >, 2 > result = generateDatasets( m_tractIC->getData(), m_clusterIC->getData() );

        if( !result.empty() )
        {
            m_voxelizedOC->updateData( result[0] );
            if( result.size() == 2 ) // parameterized dataset available
            {
                m_paramOC->updateData( result[1] );
            }

            m_rootNode->clear();
            if( m_renderingActive->get() )
            {
                m_rootNode->insert( genDataSetGeode( result[0] ) );
            }
        }

        infoLog() << "Finished.";

        m_moduleState.wait(); // waits for firing of m_moduleState ( dataChanged, shutdown, etc. )
    }

    // clean up scene
    m_rootNode->clear();
    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->remove( postNode );
}

std::shared_ptr< WGridRegular3D > WMVoxelizer::constructGrid( std::shared_ptr< const WDataSetFibers > tracts,
        std::shared_ptr< const WFiberCluster > cluster ) const
{
    WBoundingBox bb;
    if( cluster )
    {
        bb = cluster->getBoundingBox();
    }
    else
    {
        bb = tracts->getBoundingBox();
    }

    float nbVoxelsPerUnit = m_voxelsPerUnit->get( true );

    // TODO(math): remove hardcoded meta grid here.
    // the "+1" in the following three statements is because there may be some more voxels
    // The first and last voxel are only half sized! hence one more position is needed
    size_t nbPosX = std::ceil( bb.xMax() - bb.xMin() ) + 1;
    size_t nbPosY = std::ceil( bb.yMax() - bb.yMin() ) + 1;
    size_t nbPosZ = std::ceil( bb.zMax() - bb.zMin() ) + 1;

    WMatrix< double > mat( 4, 4 );
    mat.makeIdentity();
    mat( 0, 0 ) = mat( 1, 1 ) = mat( 2, 2 ) = 1.0 / nbVoxelsPerUnit;
    mat( 0, 3 ) = bb.getMin()[ 0 ];
    mat( 1, 3 ) = bb.getMin()[ 1 ];
    mat( 2, 3 ) = bb.getMin()[ 2 ];

    WGridTransformOrtho transform( mat );

    std::shared_ptr< WGridRegular3D > grid( new WGridRegular3D( nbVoxelsPerUnit * nbPosX,
                                                                  nbVoxelsPerUnit * nbPosY,
                                                                  nbVoxelsPerUnit * nbPosZ,
                                                                  transform ) );
    debugLog() << "Created grid of size: " << grid->size();
    return grid;
}

boost::array< std::shared_ptr< WDataSetScalar >, 2 > WMVoxelizer::generateDatasets(
        std::shared_ptr< const WDataSetFibers > tracts,
        std::shared_ptr< const WFiberCluster > cluster ) const
{
    boost::array< std::shared_ptr< WDataSetScalar >, 2 > result; // unusable instances

    if( !tracts ) // mean while input connector has changed => abort
    {
        return result;
    }

    std::shared_ptr< WGridRegular3D > grid = constructGrid( tracts, cluster );

    std::shared_ptr< WRasterAlgorithm > rasterAlgo;
    std::string rasterName = m_rasterAlgo->get().at( 0 )->getName();
    if( rasterName == "Bresenham (Max)" )
    {
        rasterAlgo = std::shared_ptr< WBresenham >( new WBresenham( grid, WBresenham::MAXIMUM, m_antialiased->get() ) );
    }
    else if( rasterName == "Bresenham (Sum)" )
    {
        rasterAlgo = std::shared_ptr< WBresenham >( new WBresenham( grid, WBresenham::SUM, m_antialiased->get() ) );
    }
    else
    {
        errorLog() << "Invalid rasterization algorithm selected: " << rasterName << " aborting.";
        return result;
    }

    // decide which param algo to use:
    std::shared_ptr< WRasterParameterization > paramAlgo;
    std::string paramName = m_parameterAlgo->get( true ).at( 0 )->getName();
    if( paramName == "By Longest Line" )
    {
        paramAlgo = std::shared_ptr< WRasterParameterization >( new WCenterlineParameterization( grid, longestLine( tracts, cluster ) ) );
    }
    else if( paramName == "By Centerline" )
    {
        paramAlgo = std::shared_ptr< WRasterParameterization >( new WCenterlineParameterization( grid, centerLine( tracts, cluster ) ) );
    }
    else if( paramName == "By Integration" )
    {
        paramAlgo = std::shared_ptr< WRasterParameterization >( new WIntegrationParameterization( grid ) );
    }
    debugLog() << paramName << " as parameterization method selected.";

    if( paramAlgo )
    {
        rasterAlgo->addParameterizationAlgorithm( paramAlgo );
    }

    raster( rasterAlgo, tracts, cluster );

    result[0] = rasterAlgo->generateDataSet();

    if( paramAlgo )
    {
        result[1] = paramAlgo->getDataSet();
    }

    return result;
}

std::shared_ptr< WFiber > WMVoxelizer::longestLine( std::shared_ptr< const WDataSetFibers > tracts,
        std::shared_ptr< const WFiberCluster > cluster ) const
{
    if( cluster )
    {
        return cluster->getLongestLine();
    }
    return longestLine( tracts );
}

std::shared_ptr< WFiber > WMVoxelizer::centerLine( std::shared_ptr< const WDataSetFibers > tracts,
        std::shared_ptr< const WFiberCluster > cluster ) const
{
    if( cluster )
    {
        return cluster->getCenterLine();
    }
    return centerLine( tracts );
}

void WMVoxelizer::raster( std::shared_ptr< WRasterAlgorithm > algo, std::shared_ptr< const WDataSetFibers > tracts,
        std::shared_ptr< const WFiberCluster > cluster ) const
{
    // for each tract apply a call to algo->raster( tract );

    if( cluster )
    {
        std::shared_ptr< const WDataSetFiberVector > clusterTracts = cluster->getDataSetReference();
        const std::list< size_t >& tractIDs = cluster->getIndices();
        std::list< size_t >::const_iterator cit = tractIDs.begin();
        for( cit = tractIDs.begin(); cit != tractIDs.end(); ++cit )
        {
            algo->raster( clusterTracts->at( *cit ) );
        }
    }
    else
    {
        std::shared_ptr< WDataSetFiberVector > allTracts( new WDataSetFiberVector( tracts ) );
        for( WDataSetFiberVector::const_iterator cit = allTracts->begin(); cit != allTracts->end(); ++cit )
        {
            algo->raster( *cit );
        }
    }

    algo->finished();
}

osg::ref_ptr< osg::Node > WMVoxelizer::genDataSetGeode( std::shared_ptr< WDataSetScalar > dataset ) const
{
    // set the scaling of the dataset. We assume a unit cube per voxel. But this might not be true:
    WGridRegular3D::SPtr grid = std::dynamic_pointer_cast< WGridRegular3D >( dataset->getGrid() );
    if( !grid )
    {
        errorLog() << "The dataset grid is not regular.";
        return new osg::Node;   // empty node
    }
    WPosition size( grid->getOffsetX(), grid->getOffsetY(), grid->getOffsetZ() );

    // add cubes to this geode
    osg::ref_ptr< osg::Geode > geode( new osg::Geode );

    std::shared_ptr< WValueSet< double > > valueset = std::dynamic_pointer_cast< WValueSet< double > >( dataset->getValueSet() );
    if( !valueset )
    {
        errorLog() << "The dataset does not contain a double valueset";
        return new osg::Node;   // empty node
    }

    // create geometry for each voxel
    osg::ref_ptr< osg::Geometry > geometry = osg::ref_ptr< osg::Geometry >( new osg::Geometry );
    const std::vector< double >& values = *valueset->rawDataVectorPointer();
    for( size_t i = 0; i < values.size(); ++i )
    {
        if( values[i] != 0.0 )
        {
            // collect data
            WPosition pos = grid->getPosition( i );
            double transparency = ( values[i] <= 1.0 ? values[i] : 1.0 );
            WColor color( 1.0, 0.0, 0.0, transparency );

            // build cube
            wge::createCube( geometry, pos, size, color );
        }
    }

    // done
    geode->addDrawable( geometry );
    return geode;
}
