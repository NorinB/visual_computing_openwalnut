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

#include "WGEShader-attributes.glsl"
#include "WGEShader-uniforms.glsl"

#include "WGETransformationTools.glsl"

// Now you are in the vertex shader of the first pass. All the shaders for each pass are nothing special. They are standard GLSL shaders.

// The surface normal
out vec3 v_normal;

void main()
{
    // prepare light
    v_normal = osg_NormalMatrix * osg_Normal;
    gl_Position = osg_ModelViewProjectionMatrix * osg_Vertex;
}
