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

#ifndef WGETEXTUREUTILS_H
#define WGETEXTUREUTILS_H

#include <string>

#include <osg/Node>
#include <osg/StateSet>
#include <osg/TexMat>
#include <osg/Texture1D>
#include <osg/Texture2D>
#include <osg/Texture3D>

#include "../common/WStringUtils.h"

#include "shaders/WGEPropertyUniform.h"
#include "callbacks/WGEPropertyTransformationCallback.h"
#include "callbacks/WGETexMatUniformCallback.h"


template < typename T > class WGETexture;
class WDataTexture3D;

namespace wge
{
    /**
     * Binds the specified texture to the specified unit. It automatically adds several uniforms which then can be utilized in the shader:
     * - u_textureXUnit: the unit number (useful for accessing correct gl_TexCoord and so on)
     * - u_textureXSampler: the needed sampler
     * - u_textureXSizeX: width of the texture in pixels
     * - u_textureXSizeY: height of the texture in pixels
     * - u_textureXSizeZ: depth of the texture in pixels
     *
     * \warning this is not OSG-thread-safe. This method binds the texture immediately. So please use this only for nodes which are not yet used
     * in the scene graph. For safely binding textures to a node already in the scene, utilize an update callback.
     *
     * \param node where to bind
     * \param unit the unit to use
     * \param texture the texture to use.
     * \param prefix if specified, defines the uniform name prefix. (Sampler, Unit, Sizes, ...)
     * \tparam T the type of texture. Usually osg::Texture3D or osg::Texture2D.
     */
    template < typename T >
    void bindTexture( osg::ref_ptr< osg::Node > node, osg::ref_ptr< T > texture, size_t unit = 0, std::string prefix = "" );

    /**
     * Binds the specified texture to the specified unit. It automatically adds several uniforms which then can be utilized in the shader:
     * - u_textureXUnit: the unit number (useful for accessing correct gl_TexCoord and so on)
     * - u_textureXSampler: the needed sampler
     * - u_textureXSizeX: width of the texture in pixels
     * - u_textureXSizeY: height of the texture in pixels
     * - u_textureXSizeZ: depth of the texture in pixels
     * If the specified texture is a WGETexture, it additionally adds u_textureXMin and u_textureXScale for unscaling.
     *
     * \warning this is not OSG-thread-safe. This method binds the texture immediately. So please use this only for nodes which are not yet used
     * in the scene graph. For safely binding textures to a node already in the scene, utilize an update callback.
     *
     * \param node where to bind
     * \param unit the unit to use
     * \param texture the texture to use.
     * \param prefix if specified, defines the uniform name prefix. (Sampler, Unit, Sizes, ...)
     * \tparam T the type of texture. Usually osg::Texture3D or osg::Texture2D.
     */
    template < typename T >
    void bindTexture( osg::ref_ptr< osg::Node > node, osg::ref_ptr< WGETexture< T > > texture, size_t unit = 0, std::string prefix = ""  );

    /**
     * Removes the binding associated with the specified unit.
     *
     * \param unit the unit to unbind
     * \param node the node from which the binding should be removed
     * \param count the number of units beginning at the specified one should be unbound? 1 is the default.
     */
    void unbindTexture( osg::ref_ptr< osg::Node > node, size_t unit, size_t count = 1 );

    /**
     * Returns the maximum number of textures that can be bound to a node. Call this only from withing the OSG thread!
     *
     * \return the max number of texture units.
     */
    size_t getMaxTexUnits();

    /**
     * This generates an 1D texture only containing white noise in its channels.
     *
     * \param sizeX size in x direction (in pixels)
     * \param channels the number of channels. Valid are 1, 3 and 4.
     *
     * \return the generated texture.
     */
    osg::ref_ptr< WGETexture< osg::Texture1D > > genWhiteNoiseTexture( size_t sizeX, size_t channels );

    /**
     * This generates an 2D texture only containing white noise in its channels.
     *
     * \param sizeX size in x direction (in pixels)
     * \param sizeY size in y direction (in pixels)
     * \param channels the number of channels. Valid are 1, 3 and 4.
     *
     * \return the generated texture.
     */
    osg::ref_ptr< WGETexture< osg::Texture2D > > genWhiteNoiseTexture( size_t sizeX, size_t sizeY, size_t channels );

    /**
     * This generates an 3D texture only containing white noise in its channels.
     *
     * \param sizeX size in x direction (in pixels)
     * \param sizeY size in y direction (in pixels)
     * \param sizeZ size in z direction (in pixels)
     * \param channels the number of channels. Valid are 1, 3 and 4.
     *
     * \return the generated texture.
     */
    osg::ref_ptr< WGETexture< osg::Texture3D > > genWhiteNoiseTexture( size_t sizeX, size_t sizeY, size_t sizeZ, size_t channels );

    /**
     * Generates an image only containing white noise in its channels.
     *
     * \param sizeX size in x direction (in pixels)
     * \param sizeY size in y direction (in pixels)
     * \param sizeZ size in z direction (in pixels)
     * \param channels the number of channels. Valid are 1, 3 and 4.
     *
     * \return the generated image.
     */
    osg::ref_ptr< osg::Image > genWhiteNoiseImage( size_t sizeX, size_t sizeY, size_t sizeZ, size_t channels = 1 );

    /**
     * Generates a 3D turing noise texture. For details, see:
     *
     * Eichelbaum, Sebastian, et al. "Fabric-like visualization of tensor field data on arbitrary surfaces
     * in image space." New Developments in the Visualization and Processing of Tensor Fields. Springer Berlin Heidelberg, 2012. 71-92.
     *
     * \param sizeX The size of the textures in voxels, should be a power of 2.
     * \param sizeY The size of the textures in voxels, should be a power of 2.
     * \param sizeZ The size of the textures in voxels, should be a power of 2.
     * \param channels The number of channels; either 1, 3 or 4.
     *
     * \return The texture.
     */
    osg::ref_ptr< WGETexture< osg::Texture3D > > genTuringNoiseTexture( std::size_t sizeX, std::size_t sizeY,
                                                                        std::size_t sizeZ, std::size_t channels = 1 );
}

template < typename T >
void wge::bindTexture( osg::ref_ptr< osg::Node > node, osg::ref_ptr< T > texture, size_t unit, std::string prefix )
{
    if( prefix == "" )
    {
        prefix = "u_texture" + string_utils::toString( unit );
    }

    osg::StateSet* state = node->getOrCreateStateSet();
    state->setTextureAttributeAndModes( unit, texture, osg::StateAttribute::ON );
    state->addUniform( new osg::Uniform( ( prefix + "Sampler" ).c_str(), static_cast< int >( unit ) ) );
    state->addUniform( new osg::Uniform( ( prefix + "Unit" ).c_str(), static_cast< int >( unit ) ) );
    state->addUniform( new osg::Uniform( ( prefix + "SizeX" ).c_str(), static_cast< int >( texture->getTextureWidth() ) ) );
    state->addUniform( new osg::Uniform( ( prefix + "SizeY" ).c_str(), static_cast< int >( texture->getTextureHeight() ) ) );
    state->addUniform( new osg::Uniform( ( prefix + "SizeZ" ).c_str(), static_cast< int >( texture->getTextureDepth() ) ) );
}

template < typename T >
void wge::bindTexture( osg::ref_ptr< osg::Node > node, osg::ref_ptr< WGETexture< T > > texture, size_t unit, std::string prefix )
{
    if( prefix == "" )
    {
        prefix = "u_texture" + string_utils::toString( unit );
    }

    wge::bindTexture< T >( node, osg::ref_ptr< T >( texture ), unit, prefix );

    // set the texture matrix to the stateset
    osg::TexMat* texMat = new osg::TexMat( texture->transformation()->get() );
    // use a callback to update the tex matrix if needed according to transformation property of texture
    texMat->setUpdateCallback( new WGEPropertyTransformationCallback< osg::StateAttribute, osg::TexMat >( texture->transformation() ) );
    node->getOrCreateStateSet()->setTextureAttributeAndModes( unit, texMat, osg::StateAttribute::ON );

    osg::ref_ptr< osg::Uniform > uniform = new osg::Uniform(
        osg::Uniform::FLOAT_MAT4, ( "ow_TextureMatrix" + string_utils::toString( unit ) ).c_str() );
    uniform->setUpdateCallback( new WGETexMatUniformCallback( texMat ) );
    node->getOrCreateStateSet()->addUniform( uniform );

    // add some additional uniforms containing scaling information
    texture->applyUniforms( prefix, node->getOrCreateStateSet() );
}

#endif  // WGETEXTUREUTILS_H

