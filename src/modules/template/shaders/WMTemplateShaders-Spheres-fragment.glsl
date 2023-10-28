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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Welcome to this demo shader. It basically demonstrates the coupling features you already seen in WMTemplateShaders.
// (Properties coupled to uniforms, #defines, property-coupled defines and so on.
//
// NOTE: Please refer to the vertex shader first!
//
// Please note that you need a basic understanding of GLSL to understand this rather simple example.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#version 150 core

#include "WGEShader-uniforms.glsl"

// For lighting functionality.
#include "WGEShadingTools.glsl"
#include "WGETextureTools.glsl"

in vec4 v_color;

// This is updated by a callback:
uniform int u_animation;

// These uniforms where set automatically by wge::bindTexture:
uniform sampler3D u_noiseSampler;
// The size in voxel dimensions
uniform int u_noiseSizeX;
uniform int u_noiseSizeY;
uniform int u_noiseSizeZ;

// The surface normal
in vec3 v_normal;

// Normalized coordinate in the bounding volume of the sphere
in vec3 v_normalizedVertex;

void main()
{
    vec4 col = v_color;

    // Use a utility function to get the gradient for us
    vec3 grad = getGradient( u_noiseSampler, v_normalizedVertex, 1.0 / u_noiseSizeX );

    // do light. Scale by a compile time constant LIGHT_INTENSITY.
    float light = LIGHT_INTENSITY * blinnPhongIlluminationIntensity( normalize( viewAlign( v_normal * grad ) ) );

    // Time based dimming of the color.
    // NOTE: The constant PI was set on C++-side as compile time constant.
    float dimmer = 0.5 + 0.75 * sin( PI * mod( u_animation, 100.0 ) / 100.0 );

    // Apply light. Pow()? -> it makes it look more "metallic".
    col.rgb = pow( light, 1.5 ) * col.rgb;

    // This define was defined on C++ side. You can use these simple blocks to turn on/off certain features.
#ifdef BW_ENABLED
    // If this feature is enabled, we force a BW texture.
    col.rgb = vec3( col.r + col.g + col.b ) / 3.0;
#endif

    // These 4 blocks where defined as WGEShaderDefineOptions on C++ side:
#ifdef RED_ONLY
    // Do something
#endif
#ifdef GREEN_ONLY
    // Do something
#endif
#ifdef BLUE_ONLY
    // Do something
#endif
#ifdef COMBINE
    // Do something
#endif

    // finally set the color and depth
    gl_FragColor = col;
}

