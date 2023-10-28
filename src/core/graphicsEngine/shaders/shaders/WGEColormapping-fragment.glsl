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

#ifndef WGECOLORMAPPING_FRAGMENT_GLSL
#define WGECOLORMAPPING_FRAGMENT_GLSL

#version 150 core

#include "WGEShader-uniforms.glsl"

#include "WGEColorMapsImproved.glsl"

#include "WGEColormapping-uniforms.glsl"

/**
 * The texture coordinate in local texture space.
 */
in vec3 v_colormap0TexCoord;

/**
 * The texture coordinate in local texture space.
 */
in vec3 v_colormap1TexCoord;

/**
 * The texture coordinate in local texture space.
 */
in vec3 v_colormap2TexCoord;

/**
 * The texture coordinate in local texture space.
 */
in vec3 v_colormap3TexCoord;

/**
 * The texture coordinate in local texture space.
 */
in vec3 v_colormap4TexCoord;

/**
 * The texture coordinate in local texture space.
 */
in vec3 v_colormap5TexCoord;

/**
 * The texture coordinate in local texture space.
 */
in vec3 v_colormap6TexCoord;

/**
 * The texture coordinate in local texture space.
 */
in vec3 v_colormap7TexCoord;

/**
 * This method applies a colormap to the specified value and mixes it with the specified color. It uses the proper colormap and is able to
 * unscale values if needed. It uses real compositing.
 *
 * \param color this color gets mixed using alpha value with the new colormap color
 * \param sampl the texture sampl to use
 * \param coord the coordinate where to get the value
 * \param size the size in voxels
 * \param minV the minimum of the original value
 * \param clipZeroEnabled if true, zero values get clipped
 * \param scaleV the scaler used to downscale the original value to [0-1]
 * \param thresholdVLower a threshold in original space (you need to downscale it to [0-1] if you want to use it to scaled values.
 * \param thresholdVUpper a threshold in original space (you need to downscale it to [0-1] if you want to use it to scaled values.
 * \param window a window level scaling
 * \param windowEnabled if true, the window level scaling is applied
 * \param alpha the alpha blending value
 * \param cmap the colormap index to use
 */
void colormap( inout vec4 color, in sampler3D sampl, in vec3 coord, in vec3 size,
               float minV, float scaleV,
               bool clipZeroEnabled,
               float thresholdVLower, float thresholdVUpper, bool thresholdEnabled,
               bool windowEnabled, vec2  window,
               float alpha, int cmap, bool cmactive )
{
    // This implements a manual trilinear interpolation. Include WGETextureutils.glsl to use this
    // vec3 vSize = vec3( 1.0 / float( size.x ),
    //                    1.0 / float( size.y ),
    //                    1.0 / float( size.z ) );
    //
    // vec3 discreteCoord = getDiscreteVoxelCoordinate( vSize, coord );
    // vec3 voxelSpace = coord / vSize;
    // vec3 coordDiff = voxelSpace - vec3( floor( voxelSpace.x ), floor( voxelSpace.y ), floor( voxelSpace.z ) );
    //
    // vec3 c000 = getNeighbourVoxel( vSize, coord, vec3( 0.0, 0.0, 0.0 ) );
    // vec3 c010 = getNeighbourVoxel( vSize, coord, vec3( 0.0, 1.0, 0.0 ) );
    // vec3 c001 = getNeighbourVoxel( vSize, coord, vec3( 0.0, 0.0, 1.0 ) );
    // vec3 c011 = getNeighbourVoxel( vSize, coord, vec3( 0.0, 1.0, 1.0 ) );
    // vec3 c100 = getNeighbourVoxel( vSize, coord, vec3( 1.0, 0.0, 0.0 ) );
    // vec3 c110 = getNeighbourVoxel( vSize, coord, vec3( 1.0, 1.0, 0.0 ) );
    // vec3 c101 = getNeighbourVoxel( vSize, coord, vec3( 1.0, 0.0, 1.0 ) );
    // vec3 c111 = getNeighbourVoxel( vSize, coord, vec3( 1.0, 1.0, 1.0 ) );
    //
    // vec4 v00 = mix( colormap( texture( sampl, c000 ).rgba, minV, scaleV, thresholdV, thresholdEnabled, alpha, cmap, cmactive ),
    //                 colormap( texture( sampl, c100 ).rgba, minV, scaleV, thresholdV, thresholdEnabled, alpha, cmap, cmactive ), coordDiff.x );
    // vec4 v10 = mix( colormap( texture( sampl, c010 ).rgba, minV, scaleV, thresholdV, thresholdEnabled, alpha, cmap, cmactive ),
    //                 colormap( texture( sampl, c110 ).rgba, minV, scaleV, thresholdV, thresholdEnabled, alpha, cmap, cmactive ), coordDiff.x );
    // vec4 v01 = mix( colormap( texture( sampl, c001 ).rgba, minV, scaleV, thresholdV, thresholdEnabled, alpha, cmap, cmactive ),
    //                 colormap( texture( sampl, c101 ).rgba, minV, scaleV, thresholdV, thresholdEnabled, alpha, cmap, cmactive ), coordDiff.x );
    // vec4 v11 = mix( colormap( texture( sampl, c011 ).rgba, minV, scaleV, thresholdV, thresholdEnabled, alpha, cmap, cmactive ),
    //                 colormap( texture( sampl, c111 ).rgba, minV, scaleV, thresholdV, thresholdEnabled, alpha, cmap, cmactive ), coordDiff.x );
    //
    // vec4 src = mix( mix( v00, v10, coordDiff.y ),
    //            mix( v01, v11, coordDiff.y ), coordDiff.z );

    // get the value and descale it
    vec4 value = texture( sampl, coord ).rgba;

    // let someone else apply the colormap
    vec4 src = colormap( value, minV, scaleV, clipZeroEnabled,
                                              thresholdVLower, thresholdVUpper, thresholdEnabled,
                                              window, windowEnabled,
                                              alpha, cmap, cmactive );

    // compositing:
    // associated colors needed
    src.rgb *= src.a;
    // apply compositing (front to back with associated colors)
    color = ( 1.0 - src.a ) * color + src;
}

/**
 * Calculates the final colormapping. Call this from your fragment shader.
 * Be aware that this only works with the WGEColormapping class. If you are using real geometry use the other colormapping call. This version
 * takes a unit-cube texture coordinate which gets translated to the right coordinate space of the texture.
 *
 * \note If your are using this method, the call to colormapping() inside your vertex shader is NOT needed.
 *
 * \param texcoord the texture coordinate in the bounding box space of the data
 * \return the final color determined by the user defined colormapping
 */
vec4 colormapping( vec4 texcoord )
{
    vec4 finalColor = vec4( 0.0, 0.0, 0.0, 0.0 );

    // ColormapPreTransform is a mat4 defined by OpenWalnut before compilation
    vec4 t = ColormapPreTransform * texcoord;

    // back to front compositing
#ifdef Colormap7Enabled
    colormap( finalColor, u_colormap7Sampler, ( Colormap7Unit * t ).xyz,
              vec3( u_colormap7SizeX, u_colormap7SizeY, u_colormap7SizeZ ),
              u_colormap7Min, u_colormap7Scale,
              u_colormap7ClipZeroEnabled,
              u_colormap7ThresholdLower, u_colormap7ThresholdUpper, u_colormap7ThresholdEnabled,
              u_colormap7WindowEnabled, u_colormap7Window,
              u_colormap7Alpha, u_colormap7Colormap, u_colormap7Active );
#endif
#ifdef Colormap6Enabled
    colormap( finalColor, u_colormap6Sampler, ( Colormap6Unit * t ).xyz,
              vec3( u_colormap6SizeX, u_colormap6SizeY, u_colormap6SizeZ ),
              u_colormap6Min, u_colormap6Scale,
              u_colormap6ClipZeroEnabled,
              u_colormap6ThresholdLower, u_colormap6ThresholdUpper, u_colormap6ThresholdEnabled,
              u_colormap6WindowEnabled, u_colormap6Window,
              u_colormap6Alpha, u_colormap6Colormap, u_colormap6Active );
#endif
#ifdef Colormap5Enabled
    colormap( finalColor, u_colormap5Sampler, ( Colormap5Unit * t ).xyz,
              vec3( u_colormap5SizeX, u_colormap5SizeY, u_colormap5SizeZ ),
              u_colormap5Min, u_colormap5Scale,
              u_colormap5ClipZeroEnabled,
              u_colormap5ThresholdLower, u_colormap5ThresholdUpper, u_colormap5ThresholdEnabled,
              u_colormap5WindowEnabled, u_colormap5Window,
              u_colormap5Alpha, u_colormap5Colormap, u_colormap5Active );
#endif
#ifdef Colormap4Enabled
    colormap( finalColor, u_colormap4Sampler, ( Colormap4Unit * t ).xyz,
              vec3( u_colormap4SizeX, u_colormap4SizeY, u_colormap4SizeZ ),
              u_colormap4Min, u_colormap4Scale,
              u_colormap4ClipZeroEnabled,
              u_colormap4ThresholdLower, u_colormap4ThresholdUpper, u_colormap4ThresholdEnabled,
              u_colormap4WindowEnabled, u_colormap4Window,
              u_colormap4Alpha, u_colormap4Colormap, u_colormap4Active );
#endif
#ifdef Colormap3Enabled
    colormap( finalColor, u_colormap3Sampler, ( Colormap3Unit * t ).xyz,
              vec3( u_colormap3SizeX, u_colormap3SizeY, u_colormap3SizeZ ),
              u_colormap3Min, u_colormap3Scale,
              u_colormap3ClipZeroEnabled,
              u_colormap3ThresholdLower, u_colormap3ThresholdUpper, u_colormap3ThresholdEnabled,
              u_colormap3WindowEnabled, u_colormap3Window,
              u_colormap3Alpha, u_colormap3Colormap, u_colormap3Active );
#endif
#ifdef Colormap2Enabled
    colormap( finalColor, u_colormap2Sampler, ( Colormap2Unit * t ).xyz,
              vec3( u_colormap2SizeX, u_colormap2SizeY, u_colormap2SizeZ ),
              u_colormap2Min, u_colormap2Scale,
              u_colormap2ClipZeroEnabled,
              u_colormap2ThresholdLower, u_colormap2ThresholdUpper, u_colormap2ThresholdEnabled,
              u_colormap2WindowEnabled, u_colormap2Window,
              u_colormap2Alpha, u_colormap2Colormap, u_colormap2Active );
#endif
#ifdef Colormap1Enabled
    colormap( finalColor, u_colormap1Sampler, ( Colormap1Unit * t ).xyz,
              vec3( u_colormap1SizeX, u_colormap1SizeY, u_colormap1SizeZ ),
              u_colormap1Min, u_colormap1Scale,
              u_colormap1ClipZeroEnabled,
              u_colormap1ThresholdLower, u_colormap1ThresholdUpper, u_colormap1ThresholdEnabled,
              u_colormap1WindowEnabled, u_colormap1Window,
              u_colormap1Alpha, u_colormap1Colormap, u_colormap1Active );
#endif
#ifdef Colormap0Enabled
    colormap( finalColor, u_colormap0Sampler, ( Colormap0Unit * t ).xyz,
              vec3( u_colormap0SizeX, u_colormap0SizeY, u_colormap0SizeZ ),
              u_colormap0Min, u_colormap0Scale,
              u_colormap0ClipZeroEnabled,
              u_colormap0ThresholdLower, u_colormap0ThresholdUpper, u_colormap0ThresholdEnabled,
              u_colormap0WindowEnabled, u_colormap0Window,
              u_colormap0Alpha, u_colormap0Colormap, u_colormap0Active );
#endif

    return finalColor;
}

/**
 * Calculates the final colormapping. Call this from your fragment shader. A call to colormapping() from within the vertex shader is also needed.
 * Be aware that this only works with the WGEColormapping class. This version uses the interpolated texture coordinate from the vertex shader. Be
 * yourself aware that this should be used only for geometry based data. If you are using raytracing-like techniques where only texture
 * coordinates of the proxy geometry are available, use the colormapping( vec3 ) call instead.
 *
 * \return the final color determined by the user defined colormapping
 */
vec4 colormapping()
{
    vec4 finalColor = vec4( 0.0, 0.0, 0.0, 0.0 );

    // back to front compositing
#ifdef Colormap7Enabled
    colormap( finalColor, u_colormap7Sampler, v_colormap7TexCoord.xyz,
                          vec3( u_colormap7SizeX, u_colormap7SizeY, u_colormap7SizeZ ),
                          u_colormap7Min, u_colormap7Scale,
                          u_colormap7ClipZeroEnabled,
                          u_colormap7ThresholdLower, u_colormap7ThresholdUpper,
                          u_colormap7ThresholdEnabled,
                          u_colormap7WindowEnabled, u_colormap7Window,
                          u_colormap7Alpha, u_colormap7Colormap, u_colormap7Active );
#endif
#ifdef Colormap6Enabled
    colormap( finalColor, u_colormap6Sampler, v_colormap6TexCoord.xyz,
                          vec3( u_colormap6SizeX, u_colormap6SizeY, u_colormap6SizeZ ),
                          u_colormap6Min, u_colormap6Scale,
                          u_colormap6ClipZeroEnabled,
                          u_colormap6ThresholdLower, u_colormap6ThresholdUpper,
                          u_colormap6ThresholdEnabled,
                          u_colormap6WindowEnabled, u_colormap6Window,
                          u_colormap6Alpha, u_colormap6Colormap, u_colormap6Active );
#endif
#ifdef Colormap5Enabled
    colormap( finalColor, u_colormap5Sampler, v_colormap5TexCoord.xyz,
                          vec3( u_colormap5SizeX, u_colormap5SizeY, u_colormap5SizeZ ),
                          u_colormap5Min, u_colormap5Scale,
                          u_colormap5ClipZeroEnabled,
                          u_colormap5ThresholdLower, u_colormap5ThresholdUpper,
                          u_colormap5ThresholdEnabled,
                          u_colormap5WindowEnabled, u_colormap5Window,
                          u_colormap5Alpha, u_colormap5Colormap, u_colormap5Active );
#endif
#ifdef Colormap4Enabled
    colormap( finalColor, u_colormap4Sampler, v_colormap4TexCoord.xyz,
                          vec3( u_colormap4SizeX, u_colormap4SizeY, u_colormap4SizeZ ),
                          u_colormap4Min, u_colormap4Scale,
                          u_colormap4ClipZeroEnabled,
                          u_colormap4ThresholdLower, u_colormap4ThresholdUpper,
                          u_colormap4ThresholdEnabled,
                          u_colormap4WindowEnabled, u_colormap4Window,
                          u_colormap4Alpha, u_colormap4Colormap, u_colormap4Active );
#endif
#ifdef Colormap3Enabled
    colormap( finalColor, u_colormap3Sampler, v_colormap3TexCoord.xyz,
                          vec3( u_colormap3SizeX, u_colormap3SizeY, u_colormap3SizeZ ),
                          u_colormap3Min, u_colormap3Scale,
                          u_colormap3ClipZeroEnabled,
                          u_colormap3ThresholdLower, u_colormap3ThresholdUpper,
                          u_colormap3ThresholdEnabled,
                          u_colormap3WindowEnabled, u_colormap3Window,
                          u_colormap3Alpha, u_colormap3Colormap, u_colormap3Active );
#endif
#ifdef Colormap2Enabled
    colormap( finalColor, u_colormap2Sampler, v_colormap2TexCoord.xyz,
                          vec3( u_colormap2SizeX, u_colormap2SizeY, u_colormap2SizeZ ),
                          u_colormap2Min, u_colormap2Scale,
                          u_colormap2ClipZeroEnabled,
                          u_colormap2ThresholdLower, u_colormap2ThresholdUpper,
                          u_colormap2ThresholdEnabled,
                          u_colormap2WindowEnabled, u_colormap2Window,
                          u_colormap2Alpha, u_colormap2Colormap, u_colormap2Active );
#endif
#ifdef Colormap1Enabled
    colormap( finalColor, u_colormap1Sampler, v_colormap1TexCoord.xyz,
                          vec3( u_colormap1SizeX, u_colormap1SizeY, u_colormap1SizeZ ),
                          u_colormap1Min, u_colormap1Scale,
                          u_colormap1ClipZeroEnabled,
                          u_colormap1ThresholdLower, u_colormap1ThresholdUpper,
                          u_colormap1ThresholdEnabled,
                          u_colormap1WindowEnabled, u_colormap1Window,
                          u_colormap1Alpha, u_colormap1Colormap, u_colormap1Active );
#endif
#ifdef Colormap0Enabled
    colormap( finalColor, u_colormap0Sampler, v_colormap0TexCoord.xyz,
                          vec3( u_colormap0SizeX, u_colormap0SizeY, u_colormap0SizeZ ),
                          u_colormap0Min, u_colormap0Scale,
                          u_colormap0ClipZeroEnabled,
                          u_colormap0ThresholdLower, u_colormap0ThresholdUpper,
                          u_colormap0ThresholdEnabled,
                          u_colormap0WindowEnabled, u_colormap0Window,
                          u_colormap0Alpha, u_colormap0Colormap, u_colormap0Active );
#endif

    return finalColor;
}

#endif // WGECOLORMAPPING_FRAGMENT_GLSL

