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

#include <vector>

#include "WColor.h"
#include "W2DTFMapper.h"
#include "WLogger.h"
#include "qtgui/controlPanel/transferFunction2D/WTransferFunction2DEnums.h"

W2DTFMapper::W2DTFMapper()
{
    // Viridis colorMap
    c_viridis.push_back( Step( 0.0, WColor( 0.267, 0.051, 0.33, 1.0 ) ) );
    c_viridis.push_back( Step( 0.25, WColor( 0.223, 0.336, 0.547, 1.0 ) ) );
    c_viridis.push_back( Step( 0.5, WColor( 0.121, 0.586, 0.543, 1.0 ) ) );
    c_viridis.push_back( Step( 0.75, WColor( 0.449, 0.813, 0.332, 1.0 ) ) );
    c_viridis.push_back( Step( 1.0, WColor( 0.992, 0.906, 0.145, 1.0 ) ) );

    c_inv_viridis.push_back( Step( 0.0, WColor( 0.992, 0.906, 0.145, 1.0 ) ) );
    c_inv_viridis.push_back( Step( 0.25, WColor( 0.449, 0.813, 0.332, 1.0 ) ) );
    c_inv_viridis.push_back( Step( 0.5, WColor( 0.121, 0.586, 0.543, 1.0 ) ) );
    c_inv_viridis.push_back( Step( 0.75, WColor( 0.223, 0.336, 0.547, 1.0 ) ) );
    c_inv_viridis.push_back( Step( 1.0, WColor( 0.267, 0.051, 0.33, 1.0 ) ) );

    // Decreasing Continuous OpacityMap
    o_decrease.push_back( Step( 0.0, WColor( 0.0, 0.0, 0.0, 1 ) ) );
    o_decrease.push_back( Step( 1.0, WColor( 0.0, 0.0, 0.0, 0.075 ) ) );

    o_increase.push_back( Step( 0.0, WColor( 0.0, 0.0, 0.0, 0.075 ) ) );
    o_increase.push_back( Step( 1.0, WColor( 0.0, 0.0, 0.0, 1.0 ) ) );

    // Green Yellow Red colorMap
    c_GYR.push_back( Step( 0.0, WColor( 0.0, 1.0, 0.0, 1.0 ) ) );
    c_GYR.push_back( Step( 0.5, WColor( 1.0, 0.5, 0.0, 1.0 ) ) );
    c_GYR.push_back( Step( 1.0, WColor( 1.0, 0.0, 0.0, 1.0 ) ) );

    c_inv_GYR.push_back( Step( 0.0, WColor( 1.0, 0.0, 0.0, 1.0 ) ) );
    c_inv_GYR.push_back( Step( 0.5, WColor( 1.0, 0.5, 0.0, 1.0 ) ) );
    c_inv_GYR.push_back( Step( 1.0, WColor( 0.0, 1.0, 0.0, 1.0 ) ) );

    // Black to White colorMap
    c_BWcont.push_back( Step( 0.0, WColor( 0.0, 0.0, 0.0, 1.0 ) ) );
    c_BWcont.push_back( Step( 1.0, WColor( 1.0, 1.0, 1.0, 1.0 ) ) );

    c_inv_BWcont.push_back( Step( 0.0, WColor( 1.0, 1.0, 1.0, 1.0 ) ) );
    c_inv_BWcont.push_back( Step( 1.0, WColor( 0.0, 0.0, 0.0, 1.0 ) ) );

    // Inferno Colormap
    c_inferno.push_back( Step( 0.0, WColor( 0.002, 0.005, 0.014, 1.0 ) ) );
    c_inferno.push_back( Step( 0.143, WColor( 0.159, 0.044, 0.329, 1.0 ) ) );
    c_inferno.push_back( Step( 0.286, WColor( 0.397, 0.083, 0.433, 1.0 ) ) );
    c_inferno.push_back( Step( 0.429, WColor( 0.623, 0.165, 0.388, 1.0 ) ) );
    c_inferno.push_back( Step( 0.571, WColor( 0.831, 0.283, 0.259, 1.0 ) ) );
    c_inferno.push_back( Step( 0.714, WColor( 0.962, 0.490, 0.084, 1.0 ) ) );
    c_inferno.push_back( Step( 0.857, WColor( 0.982, 0.756, 0.153, 1.0 ) ) );
    c_inferno.push_back( Step( 1.0, WColor( 0.988, 0.998, 0.645, 1.0 ) ) );

    c_inv_inferno.push_back( Step( 0.0, WColor( 0.988, 0.998, 0.645, 1.0 ) ) );
    c_inv_inferno.push_back( Step( 0.143, WColor( 0.982, 0.756, 0.153, 1.0 ) ) );
    c_inv_inferno.push_back( Step( 0.286, WColor( 0.962, 0.490, 0.084, 1.0 ) ) );
    c_inv_inferno.push_back( Step( 0.429, WColor( 0.831, 0.283, 0.259, 1.0 ) ) );
    c_inv_inferno.push_back( Step( 0.571, WColor( 0.623, 0.165, 0.388, 1.0 ) ) );
    c_inv_inferno.push_back( Step( 0.714, WColor( 0.397, 0.083, 0.433, 1.0 ) ) );
    c_inv_inferno.push_back( Step( 0.857, WColor( 0.159, 0.044, 0.329, 1.0 ) ) );
    c_inv_inferno.push_back( Step( 1.0, WColor( 0.002, 0.005, 0.014, 1.0 ) ) );

    // RedBlue Colormap
    c_redblue.push_back( Step( 0.0, WColor( 0.667, 0.0, 0.0, 1.0 ) ) );
    c_redblue.push_back( Step( 0.25, WColor( 0.833, 0.5, 0.5, 1.0 ) ) );
    c_redblue.push_back( Step( 0.5, WColor( 1.0, 1.0, 1.0, 1.0 ) ) );
    c_redblue.push_back( Step( 0.75, WColor( 0.5, 0.5, 0.833, 1.0 ) ) );
    c_redblue.push_back( Step( 1.0, WColor( 0.0, 0.0, 0.667, 1.0 ) ) );

    c_inv_redblue.push_back( Step( 0.0, WColor( 0.0, 0.0, 0.667, 1.0 ) ) );
    c_inv_redblue.push_back( Step( 0.25, WColor( 0.5, 0.5, 0.833, 1.0 ) ) );
    c_inv_redblue.push_back( Step( 0.5, WColor( 1.0, 1.0, 1.0, 1.0 ) ) );
    c_inv_redblue.push_back( Step( 0.75, WColor( 0.833, 0.5, 0.5, 1.0 ) ) );
    c_inv_redblue.push_back( Step( 1.0, WColor( 0.667, 0.0, 0.0, 1.0 ) ) );


    // Twilight Colormap
    c_twilight.push_back( Step( 0.0, WColor( 0.745, 0.714, 0.745, 1.0 ) ) );
    c_twilight.push_back( Step( 0.25, WColor( 0.271, 0.353, 0.604, 1.0 ) ) );
    c_twilight.push_back( Step( 0.5, WColor( 0.086, 0.0, 0.118, 1.0 ) ) );
    c_twilight.push_back( Step( 0.75, WColor( 0.567, 0.224, 0.208, 1.0 ) ) );
    c_twilight.push_back( Step( 1.0, WColor( 0.745, 0.714, 0.745, 1.0 ) ) );

    c_inv_twilight.push_back( Step( 0.0, WColor( 0.745, 0.714, 0.745, 1.0 ) ) );
    c_inv_twilight.push_back( Step( 0.25, WColor( 0.567, 0.224, 0.208, 1.0 ) ) );
    c_inv_twilight.push_back( Step( 0.5, WColor( 0.086, 0.0, 0.118, 1.0 ) ) );
    c_inv_twilight.push_back( Step( 0.75, WColor( 0.271, 0.353, 0.604, 1.0 ) ) );
    c_inv_twilight.push_back( Step( 1.0, WColor( 0.745, 0.714, 0.745, 1.0 ) ) );
}


W2DTFMapper::~W2DTFMapper()
{
}

WColor W2DTFMapper::getColorForWidget( std::vector<MapType> mapsFirst, std::vector<MapType> mapsSecond, int posX, int posY, int maxX, int maxY,
                                        int minX, int minY, WColor current ) const
{
    //TODO(T.Neeb): Refactor/Split this method into multiple parts/methods to improve overview and structure
    WColor m_mappedColor = WColor();
    WColor m_colorDS1 = WColor();
    WColor m_colorDS2 = WColor();
    bool opacitySetDS1 = false, colorSetDS1 = false;
    bool opacitySetDS2 = false, colorSetDS2 = false;
    float fposX = static_cast<float>( posX );
    float fposY = static_cast<float>( posY );
    float fmaxX = static_cast<float>( maxX );
    float fmaxY = static_cast<float>( maxY );
    float fminX = static_cast<float>( minX );
    float fminY = static_cast<float>( minY );

    float scalarValue = ( fposX - fminX ) / ( fmaxX - fminX );
    for( size_t i = 0; i < mapsFirst.size(); i++ )
    {
        switch( mapsFirst[i] )
        {
            case O_DECREASE_CONT:
                m_colorDS1 += calculateColorForMap( o_decrease, scalarValue, o_decrease.size(), fposX, fmaxX, true );
                opacitySetDS1 = true;
                break;
            case O_INCREASE_CONT:
                m_colorDS1 += calculateColorForMap( o_increase, scalarValue, o_decrease.size(), fposX, fmaxX, true );
                opacitySetDS1 = true;
                break;
            case C_VIRIDIS:
                m_colorDS1 += calculateColorForMap( c_viridis, scalarValue, c_viridis.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_GYR_CONT:
                m_colorDS1 += calculateColorForMap( c_GYR, scalarValue, c_GYR.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_BW_CONT:
                m_colorDS1 += calculateColorForMap( c_BWcont, scalarValue, c_BWcont.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_INFERNO:
                m_colorDS1 += calculateColorForMap( c_inferno, scalarValue, c_inferno.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_REDBLUE:
                m_colorDS1 += calculateColorForMap( c_redblue, scalarValue, c_redblue.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_TWILIGHT:
                m_colorDS1 += calculateColorForMap( c_twilight, scalarValue, c_twilight.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_CONST_BLUE:
                m_colorDS1 += defaultColor::BLUE;
                colorSetDS1 += true;
                break;
            case C_CONST_RED:
                m_colorDS1 += defaultColor::RED;
                colorSetDS1 = true;
                break;
            case C_CONST_GREEN:
                m_colorDS1 += defaultColor::GREEN;
                colorSetDS1 = true;
                break;
            case C_INV_VIRIDIS:
                m_colorDS1 += calculateColorForMap( c_inv_viridis, scalarValue, c_viridis.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_INV_BW_CONT:
                m_colorDS1 += calculateColorForMap( c_inv_BWcont, scalarValue, c_BWcont.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_INV_GYR_CONT:
                m_colorDS1 += calculateColorForMap( c_inv_GYR, scalarValue, c_GYR.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_INV_INFERNO:
                m_colorDS1 += calculateColorForMap( c_inv_inferno, scalarValue, c_inferno.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_INV_REDBLUE:
                m_colorDS1 += calculateColorForMap( c_inv_redblue, scalarValue, c_redblue.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            case C_INV_TWILIGHT:
                m_colorDS1 += calculateColorForMap( c_inv_twilight, scalarValue, c_twilight.size(), fposX, fmaxX, false );
                colorSetDS1 = true;
                break;
            default:
                break;
        }
    }
    scalarValue = ( fposY - fminY ) / ( fmaxY - fminY );
    for( size_t i = 0; i < mapsSecond.size(); i++ )
    {
        switch( mapsSecond[i] )
        {
            case O_DECREASE_CONT:
                m_colorDS2 += calculateColorForMap( o_decrease, scalarValue, o_decrease.size(), fposY, fmaxY, true );
                opacitySetDS2 = true;
                break;
            case O_INCREASE_CONT:
                m_colorDS2 += calculateColorForMap( o_increase, scalarValue, o_decrease.size(), fposY, fmaxY, true );
                opacitySetDS2 = true;
                break;
            case C_VIRIDIS:
                m_colorDS2 += calculateColorForMap( c_viridis, scalarValue, c_viridis.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_GYR_CONT:
                m_colorDS2 += calculateColorForMap( c_GYR, scalarValue, c_GYR.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_BW_CONT:
                m_colorDS2 += calculateColorForMap( c_BWcont, scalarValue, c_BWcont.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_INFERNO:
                m_colorDS2 += calculateColorForMap( c_inferno, scalarValue, c_inferno.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_REDBLUE:
                m_colorDS2 += calculateColorForMap( c_redblue, scalarValue, c_redblue.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_TWILIGHT:
                m_colorDS2 += calculateColorForMap( c_twilight, scalarValue, c_twilight.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_CONST_BLUE:
                m_colorDS2 += defaultColor::BLUE;
                colorSetDS2 += true;
                break;
            case C_CONST_RED:
                m_colorDS2 += defaultColor::RED;
                colorSetDS2 = true;
                break;
            case C_CONST_GREEN:
                m_colorDS2 += defaultColor::GREEN;
                colorSetDS2 = true;
                break;
            case C_INV_VIRIDIS:
                m_colorDS2 += calculateColorForMap( c_inv_viridis, scalarValue, c_viridis.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_INV_BW_CONT:
                m_colorDS2 += calculateColorForMap( c_inv_BWcont, scalarValue, c_BWcont.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_INV_GYR_CONT:
                m_colorDS2 += calculateColorForMap( c_inv_GYR, scalarValue, c_GYR.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_INV_INFERNO:
                m_colorDS2 += calculateColorForMap( c_inv_inferno, scalarValue, c_inferno.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_INV_REDBLUE:
                m_colorDS2 += calculateColorForMap( c_inv_redblue, scalarValue, c_redblue.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            case C_INV_TWILIGHT:
                m_colorDS2 += calculateColorForMap( c_inv_twilight, scalarValue, c_twilight.size(), fposY, fmaxY, false );
                colorSetDS2 = true;
                break;
            default:
                break;
        }
    }
    //TODO(T.Neeb): Refactor this including the blendColors()-Method
    if( opacitySetDS2 && opacitySetDS1 && colorSetDS2 && colorSetDS1 )
    {
        m_mappedColor = blendColors( m_colorDS1, m_colorDS2, false, false );
        return m_mappedColor;
    }
    if( !opacitySetDS2 && opacitySetDS1 && colorSetDS2 && colorSetDS1 )
    {
        m_mappedColor = blendColors( m_colorDS1, m_colorDS2, true, true );
        return m_mappedColor;
    }
    if( opacitySetDS2 && !opacitySetDS1 && colorSetDS2 && colorSetDS1 )
    {
        m_mappedColor = blendColors( m_colorDS1, m_colorDS2, true, false );
        return m_mappedColor;
    }
    if( !opacitySetDS2 && !opacitySetDS1 && colorSetDS2 && colorSetDS1 )
    {
        WColor blend = blendColors( m_colorDS1, m_colorDS2, true, true );
        m_mappedColor = WColor( blend.r(), blend.g(), blend.b(), current.a() );
        return m_mappedColor;
    }
    if( opacitySetDS2 && opacitySetDS1 && colorSetDS2 && !colorSetDS1 )
    {
        m_mappedColor = blendColors( m_colorDS2, m_colorDS2, false, false );
        return m_mappedColor;
    }
    if( opacitySetDS2 && !opacitySetDS1 && colorSetDS2 && !colorSetDS1 )
    {
        m_mappedColor = m_colorDS2;
        return m_mappedColor;
    }
    if( !opacitySetDS2 && opacitySetDS1 && colorSetDS2 && !colorSetDS1 )
    {
        m_colorDS1 = WColor( m_colorDS2.r(), m_colorDS2.g(), m_colorDS2.b(), m_colorDS1.a() );
        m_mappedColor = blendColors( m_colorDS1, m_colorDS2, true, true );
        return m_mappedColor;
    }
    if( !opacitySetDS2 && !opacitySetDS1 && colorSetDS2 && !colorSetDS1 )
    {
        m_mappedColor = WColor( m_colorDS2.r(), m_colorDS2.g(), m_colorDS2.b(), current.a() );
        return m_mappedColor;
    }
    if( opacitySetDS2 && opacitySetDS1 && !colorSetDS2 && colorSetDS1 )
    {
        m_mappedColor = blendColors( m_colorDS1, m_colorDS1, false, false );
        return m_mappedColor;
    }
    if( opacitySetDS2 && !opacitySetDS1 && !colorSetDS2 && colorSetDS1 )
    {
        m_colorDS2 = WColor( m_colorDS1.r(), m_colorDS1.g(), m_colorDS1.b(), m_colorDS2.a() );
        m_mappedColor = blendColors( m_colorDS1, m_colorDS2, false, false );
        return m_mappedColor;
    }
    if( !opacitySetDS2 && opacitySetDS1 && !colorSetDS2 && colorSetDS1 )
    {
        m_mappedColor = m_colorDS1;
        return m_mappedColor;
    }
    if( !opacitySetDS2 && !opacitySetDS1 && !colorSetDS2 && colorSetDS1 )
    {
        m_mappedColor = WColor( m_colorDS1.r(), m_colorDS1.g(), m_colorDS1.b(), current.a() );
        return m_mappedColor;
    }
    if( opacitySetDS2 && opacitySetDS1 && !colorSetDS2 && !colorSetDS1 )
    {
        m_mappedColor = WColor( current.r(), current.g(), current.b(), 0.5 * m_colorDS1.a() + 0.5 * m_colorDS2.a() );
        return m_mappedColor;
    }
    if( opacitySetDS2 && !opacitySetDS1 && !colorSetDS2 && !colorSetDS1 )
    {
        m_mappedColor = WColor( current.r(), current.g(), current.b(), m_colorDS2.a() );
        return m_mappedColor;
    }
    if( !opacitySetDS2 && opacitySetDS1 && !colorSetDS2 && !colorSetDS1 )
    {
        m_mappedColor = WColor( current.r(), current.g(), current.b(), m_colorDS1.a() );
        return m_mappedColor;
    }
    if( !opacitySetDS2 && !opacitySetDS1 && !colorSetDS2 && !colorSetDS1 )
    {
        m_mappedColor = WColor( current.r(), current.g(), current.b(), current.a() );
        return m_mappedColor;
    }
    return m_mappedColor;
}

WColor W2DTFMapper::interpolate( WColor first, WColor second, float weight, bool isColorMap ) const
{
    if( isColorMap )
    {
        float ir, ig, ib;
        ir = ( weight * second.r() + ( 1.0 - weight ) * first.r() );
        ig = ( weight * second.g() + ( 1.0 - weight ) * first.g() );
        ib = ( weight * second.b() + ( 1.0 - weight ) * first.b() );
        return WColor( ir, ig, ib, 0.0 );
    }
    else
    {
        float ia;
        ia = ( weight * second.a() + ( 1.0 - weight ) * first.a() );
        return WColor( 0.0, 0.0, 0.0, ia );
    }
}

WColor W2DTFMapper::blendColors( WColor first, WColor second, bool onlyColor, bool firstOpacity ) const
{
    float br, bg, bb;
    if( onlyColor )
    {
        br = 0.5 * first.r() + 0.5 * second.r();
        bg = 0.5 * first.g() + 0.5 * second.g();
        bb = 0.5 * first.b() + 0.5 * second.b();
        if( firstOpacity )
        {
            return WColor( br, bg, bb, first.a() );
        }
        else
        {
            return WColor( br, bg, bb, second.a() );
        }
    }
    else
    {
        float ba;
        br = 0.5 * first.r() + 0.5 * second.r();
        bg = 0.5 * first.g() + 0.5 * second.g();
        bb = 0.5 * first.b() + 0.5 * second.b();
        ba = 0.5 * first.a() + 0.5 * second.a();

        return WColor( br, bg, bb, ba );
    }
}

WColor W2DTFMapper::calculateColorForMap( std::vector<Step> map, float scalarValue, int mapSteps, [[maybe_unused]]float pos, float max,
                                            bool isOpacity ) const
{
    WColor calcColor = WColor();
    for( int i = 0; i < mapSteps-1; i++ )
    {
        if( map[i].value <= scalarValue && scalarValue < map[i+1].value )
        {
            float weight = ( max * scalarValue - map[i].value * max ) / ( map[i+1].value * max - map[i].value * max );
            if( !isOpacity )
            {
                calcColor += interpolate( map[i].color, map[i+1].color, weight, true );
            }
            else
            {
                calcColor += interpolate( map[i].color, map[i+1].color, weight, false );
            }
        }
    }
    return calcColor;
}

std::vector<W2DTFMapper::Step> W2DTFMapper::getMap( MapType map )
{
    switch( map )
    {
        case O_DECREASE_CONT:
            return o_decrease;
            break;
        case O_INCREASE_CONT:
            return o_increase;
            break;
        case C_VIRIDIS:
            return c_viridis;
            break;
        case C_GYR_CONT:
            return c_GYR;
            break;
        case C_BW_CONT:
            return c_BWcont;
            break;
        case C_INFERNO:
            return c_inferno;
            break;
        case C_REDBLUE:
            return c_redblue;
            break;
        case C_TWILIGHT:
            return c_twilight;
            break;
        case C_CONST_BLUE:
        {
            std::vector<Step> blue;
            blue.push_back( Step( 0.0, WColor( 0.0, 0.0, 1.0, 1.0 ) ) );
            blue.push_back( Step( 1.0, WColor( 0.0, 0.0, 1.0, 1.0 ) ) );
            return blue;
            break;
        }
        case C_CONST_RED:
        {
            std::vector<Step> red;
            red.push_back( Step( 0.0, WColor( 0.0, 0.0, 1.0, 1.0 ) ) );
            red.push_back( Step( 1.0, WColor( 0.0, 0.0, 1.0, 1.0 ) ) );
            return red;
            break;
        }
        case C_CONST_GREEN:
        {
            std::vector<Step> green;
            green.push_back( Step( 0.0, WColor( 0.0, 0.0, 1.0, 1.0 ) ) );
            green.push_back( Step( 1.0, WColor( 0.0, 0.0, 1.0, 1.0 ) ) );
            return green;
            break;
        }
        case C_INV_VIRIDIS:
            return c_inv_viridis;
            break;
        case C_INV_BW_CONT:
            return c_inv_BWcont;
            break;
        case C_INV_GYR_CONT:
            return c_inv_GYR;
            break;
        case C_INV_INFERNO:
            return c_inv_inferno;
            break;
        case C_INV_REDBLUE:
            return c_inv_redblue;
            break;
        case C_INV_TWILIGHT:
            return c_inv_twilight;
            break;
        default:
            return c_viridis;
            break;
    }
}
