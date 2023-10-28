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

#include <memory>
#include <string>
#include <vector>

#include "WGEPostprocessor.h"
#include "WGEPostprocessorCelShading.h"
#include "WGEPostprocessorEdgeEnhance.h"
#include "WGEPostprocessorGauss.h"
#include "WGEPostprocessorHalftone.h"
#include "WGEPostprocessorLineAO.h"
#include "WGEPostprocessorSSAO.h"

WGEPostprocessor::ProcessorList WGEPostprocessor::m_postProcessors;

WGEPostprocessor::WGEPostprocessor( std::string name, std::string description ):
    WPrototyped(),
    m_resultTextures(),
    m_depthTexture(),
    m_properties( std::shared_ptr< WProperties >( new WProperties( "Settings for " + name, "Post-processing properties" ) ) ),
    m_name( name ),
    m_description( description )
{
    // there is always one property:
    m_effectOnly = m_properties->addProperty( "Effect Only", "If active, the plain effect will be shown instead a combination of effect "
                                                             "and color. This settings does not affect all postprocessors.", false );
    m_effectScale = m_properties->addProperty( "Effect Scaling", "Use this to overemphasize an effect or to weaken it. Technically spoken, this "
                                                "factor determines the pre-multiplication done prior to blending with the input color.", 1.0,
                                                true );
    m_effectScale->setMin( 0.0 );
    m_effectScale->setMax( 10.0 );

    // for convenience, also create a preprocessor for this property
    m_effectOnlyPreprocessor = WGEShaderPreprocessor::SPtr( new WGEShaderPropertyDefineOptions< WPropBool >( m_effectOnly,
        "WGE_POSTPROCESSOR_OUTPUT_COMBINE", "WGE_POSTPROCESSOR_OUTPUT_EFFECT_ONLY" ) );
}

WGEPostprocessor::~WGEPostprocessor()
{
    // cleanup
}

WPropGroup WGEPostprocessor::getProperties() const
{
    return m_properties;
}

osg::ref_ptr< osg::Texture2D > WGEPostprocessor::getOutput( size_t idx ) const
{
    return m_resultTextures[ idx ];
}

const std::vector< osg::ref_ptr< osg::Texture2D > >& WGEPostprocessor::getOutputList() const
{
    return m_resultTextures;
}

osg::ref_ptr< osg::Texture2D > WGEPostprocessor::getDepth() const
{
    return m_depthTexture;
}

WGEPostprocessor::PostprocessorInput::PostprocessorInput()
{
    // leave them un-initialized
}

WGEPostprocessor::PostprocessorInput::PostprocessorInput( std::vector< osg::ref_ptr< osg::Texture2D > > from )
{
    if( from.size() > 0 )
    {
        m_colorTexture = from[0];
    }
    if( from.size() > 1 )
    {
        m_normalTexture = from[1];
    }
    if( from.size() > 2 )
    {
        m_parameterTexture = from[2];
    }
    if( from.size() > 3 )
    {
        m_tangentTexture = from[3];
    }
    if( from.size() > 4 )
    {
        m_depthTexture = from[4];
    }
}

WGEPostprocessor::PostprocessorInput::PostprocessorInput( osg::ref_ptr< osg::Texture2D > color,
                                                          osg::ref_ptr< osg::Texture2D > normal,
                                                          osg::ref_ptr< osg::Texture2D > parameter,
                                                          osg::ref_ptr< osg::Texture2D > tangent,
                                                          osg::ref_ptr< osg::Texture2D > depth ):
    m_colorTexture( color ),
    m_normalTexture( normal ),
    m_parameterTexture( parameter ),
    m_tangentTexture( tangent ),
    m_depthTexture( depth )
{
}

WGEPostprocessor::PostprocessorInput WGEPostprocessor::PostprocessorInput::attach( osg::ref_ptr< WGEOffscreenRenderPass > from )
{
    PostprocessorInput buf;
    buf.m_colorTexture = from->attach( WGECamera::COLOR_BUFFER0 );
    buf.m_normalTexture = from->attach( WGECamera::COLOR_BUFFER1, GL_RGB );
    buf.m_parameterTexture = from->attach( WGECamera::COLOR_BUFFER2, GL_R32F );
    buf.m_tangentTexture = from->attach( WGECamera::COLOR_BUFFER3, GL_RGB );
    buf.m_depthTexture = from->attach( WGECamera::DEPTH_BUFFER );

    return buf;
}

size_t WGEPostprocessor::PostprocessorInput::bind( osg::ref_ptr< WGEOffscreenRenderPass > to ) const
{
    to->bind( m_colorTexture, 0 );
    to->bind( m_normalTexture, 1 );
    to->bind( m_parameterTexture, 2 );
    to->bind( m_depthTexture, 3 );
    to->bind( m_tangentTexture, 4 );

    return 5;
}

WGEPostprocessor::ProcessorList WGEPostprocessor::getPostprocessors()
{
    return m_postProcessors;
}

void WGEPostprocessor::initPostprocessors()
{
    // create prototypes of the postprocessors we know.
    m_postProcessors.push_back( WGEPostprocessor::SPtr( new WGEPostprocessorEdgeEnhance() ) );
    m_postProcessors.push_back( WGEPostprocessor::SPtr( new WGEPostprocessorCelShading() ) );
    m_postProcessors.push_back( WGEPostprocessor::SPtr( new WGEPostprocessorGauss() ) );
    m_postProcessors.push_back( WGEPostprocessor::SPtr( new WGEPostprocessorSSAO() ) );
    m_postProcessors.push_back( WGEPostprocessor::SPtr( new WGEPostprocessorLineAO() ) );
    m_postProcessors.push_back( WGEPostprocessor::SPtr( new WGEPostprocessorHalftone() ) );
}

size_t WGEPostprocessor::addPostprocessor( SPtr processor )
{
    m_postProcessors.push_back( processor );
    return m_postProcessors.size() - 1;
}

const std::string WGEPostprocessor::getName() const
{
    return m_name;
}

const std::string WGEPostprocessor::getDescription() const
{
    return m_description;
}

bool WGEPostprocessor::getFixedViewportSize() const
{
    return false;
}
