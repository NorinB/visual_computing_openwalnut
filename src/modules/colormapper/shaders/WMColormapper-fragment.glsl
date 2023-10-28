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

#include "WGEColorMapsImproved.glsl"

/////////////////////////////////////////////////////////////////////////////
// Varyings
/////////////////////////////////////////////////////////////////////////////

/**
 * The value along the bar.
 */
in float v_value;

/////////////////////////////////////////////////////////////////////////////
// Uniforms
/////////////////////////////////////////////////////////////////////////////

/**
 * The colormap to show.
 */
uniform int u_colormap = 0;

/**
 * The colormap to show.
 */
uniform float u_minV = 0;

/**
 * The colormap to show.
 */
uniform float u_scaleV = 0;

/////////////////////////////////////////////////////////////////////////////
// Attributes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

/**
 * Main entry point of the fragment shader.
 */
void main()
{
    vec4 col;
    if( u_colormap == 3 )
    {
        col = colormap( vec4( v_value ), u_minV, u_scaleV, false, 0.0, 1.0, false, vec2( 0.0, 1.0 ), false, 1.0, u_colormap, true );
    }
    else
    {
        col = colormap( vec4( v_value ), 0.0, 1.0, false, 0.0, 1.0, false, vec2( 0.0, 1.0 ), false, 1.0, u_colormap, true );
    }

    gl_FragColor = col;
}

