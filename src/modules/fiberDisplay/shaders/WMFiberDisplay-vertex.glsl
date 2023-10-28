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

#include "WGEColormapping-vertex.glsl"

#include "WGETransformationTools.glsl"



out vec4 v_color;

/////////////////////////////////////////////////////////////////////////////
// Varyings
/////////////////////////////////////////////////////////////////////////////

#ifdef CLIPPLANE_ENABLED
/**
 * The distance to the plane
 */
out float v_dist;
#endif

/**
 * The surface normal. Needed for nice lighting.
 */
out vec3 v_normal;

/**
 * The line tangent.
 */
out vec3 v_tangent;

/**
 * The normal parameterizing the surface in orthogonal tangent direction.
 */
out vec3 v_biNormal;

/**
 * The actual, corrected vertex.
 */
out vec4 v_vertex;

/**
 * The diameter of the tube in world-space.
 */
out float v_diameter;

/**
 * This is the interpolated surface parameter describing the surface orthogonal to the tangent. 0 is the center of the strip and -1 and 1 the
 * borders.
 */
out float v_surfaceParam;

/**
 * The scaling component of the modelview matrix.
 */
out float v_worldScale;

/**
 * This varying carries the current cluster color.
 */
out vec4 v_clusterColor;

/**
 * Varying defines wether to discard the fragments or not.
 */
out float v_discard;

/////////////////////////////////////////////////////////////////////////////
// Uniforms
/////////////////////////////////////////////////////////////////////////////

/**
 * A point on the plane.
 */
uniform vec3 u_planePoint;

/**
 * The normal vector of the plane
 */
uniform vec3 u_planeVector;

/**
 * The size of the tube
 */
uniform float u_tubeSize;

#ifdef BITFIELD_ENABLED
    uniform sampler2D bitfieldSampler;
    uniform int bitfieldSize;

    uniform sampler2D selColorSampler;
    uniform int selColorSize;
#endif

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
 * Converts an index to a vec2
 * \param idx the index
 * \param size the size of the quadratic texture
 *
 * \return The x and y coordinates of the index
 */
ivec2 index2Vec2( int idx, int size )
{
    return ivec2( idx % size, idx / size );
}

/**
 * Main entry point of the vertex shader.
 */
void main()
{
#ifdef CLIPPLANE_ENABLED
    // define the plane
    vec3 n = normalize( u_planeVector );
    float d = dot( u_planePoint, n );
    v_dist = dot( osg_Vertex.xyz, n ) - d;
#endif  // CLIPPLANE_ENABLED

    // The same accounds for the vertex. Transfer it to world-space.
    v_vertex = osg_ModelViewMatrix * vec4( osg_Vertex.xyz, 1.0 );

    // fill this varying with a dummy. Not always needed.
    v_normal = vec3( 1.0, 0.0, 0.0 );

    // To avoid that the quad strip gets thinner and thinner when zooming in (or the other way around: to avoid the quad strip always occupies
    // the same screen space), we need to calculate the zoom factor involved in OpenWalnut's current camera.
    v_worldScale = getModelViewScale();

    // Grab the tangent. We have uploaded it normalized in osg_Normal per vertex
    // We need to transfer it to the world-space ass all further operations are done there.
    vec3 tangent = normalize( ( osg_ModelViewMatrix * vec4( osg_Normal, 0.0 ) ).xyz );
    v_tangent = tangent;

    // The view direction in world-space. In OpenGL this is always defined by this vector
    vec3 view = vec3( 0.0, 0.0, -1.0 );

    // Each vertex on the quad which are on the same position have a texture coordinate to differentiate them. But only if the tube mode is
    // active.
    v_surfaceParam = osg_MultiTexCoord0.s;
#ifndef TUBE_ENABLED
    v_surfaceParam = 1.0;
#endif  // !TUBE_ENABLED

    // To enforce that each quad's normal points towards the user, we move the two vertex (which are at the same point currently) according to
    // the direction stored in osg_MultiTexCoord0
    vec3 offset = normalize( v_surfaceParam * cross( view, tangent ) );
    v_biNormal = offset;

#ifdef TUBE_ENABLED
#ifdef ZOOMABLE_ENABLED

    // worldScale now contains the scaling which is done by ModelView transformation (including the camera).
    // With this, we can ensure that our offset, which is of unit-length, is scaled acccording to the camera zoom. The
    // additional uniform u_tubeSize allows the user to scale the tubes.
    // We clamp the value to ensure a minimum width of the quadstrip of 1px on screen:
    float worldScale = clamp( u_tubeSize * v_worldScale, 1.0, 1000000.0 );
#else  // ZOOMABLE_ENABLED
    // In this mode, the tubes should not be zoomed. Just use the user defined size here.
    float worldScale = clamp( u_tubeSize, 1.0, 1000000.0 );
#endif

    // Apply the offset and scale correctly.
    v_vertex.xyz += 0.1 * worldScale * offset;
    v_diameter = 0.1 * worldScale;
#endif  // TUBE_ENABLED

    // with the tangent and the view vector we got the offset vector. We can noch get the normal using the tangent and the offset.
    v_normal = cross( offset, tangent );
    v_normal *= sign( dot( v_normal, vec3( 0.0, 0.0, 1.0 ) ) );

#ifdef COLORMAPPING_ENABLED
    // Allow the colormapper to do some precalculations with the real vertex coordinate in ow-scene-space
    // NOTE: v_vertex is in world-space. We need to get it back to scene space. Directly using osg_Vertex would be possible too but this would
    // ignore the actual width of the tube.
    colormapping( osg_ModelViewMatrixInverse * v_vertex );
#endif

#ifdef BITFIELD_ENABLED
    v_discard = 1.0 - texelFetch( bitfieldSampler, index2Vec2( int( osg_Vertex.w ), bitfieldSize ), 0 ).r;
    v_clusterColor = texelFetch( selColorSampler, index2Vec2( int( osg_Vertex.w ), selColorSize ), 0 );
#endif

    // Simply project the vertex afterwards
    gl_Position = osg_ProjectionMatrix * v_vertex;
    v_color = osg_Color;
}

