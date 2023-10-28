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

#ifndef WGEPOSTPROCESSOR_FRAGMENT_GLSL
#define WGEPOSTPROCESSOR_FRAGMENT_GLSL

#version 150 core

#include "WGEShader-uniforms.glsl"

#include "WGEShadingTools.glsl"
#include "WGETextureTools.glsl"
#include "WGEPostprocessorUtils-fragment.glsl"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global Uniforms
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// These are NOT specific to any postprocessor

uniform float u_effectPreBlendScale = 1.0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Varying
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility functions.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Postprocessors
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WGE_POSTPROCESSOR_EDGE

/**
 * The threshold used to clip away "unwanted" borders. Basically removes noise
 */
uniform float u_edgeEdgeThresholdLower = 0.25;
uniform float u_edgeEdgeThresholdUpper = 0.75;

/**
 * Apply laplace-filter to depth buffer. An edge is > 0.0.
 *
 * \return the edge
 */
float getEdge()
{
    // TODO(ebaum): provide properties/uniforms for the scaling factors here

    /////////////////////////////////////////////////////////////////////////////////////////////
    // GETTING TEXELS
    //
    // Get surrounding texels; needed for ALL filters
    /////////////////////////////////////////////////////////////////////////////////////////////

    float edgec  = getDepth( pixelCoord );
    float edgebl = getDepth( pixelCoord + vec2( -offsetX, -offsetY ) );
    float edgel  = getDepth( pixelCoord + vec2( -offsetX,     0.0  ) );
    float edgetl = getDepth( pixelCoord + vec2( -offsetX,  offsetY ) );
    float edget  = getDepth( pixelCoord + vec2(     0.0,   offsetY ) );
    float edgetr = getDepth( pixelCoord + vec2(  offsetX,  offsetY ) );
    float edger  = getDepth( pixelCoord + vec2(  offsetX,     0.0  ) );
    float edgebr = getDepth( pixelCoord + vec2(  offsetX,  offsetY ) );
    float edgeb  = getDepth( pixelCoord + vec2(     0.0,  -offsetY ) );

    /////////////////////////////////////////////////////////////////////////////////////////////
    // LAPLACE
    //
    // apply a standart laplace filter kernel
    /////////////////////////////////////////////////////////////////////////////////////////////

    // laplace filter kernel
    float edge = 16.0 * abs(
            0.0 * edgetl +  1.0 * edget + 0.0 * edgetr +
            1.0 * edgel  +  -4.0 * edgec + 1.0 * edger  +
            0.0 * edgebl +  1.0 * edgeb + 0.0 * edgebr
        );

    return smoothstep( u_edgeEdgeThresholdLower, u_edgeEdgeThresholdUpper, edge );
}

#endif

#ifdef WGE_POSTPROCESSOR_CEL

/**
 * The number of bins to use for cel shading
 */
uniform int u_celShadingBins = 2;

/**
 * Calculate the cel-shading of a specified color. The number of colors is defined by the u_celShadingSamples uniform.
 *
 * \param inColor the color to shade
 *
 * \return the cel-shaded color
 */
vec4 getCelShading( vec4 inColor )
{
    float samples = float( u_celShadingBins );
    return vec4(
            vec3( int( ( inColor * samples ).r ),
                  int( ( inColor * samples ).g ),
                  int( ( inColor * samples ).b ) ) / samples, inColor.a );
}

/**
 * Calculate the cel-shading of the input color. The number of colors is defined by the u_celShadingSamples uniform.
 *
 * \return the cel-shaded color
 */
vec4 getCelShading()
{
    return getCelShading( getColor() );
}

#endif

#ifdef WGE_POSTPROCESSOR_HALFTONE


/**
 * Rotation angle in the dither matrix. Avoid 45, 90 degrees as they create horizontal, vertical or strictly diagonal patterns.
 */
uniform float u_ditherRotMatrixAngle = 30.0;

/**
 * Size of the dither mask.
 */
uniform float u_ditherTexSize = 4.0;

/**
 * Threshold to decide whether to paint the pixel or not.
 */
uniform float u_ditherCrossHatchThresh = 0.9;


uniform float u_ditherClip = 0.5;

/**
 * Hatch color. Play with transparency to achieve nice effects.
 */
uniform vec4 u_hatchColor = vec4( 0.1 );

/**
 * Apply the halftone hatching. Creates pencil-like effects.
 *
 * \param inColor input color
 * \param where location
 *
 * \return the shaded pixel
 */
vec4 getHalftoneShading( vec4 inColor, vec2 where )
{
    int edgeLod = 1;
    float edge = textureLod( u_texture6Sampler, where, edgeLod ).r;
    vec4 col = vec4( u_hatchColor.rgb, 1. - step( 0.75, pow( edge, 2. ) ) );

    // create the dither matrix.
    float ditherRotMatrixAngleRad = u_ditherRotMatrixAngle * 0.0174532925;
    mat2 ditherRotMatrix = mat2( vec2( -sin( ditherRotMatrixAngleRad ), cos( ditherRotMatrixAngleRad ) ),
                                 vec2(  cos( ditherRotMatrixAngleRad ), sin( ditherRotMatrixAngleRad ) ) );

    // calc diffuse light
    vec3 normal = getNormal( where ).xyz;
    vec3 lightDir = vec3( 0.0, 0.0, 1.0 );
    float fIntensity = max( 0.0, dot( lightDir, normalize( normal ) ) );

    // Transforming the fragment coordinates into halftoning texture coordinates:
    vec2 ditherTexCoord = ditherRotMatrix * gl_FragCoord.xy;

    ditherTexCoord = vec2( mod( ditherTexCoord.x, u_ditherTexSize ) / u_ditherTexSize,
                          mod( ditherTexCoord.y, u_ditherTexSize ) / u_ditherTexSize );

    // Dither kernel that generates the real halftoning texture.
    float ditherTau = mix( u_ditherCrossHatchThresh * ditherTexCoord.y,
                          ( 1.0 - u_ditherCrossHatchThresh ) * ditherTexCoord.x + u_ditherCrossHatchThresh,
                          step( u_ditherCrossHatchThresh, ditherTexCoord.x ) );

    // Depending on the lighting intensity and the halftoning texture value, a pixel is set or not.
    if( fIntensity >= ditherTau )
    {
        if( fIntensity > ( 1.0 - u_ditherClip ) )
        {
            col.a = 0.0;
        }
        else
        {
            col = vec4( u_hatchColor.rgb, 1.0 );
        }
    }
    else
    {
        //col.a=0.0;
    }

    return col;
}

/**
 * Apply the halftone hatching. Creates pencil-like effects.
 *
 * \param where location
 *
 * \return the shaded pixel
 */
vec4 getHalftoneShading( vec2 where )
{
    return getHalftoneShading( getColor(), where );
}

/**
 * Apply the halftone hatching. Creates pencil-like effects.
 *
 * \return the shaded pixel
 */
vec4 getHalftoneShading()
{
    return getHalftoneShading( getColor(), pixelCoord );
}

#endif

#ifdef WGE_POSTPROCESSOR_GAUSS

/**
 * Returns the gauss-smoothed color of the specified pixel from the input texture.
 *
 * \param where the pixel to grab
 * \param sampl the texture to gauss
 *
 * \return the color
 */
vec4 getGaussedColor( vec2 where, sampler2D sampl )
{
    // get the 8-neighbourhood
    vec4 gaussedColorc  = texture( sampl, where );
    vec4 gaussedColorbl = texture( sampl, where + vec2( -offsetX, -offsetY ) );
    vec4 gaussedColorl  = texture( sampl, where + vec2( -offsetX,     0.0  ) );
    vec4 gaussedColortl = texture( sampl, where + vec2( -offsetX,  offsetY ) );
    vec4 gaussedColort  = texture( sampl, where + vec2(     0.0,   offsetY ) );
    vec4 gaussedColortr = texture( sampl, where + vec2(  offsetX,  offsetY ) );
    vec4 gaussedColorr  = texture( sampl, where + vec2(  offsetX,     0.0  ) );
    vec4 gaussedColorbr = texture( sampl, where + vec2(  offsetX,  offsetY ) );
    vec4 gaussedColorb  = texture( sampl, where + vec2(     0.0,  -offsetY ) );

    // apply Gauss filter
    vec4 gaussed = ( 1.0 / 16.0 ) * (
            1.0 * gaussedColortl +  2.0 * gaussedColort + 1.0 * gaussedColortr +
            2.0 * gaussedColorl  +  4.0 * gaussedColorc + 2.0 * gaussedColorr  +
            1.0 * gaussedColorbl +  2.0 * gaussedColorb + 1.0 * gaussedColorbr );
    return gaussed;
}

/**
 * Returns the gauss-smoothed color of the current pixel from the input color texture.
 *
 * \param sampl the texture to gauss
 *
 * \return the color
 */
vec4 getGaussedColor( sampler2D sampl )
{
    return getGaussedColor( pixelCoord, sampl );
}

#endif

#ifdef WGE_POSTPROCESSOR_SSAO

#ifndef WGE_POSTPROCESSOR_SSAO_SAMPLES
    #define WGE_POSTPROCESSOR_SSAO_SAMPLES 16
#endif

/**
 * Overall effect strength. In (0,100]
 */
uniform float u_ssaoTotalStrength = 2.0;

/**
 * Strength of occlusion caused by one occluder. In (0,1]
 */
uniform float u_ssaoStrength = 1.0;

/**
 * Radius in screen-space. This value influences whether local or global effects influence the occlusion. In (0, 100];
 */
uniform float u_ssaoRadius = 10.0;

/**
 * Defines a falloff at which the depthDifference is assumed to be 0 (occluder is on same height)
 */
uniform float u_ssaoFalloff = 0.0;

/**
 * Calculate SSAO effect for the specified pixel. Requires a noise texture in u_noiseSampler. This implementation is taken from
 * http://www.gamerendering.com/2009/01/14/ssao/ and slightly modified. We added a small hack to provide scaling-invariance to the effect.
 *
 * \param where coordinate in screenspace
 * \param radius additional radius scaler.
 *
 * \return AO
 */
float getSSAO( vec2 where, float radius )
{
    float totStrength = u_ssaoTotalStrength;
    float strength = u_ssaoStrength;
    float falloff = u_ssaoFalloff;
    float rad = radius * u_ssaoRadius;

    #define SAMPLES WGE_POSTPROCESSOR_SSAO_SAMPLES
    const float invSamples = 1.0/ float( SAMPLES );

    // grab a normal for reflecting the sample rays later on
    vec3 fres = normalize( ( texture( u_noiseSampler, where * u_noiseSizeX ).xyz * 2.0 ) - vec3( 1.0 ) );
    vec4 currentPixelSample = getNormal( where );
    float currentPixelDepth = getDepth( where );
    float radiusSS = radius * ( getZoom() * u_ssaoRadius / float( u_texture0SizeX ) ) / ( 1.0 - currentPixelDepth );

    // current fragment coords in screen space
    vec3 ep = vec3( where.xy, currentPixelDepth );
    // get the normal of current fragment
    vec3 norm = currentPixelSample.xyz;

    float bl = 0.0;
    // adjust for the depth ( not shure if this is good..)
    float radD = rad/currentPixelDepth;

    vec3 ray, se;
    float occluderDepth, depthDifference, normDiff;

    for( int i = 0; i < SAMPLES; ++i )
    {
        // get a vector (randomized inside of a sphere with radius 1.0) from a texture and reflect it

        // grab a rand normal from the noise texture
        vec3 randSphereNormal = getNoiseAsVector( vec2( float( i ) / float( SAMPLES ), fres.y ) );
        ray =  radiusSS * reflect( randSphereNormal, fres );

        // if the ray is outside the hemisphere then change direction
        se = ep + sign( dot( ray, norm ) ) * ray;

        // get the depth of the occluder fragment
        vec4 occluderFragment = getNormal( se.xy );
        occluderFragment.a = getDepth( se.xy );

        // if depthDifference is negative = occluder is behind current fragment
        depthDifference = currentPixelDepth - occluderFragment.a;

        // calculate the difference between the normals as a weight
        normDiff = ( 1.0 - dot( occluderFragment.xyz, norm ) );
        // the falloff equation, starts at falloff and is kind of 1/x^2 falling
        bl += step( falloff, depthDifference ) * normDiff * ( 1.0 - smoothstep( falloff, strength, depthDifference ) );
    }

    // output the result
    return 1.0 - totStrength * bl * invSamples;
}

/**
 * Calculate the screen-space ambient occlusion from normal and depth map for the current pixel.
 *
 * \return the SSAO factor
 */
float getSSAO()
{
    return getSSAO( pixelCoord, 1.0 );
}

#endif

#ifdef WGE_POSTPROCESSOR_LINEAO

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This implements the LineAO algorithm from http://doi.ieeecomputersociety.org/10.1109/TVCG.2012.142
//
//  - This implementation matches the paper in most cases. We made some additional improvements and
//    simplifications here. This simply is due to the time-lag between first submission and final acceptance.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef WGE_POSTPROCESSOR_LINEAO_SAMPLES
    #define WGE_POSTPROCESSOR_LINEAO_SAMPLES 32
#endif
#ifndef WGE_POSTPROCESSOR_LINEAO_SCALERS
    #define WGE_POSTPROCESSOR_LINEAO_SCALERS 3
#endif

/**
 * The total influence of SSAO.
 */
uniform float u_lineaoTotalStrength = 1.0;     // Should be the same default as in WGEPostprocessorLineAO.cpp

/**
 * The radius of the hemispshere in screen-space which gets scaled.
 */
uniform float u_lineaoRadiusSS = 2.0;          // Should be the same default as in WGEPostprocessorLineAO.cpp

/**
 * The strength of the occluder influence in relation to the geometry density. The higher the value, the larger the influence. Low values remove
 * the drop-shadow effect.
 */
uniform float u_lineaoDensityWeight = 1.0;     // Should be the same default as in WGEPostprocessorLineAO.cpp

/**
 * Calculate the screen-space ambient occlusion LineAO for the given pixel.
 *
 * \param where the pixel to get SSAO for
 *
 * \return the LineAO factor
 */
float getLineAO( vec2 where )
{
    #define SCALERS WGE_POSTPROCESSOR_LINEAO_SCALERS  // how much hemispheres to sample?
    #define SAMPLES WGE_POSTPROCESSOR_LINEAO_SAMPLES  // the numbers of samples to check on the hemisphere
    const float invSamples = 1.0 / float( SAMPLES );

    // Fall-off for SSAO per occluder. This hould be zero (or nearly zero) since it defines what is counted as before, or behind.
    const float falloff = 0.00001;

    // grab a random normal for reflecting the sample rays later on
    vec3 randNormal = normalize( ( texture( u_noiseSampler, where * u_noiseSizeX ).xyz * 2.0 ) - vec3( 1.0 ) );

    // grab the current pixel's normal and depth
    vec3 currentPixelSample = getNormal( where ).xyz;
    float currentPixelDepth = getDepth( where );

    // current fragment coords in screen space
    vec3 ep = vec3( where.xy, currentPixelDepth );

    // get the normal of current fragment
    vec3 normal = currentPixelSample.xyz;

    // the radius of the sphere is, in screen-space, half a pixel. So the hemisphere covers nearly one pixel. Scaling by depth somehow makes it
    // more invariant for zooming
    float maxPixels = max( float( u_colorSizeX ), float( u_colorSizeY ) );
    float radius = ( getZoom() * u_lineaoRadiusSS / maxPixels ) / ( 1.0 - currentPixelDepth );

    // some temporaries needed inside the loop
    vec3 ray;                     // the current ray inside the sphere
    vec3 hemispherePoint;         // the point on the hemisphere
    vec3 occluderNormal;          // the normal at the point on the hemisphere

    float occluderDepth;          // the depth of the potential occluder on the hemisphere
    float depthDifference;        // the depth difference between the current point and the occluder (point on hemisphere)
    float normalDifference;       // the projection of the occluderNormal to the surface normal

    // accumulated occlusion
    float occlusion = 0.0;
    float radiusScaler = 0.0;     // we sample with multiple radii, so use a scaling factor here

    // sample for different radii
    for( int l = 0; l < SCALERS; ++l )
    {
        float occlusionStep = 0.0;  // this variable accumulates the occlusion for the current radius

        // this allows an adaptive radius
        // NOTE: we do not exactly use the linear scaling from the paper here. Although they look very similar, the non-linear radius, which
        // increases non-linearly with the level l, improves visual quality a bit. The drawback of this method is that increasing SCALERS causes
        // larger structures to become more important than local structures.
        #define radScaleMin 1.5
        radiusScaler += radScaleMin + l;
        // Alternatvie, linear way -- more coherent AO when changing the number of hemispheres:
        // radiusScaler = radScaleMin + l;    // increment radius each time.

        // Get SAMPLES-times samples on the hemisphere and check for occluders
        int numSamplesAdded = 0;    // used to count how many samples really got added to the occlusion term
        for( int i = 0; i < SAMPLES; ++i )
        {
            // grab a rand normal from the noise texture
            vec3 randSphereNormal = ( texture( u_noiseSampler, vec2( float( i ) / float( SAMPLES ),
                                                                       float( l + 1 ) / float( SCALERS ) ) ).rgb * 2.0 ) - vec3( 1.0 );

            // get a vector (randomized inside of a sphere with radius 1.0) from a texture and reflect it
            vec3 hemisphereVector = reflect( randSphereNormal, randNormal );
            ray = radiusScaler * radius * hemisphereVector;
            ray = sign( dot( ray, normal ) ) * ray;

            // get the point in texture space on the hemisphere
            hemispherePoint = ray + ep;

            // we need to handle the case where a hemisphere point is outside the texture space. The correct solution would be to ensure that
            // no hemisphere point ever gets outside the texture space. This can be achieved by rendering the scene to a larger texture and than
            // process only the required viewport in this texture. Unfortunately OpenWalnut does not provide an easy to use mechanism for this.
            // So, we skip hemispherePoints outside the texture. This yields nearly no or only small artifacts at the borders if zoomed in.
            if( ( hemispherePoint.x < 0.0 ) || ( hemispherePoint.x > 1.0 ) ||
                ( hemispherePoint.y < 0.0 ) || ( hemispherePoint.y > 1.0 )
              )
            {
                continue;
            }
            // Count the samples we really use.
            numSamplesAdded++;

            // use LOD based on current hemisphere?
            float lod = 0.0;
            #ifdef WGE_POSTPROCESSOR_LINEAO_USEGAUSSPYRAMID
            // select the Level in the gaussian pyramid of the normal, depth and tangent map. When NOT using this, you retain more local detail
            // at more far away occluders which creates crispier images.
            lod = float( l );
            #endif

            // get the depth of the occluder fragment
            occluderDepth = getDepth( hemispherePoint.xy, lod );

            // get the normal of the occluder fragment
            occluderNormal = getNormal( hemispherePoint.xy, lod ).xyz;

            // if depthDifference is negative = occluder is behind the current fragment -> occluding this fragment
            depthDifference = currentPixelDepth - occluderDepth;

            // calculate the difference between the normals as a weight. This weight determines how much the occluder occludes the fragment
            float pointDiffuse = max( dot( hemisphereVector, normal ), 0.0 ); // this equals the diffuse term in Phong if lightDir is the
                                                                              // occluder's surface

            // calculate the diffuse reflected light of the occluder, which might contribute to the current pixels brightness
            #ifdef WGE_POSTPROCESSOR_LINEAO_OCCLUDERLIGHT
            vec3 t = getTangent( hemispherePoint.xy, lod ).xyz;
            vec3 newnorm = normalize( cross( normalize( cross( t, normalize( hemisphereVector ) ) ), t ) );
            float occluderDiffuse = max( dot( newnorm, ow_lightsource.xyz ), 0.0 );
            #else
            // you can disable this effect.
            float occluderDiffuse = 0.0;
            #endif

            // incorporate specular reflection
            vec3 H = normalize( ow_lightsource.xyz + normalize( hemisphereVector ) );
            float occluderSpecular = pow( max( dot( H, occluderNormal ), 0.0 ), 100.0 );

            // this second is as proposed for AO, the omega (hemisphere vector) and surface normal
            normalDifference =  pointDiffuse * ( occluderSpecular + occluderDiffuse );
            normalDifference = 1.5 - normalDifference;  // we use 2 here as occluderSpecular + occluderDiffuse might get larger than 1

            // the higher the depth difference, the less it should influence the occlusion value since large space between geometry normally allows
            // many light. It somehow can be described with "shadowiness". In other words, it describes the density of geometry and its influence to
            // the occlusion.
            float scaler = 1.0 - ( l / ( float( SCALERS - 1 ) ) );
            float densityInfluence = scaler * scaler * u_lineaoDensityWeight;

            //  This reduces the occlusion if the occluder is far away
            float densityWeight = 1.0 - smoothstep( falloff, densityInfluence, depthDifference );
            // This is the same as:
            // float e0 = falloff;
            // float e1 = densityInfluence;
            // float r = ( depthDifference - e0 ) / ( e1 - e0 );
            // float densityWeight = 1.0 - smoothstep( 0.0, 1.0, r );

            // the following step function ensures that negative depthDifference values get clamped to 0, meaning that this occluder should have NO
            // influence on the occlusion value. A positive value (fragment is behind the occluder) increases the occlusion factor according to the
            // normal weight and density weight
            occlusionStep += normalDifference * densityWeight * step( falloff, depthDifference );
        }

        // for this radius, add to total occlusion. Keep in mind to normalize the occlusion term according to the number of samples taken
        occlusion += ( 1.0 / float( numSamplesAdded ) ) * occlusionStep;
    }

    // we need to take care when the number of hemispheres is increased. This is done indirectly by calculation of the densityInfluence variable.
    // But we need some additional scaling to keep the overall image intensity (overall energy) when changing the numbr of hemispheres.
    // This usually would be done by using 1/SCALERS.
    float occlusionScalerFactor = 1.0 / ( SCALERS );

    // also allow the user to modify the strength if he likes
    occlusionScalerFactor *= u_lineaoTotalStrength;

    // output the result
    return clamp( ( 1.0 - ( occlusionScalerFactor * occlusion ) ), 0, 1 );
}

/**
 * Calculate the screen-space ambient occlusion  LineAO for the current pixel.
 *
 * \return the LineAO factor
 */
float getLineAO()
{
    return getLineAO( pixelCoord );
}

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Main. Apply the specified post-processors.
 */
void main()
{
    // don't do this stuff for background pixel
    gl_FragData[0] = vec4( 1.0, 0.0, 0.0, 1.0 );

#ifdef WGE_POSTPROCESSOR_EDGE
    // output the depth and final color.
    #ifdef WGE_POSTPROCESSOR_OUTPUT_COMBINE

        // for black borders, multiply edge with color
        #ifdef WGE_POSTPROCESSOR_EDGE_BLACKEDGE
            #define EDGEOP * u_effectPreBlendScale * ( 1.0 - getEdge() )
        #else
            // for white borders, add
            #define EDGEOP + vec3( u_effectPreBlendScale * getEdge() )
        #endif

        // apply operation and output color
        gl_FragData[0] = vec4( getColor().rgb EDGEOP, 1.0 );
    #else
        // also do this for the effect-only output
        #ifdef WGE_POSTPROCESSOR_EDGE_BLACKEDGE
            #define EDGEOP 1.0 -
        #else
            // for white borders, add
            #define EDGEOP 0.0 +
        #endif
        gl_FragData[0] = vec4( vec3( EDGEOP getEdge() ), 1.0 );
    #endif
#endif

#ifdef WGE_POSTPROCESSOR_CEL
    // output the depth and final color.
    gl_FragData[0] = u_effectPreBlendScale * getCelShading();
#endif

#ifdef WGE_POSTPROCESSOR_HALFTONE
    #ifdef WGE_POSTPROCESSOR_OUTPUT_COMBINE
        // output the depth and final color.
        vec4 ht = getHalftoneShading();
        vec4 color = getColor();

        vec3 hatched = mix( color.rgb, ht.rgb, ht.a );

        gl_FragData[0] = vec4( u_effectPreBlendScale * hatched, color.a );
    #else
        // output the depth and final color.
        vec4 ht = getHalftoneShading();
        gl_FragData[0] = vec4( u_effectPreBlendScale * ht.rgb, ht.a );
    #endif
#endif

#ifdef WGE_POSTPROCESSOR_GAUSS
    // output the depth and final color.
    #ifdef WGE_POSTPROCESSOR_GAUSS_UNIT0
        gl_FragData[0] = getGaussedColor( pixelCoord, u_texture0Sampler );
    #endif
    #ifdef WGE_POSTPROCESSOR_GAUSS_UNIT1
        gl_FragData[1] = getGaussedColor( pixelCoord, u_texture1Sampler );
    #endif
    #ifdef WGE_POSTPROCESSOR_GAUSS_UNIT2
        gl_FragData[2] = getGaussedColor( pixelCoord, u_texture2Sampler );
    #endif
    #ifdef WGE_POSTPROCESSOR_GAUSS_UNIT3
        gl_FragData[3] = getGaussedColor( pixelCoord, u_texture3Sampler );
    #endif
    #ifdef WGE_POSTPROCESSOR_GAUSS_UNIT4
        gl_FragData[4] = getGaussedColor( pixelCoord, u_texture4Sampler );
    #endif
    #ifdef WGE_POSTPROCESSOR_GAUSS_UNIT5
        gl_FragData[5] = getGaussedColor( pixelCoord, u_texture5Sampler );
    #endif
    #ifdef WGE_POSTPROCESSOR_GAUSS_UNIT6
        gl_FragData[6] = getGaussedColor( pixelCoord, u_texture6Sampler );
    #endif
    #ifdef WGE_POSTPROCESSOR_GAUSS_UNIT7
        gl_FragData[7] = getGaussedColor( pixelCoord, u_texture7Sampler );
    #endif
#endif

#ifdef WGE_POSTPROCESSOR_MERGEOP
    // output the depth and final color.
    #ifdef WGE_POSTPROCESSOR_MERGEOP_CUSTOM
        vec4 color = vec4( 1.0 );
        %WGE_POSTPROCESSOR_MERGEOP_CODE%
        gl_FragData[0] = color;
    #else
        #ifdef WGE_POSTPROCESSOR_MERGEOP_UNIT0
            vec4 color = texture( u_texture0Sampler, pixelCoord );
        #endif
        #ifdef WGE_POSTPROCESSOR_MERGEOP_UNIT1
            color = mix( color, texture( u_texture1Sampler, pixelCoord ), 0.5 );
        #endif
        #ifdef WGE_POSTPROCESSOR_MERGEOP_UNIT2
            color = mix( color, texture( u_texture2Sampler, pixelCoord ), 0.5 );
        #endif
        #ifdef WGE_POSTPROCESSOR_MERGEOP_UNIT3
            color = mix( color, texture( u_texture3Sampler, pixelCoord ), 0.5 );
        #endif
        #ifdef WGE_POSTPROCESSOR_MERGEOP_UNIT4
            color = mix( color, texture( u_texture4Sampler, pixelCoord ), 0.5 );
        #endif
        #ifdef WGE_POSTPROCESSOR_MERGEOP_UNIT5
            color = mix( color, texture( u_texture5Sampler, pixelCoord ), 0.5 );
        #endif
        #ifdef WGE_POSTPROCESSOR_MERGEOP_UNIT6
            color = mix( color, texture( u_texture6Sampler, pixelCoord ), 0.5 );
        #endif
        #ifdef WGE_POSTPROCESSOR_MERGEOP_UNIT7
            color = mix( color, texture( u_texture7Sampler, pixelCoord ), 0.5 );
        #endif
        gl_FragData[0] = color;
    #endif
#endif

#ifdef WGE_POSTPROCESSOR_SSAO
    // output color AND SSAO?
    #ifdef WGE_POSTPROCESSOR_OUTPUT_COMBINE
        gl_FragData[0] = vec4( getColor().rgb * u_effectPreBlendScale * getSSAO(), 1.0 );
    #else
        gl_FragData[0] = vec4( vec3( u_effectPreBlendScale * getSSAO() ), 1.0 );
    #endif
#endif

#ifdef WGE_POSTPROCESSOR_LINEAO
    // output color AND SSAO?
    #ifdef WGE_POSTPROCESSOR_OUTPUT_COMBINE
        gl_FragData[0] = vec4( getColor().rgb * u_effectPreBlendScale * getLineAO(), 1.0 );
    #else
        gl_FragData[0] = vec4( vec3( u_effectPreBlendScale * getLineAO() ), 1.0 );
    #endif
#endif
}

#endif // WGEPOSTPROCESSOR_FRAGMENT_GLSL

