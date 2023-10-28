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

#version 150 core

#include "WGEShader-uniforms.glsl"

in vec4 v_texCoord;

/**
 * The texture Unit for the depth field
 */
uniform sampler2D u_texture0Sampler;

/**
 * Size of texture in pixels
 */
uniform int u_texture0SizeX;

/**
 * Size of texture in pixels
 */
uniform int u_texture0SizeY;

/**
 * Size of texture in pixels
 */
uniform int u_texture0SizeZ;

/**
 * Main. Calculates the Laplace Filter for each pixel.
 */
void main()
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    // GETTING TEXELS
    //
    // Get surrounding texels; needed for ALL filters
    /////////////////////////////////////////////////////////////////////////////////////////////

    // get data of surrounding textels
    float offsetW = 2.0 / u_texture0SizeX;
    float offsetH = 2.0 / u_texture0SizeY;

    vec2 texCoord = v_texCoord.st;
    vec4 c  = texture( u_texture0Sampler, texCoord );
    vec4 bl = texture( u_texture0Sampler, texCoord + vec2( -offsetW, -offsetH ) );
    vec4 l  = texture( u_texture0Sampler, texCoord + vec2( -offsetW,     0.0  ) );
    vec4 tl = texture( u_texture0Sampler, texCoord + vec2( -offsetW,  offsetH ) );
    vec4 t  = texture( u_texture0Sampler, texCoord + vec2(     0.0,   offsetH ) );
    vec4 tr = texture( u_texture0Sampler, texCoord + vec2(  offsetW,  offsetH ) );
    vec4 r  = texture( u_texture0Sampler, texCoord + vec2(  offsetW,     0.0  ) );
    vec4 br = texture( u_texture0Sampler, texCoord + vec2(  offsetW,  offsetH ) );
    vec4 b  = texture( u_texture0Sampler, texCoord + vec2(     0.0,  -offsetH ) );

    /////////////////////////////////////////////////////////////////////////////////////////////
    // LAPLACE
    //
    // apply a standart laplace filter kernel
    /////////////////////////////////////////////////////////////////////////////////////////////

    // laplace filter kernel
    gl_FragColor = vec4(
        vec3( 10.0 * abs(
                            0.0 * tl +  1.0 * t + 0.0 * tr +
                            1.0 * l  + -4.0 * c + 1.0 * r  +
                            0.0 * bl +  1.0 * b + 0.0 * br
                        ).r
            ), 1.0 );
}

