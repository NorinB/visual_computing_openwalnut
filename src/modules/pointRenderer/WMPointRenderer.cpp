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

#include <limits>
#include <memory>
#include <string>

#include <osg/Geode>

#include "WMPointRenderer.h"
#include "core/common/WLimits.h"
#include "core/common/math/WMath.h"
#include "core/dataHandler/WDataSetPoints.h"
#include "core/graphicsEngine/WGEColormapping.h"
#include "core/graphicsEngine/WGEGeodeUtils.h"
#include "core/graphicsEngine/WGEManagedGroupNode.h"
#include "core/graphicsEngine/WGEUtils.h"
#include "core/graphicsEngine/postprocessing/WGEPostprocessingNode.h"
#include "core/graphicsEngine/shaders/WGEShader.h"
#include "core/kernel/WKernel.h"

// This line is needed by the module loader to actually find your module.
W_LOADABLE_MODULE( WMPointRenderer )

WMPointRenderer::WMPointRenderer():
    WModule()
{
}

WMPointRenderer::~WMPointRenderer()
{
    // Cleanup!
}

std::shared_ptr< WModule > WMPointRenderer::factory() const
{
    // See "src/modules/template/" for an extensively documented example.
    return std::shared_ptr< WModule >( new WMPointRenderer() );
}

const char** WMPointRenderer::getXPMIcon() const
{
    return NULL;
}

const std::string WMPointRenderer::getName() const
{
    // Specify your module name here. This name must be UNIQUE!
    return "Point Renderer";
}

const std::string WMPointRenderer::getDescription() const
{
    return "Render a given point dataset.";
}

void WMPointRenderer::connectors()
{
    // this input contains the triangle data
    m_pointInput = WModuleInputData< WDataSetPoints >::createAndAdd( shared_from_this(), "points", "The data to display" );

    // call WModule's initialization
    WModule::connectors();
}

void WMPointRenderer::properties()
{
    // Info properties
    m_nbVertices = m_infoProperties->addProperty( "Points", "The number of points in the visualized data set.", 0 );
    m_nbVertices->setMax( std::numeric_limits< int >::max() );

    // some properties need to trigger an update
    m_propCondition = std::shared_ptr< WCondition >( new WCondition() );

    // setup all the properties. See header file for their meaning and purpose.
    m_size = m_properties->addProperty( "Point size", "The size of the points.", 1.0 );
    m_size->setMin( 0.0001 );
    m_size->setMax( 10.0 );

    m_useCorrectDepth = m_properties->addProperty( "Correct Depth", "If set, the depths of the sprites are calculated correctly. You can disable "
                                                                    "this to get higher framerates at the cost of visual correctness.", true );

    m_useAttribute = m_properties->addProperty( "Use Attribute", "Decides whether attribute or uniform is used", false, true );

    // call WModule's initialization
    WModule::properties();
}

void WMPointRenderer::moduleMain()
{
    // let the main loop awake if the data changes.
    m_moduleState.setResetable( true, true );
    m_moduleState.add( m_pointInput->getDataChangedCondition() );
    m_moduleState.add( m_propCondition );

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // setup the main graphics-node:
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    // create the post-processing node which actually does the nice stuff to the rendered image
    osg::ref_ptr< WGEPostprocessingNode > postNode = new WGEPostprocessingNode(
        WKernel::getRunningKernel()->getGraphicsEngine()->getViewer()->getCamera()
    );
    postNode->addUpdateCallback( new WGENodeMaskCallback( m_active ) ); // disable the postNode with m_active
    // provide the properties of the post-processor to the user
    m_properties->addProperty( postNode->getProperties() );
    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->insert( postNode );

    // load the GLSL shader:
    m_shader = new WGEShader( "WMPointRenderer", m_localPath );
    // set geometry shader options
    m_shader->setParameter( GL_GEOMETRY_VERTICES_OUT_EXT, 4 );
    m_shader->setParameter( GL_GEOMETRY_INPUT_TYPE_EXT, GL_POINTS );
    m_shader->setParameter( GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_TRIANGLE_STRIP );

    // insert some uniforms and defines
    postNode->getOrCreateStateSet()->addUniform( new WGEPropertyUniform< WPropDouble >( "u_pointSize", m_size ) );
    m_shader->addPreprocessor( WGEShaderPreprocessor::SPtr(
        new WGEShaderPropertyDefineOptions< WPropBool >( m_useCorrectDepth, "DEPTHWRITE_DISABLED", "DEPTHWRITE_ENABLED" ) )
    );
    m_shader->addPreprocessor( WGEShaderPreprocessor::SPtr(
        new WGEShaderPropertyDefineOptions< WPropBool >( m_useAttribute, "USE_ATTRIBUTE_DISABLED", "USE_ATTRIBUTE_ENABLED" ) )
    );

    // register attribute
    m_shader->addBindAttribLocation( "a_pointSize", 15 );

    // signal ready state. The module is now ready to be used.
    ready();

    // loop until the module container requests the module to quit
    while( !m_shutdownFlag() )
    {
        // Now, the moduleState variable comes into play. The module can wait for the condition, which gets fired whenever the input receives data
        // or an property changes. The main loop now waits until something happens.
        debugLog() << "Waiting ...";
        m_moduleState.wait();

        // woke up since the module is requested to finish
        if( m_shutdownFlag() )
        {
            break;
        }

        // Get data and check for invalid data.
        WDataSetPoints::SPtr points = m_pointInput->getData();
        if( !points )
        {
            debugLog() << "Invalid Data. Disabling.";
            postNode->clear();
            continue;
        }

        m_nbVertices->set( points->size() );

        std::shared_ptr< WValueSet< float > > valueSet;
        if( points->getData().type() == typeid( std::shared_ptr< WValueSet< float > > ) )
        {
            valueSet = std::any_cast< std::shared_ptr< WValueSet< float > > >( points->getData() );
        }

        m_useAttribute->set( valueSet ? true : false );

        // we have valid data. Put this into a geode
        osg::ref_ptr< osg::Geometry > geometry = osg::ref_ptr< osg::Geometry >( new osg::Geometry );
        osg::ref_ptr< osg::Geode >  geode( new osg::Geode() );

        osg::StateSet* state = geode->getOrCreateStateSet();
        state->setMode( GL_BLEND, osg::StateAttribute::ON );

        // convert point arrays to osg vec3 arrays
        osg::ref_ptr< osg::Vec3Array > vertices = osg::ref_ptr< osg::Vec3Array >( new osg::Vec3Array );
        osg::ref_ptr< osg::Vec4Array > colors = osg::ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
        osg::ref_ptr< osg::FloatArray > sizes = osg::ref_ptr< osg::FloatArray >( new osg::FloatArray );

        WDataSetPoints::VertexArray pointVertices = points->getVertices();
        WDataSetPoints::ColorArray pointColors = points->getColors();
        for( size_t pointIdx = 0; pointIdx < points->size(); ++pointIdx )
        {
            osg::Vec3 vert = points->operator[]( pointIdx );
            osg::Vec4 color = points->getColor( pointIdx );

            vertices->push_back( vert );
            colors->push_back( color );

            if( valueSet )
            {
                sizes->push_back( valueSet->getScalar( pointIdx ) );
            }
        }

        // combine to geometry
        geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::POINTS, 0, vertices->size() ) );
        geometry->setVertexArray( vertices );
        geometry->setColorArray( colors );
        geometry->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
        if( valueSet )
        {
            geometry->setVertexAttribArray( 15, sizes, osg::Array::BIND_PER_VERTEX );
        }

        // add geometry to geode
        geode->addDrawable( geometry );

        wge::enableTransparency( geode );

        // shader and colormapping
        m_shader->apply( geode );

        // add geode to group
        postNode->clear();
        postNode->insert( geode, m_shader );

        debugLog() << "Bounding Box: " << points->getBoundingBox();
    }

    // it is important to always remove the modules again
    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->remove( postNode );
}
