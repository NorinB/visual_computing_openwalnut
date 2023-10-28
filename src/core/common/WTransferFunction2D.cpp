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

#include <cmath>
#include <iostream>
#include <vector>


#include "WAssert.h"
#include "WTransferFunction2D.h"
#include "W2DTFMapper.h"
#include "WLogger.h"
#include "core/kernel/WKernel.h"

void WTransferFunction2D::sample2DTransferFunction( unsigned char*array, int width, int height ) const
{
    WColor color;
    std::vector<bool> colorSet = std::vector<bool>( width * height * 4 );
    for( int i = 0; i < width * height * 4; i++ )
    {
        colorSet[i] = false;
    }
    // Iterate over widgets and write the color in the "texture" (array) in normalized space
    if( m_widgets.size() >= 1 )
    {
        for( auto const &w : m_widgets )
        {
            color = w.color;
            int xMin = static_cast<int>( w.scalarPosX * width );
            int xMax = static_cast<int>( ( w.scalarPosX + w.width ) * width );
            int yMin = static_cast<int>( w.scalarPosY * height );
            int yMax = static_cast<int>( ( w.scalarPosY + w.height ) * height );
            int anchorX = static_cast<int>( w.xAnchor * width );
            int anchorY = static_cast<int>( w.yAnchor * height );
            int minAnchorX = static_cast<int>( w.xMinAnchor * width );
            int minAnchorY = static_cast<int>( w.yMinAnchor * height );
            switch( w.entryShape )
            {
                case BOX:
                {
                    for( int x = xMin; x < xMax; ++x )
                    {
                        for( int y = yMin; y < yMax; ++y )
                        {
                            WColor mapColor;
                            if( w.localMapping )
                            {
                                mapColor = m_mapper.getColorForWidget( w.mapsFirst, w.mapsSecond, x, y, anchorX, anchorY,
                                                                        minAnchorX, minAnchorY, color );
                            }
                            else
                            {
                                mapColor = m_mapper.getColorForWidget( w.mapsFirst, w.mapsSecond, x, y, width, height, 0, 0, color );
                            }
                            for( int j = 0; j < 3; ++j )
                            {
                                if( w.mapsFirst.size() < 1 && w.mapsSecond.size() < 1 )
                                {
                                    array[4 * width * x + 4 * y + j] = color[j] * 255.0;
                                    array[4 * width * x + 4 * y + 3] = color[3] * 255.0 * m_opacityScale;
                                }
                                else
                                {
                                    array[4 * width * x + 4 * y + j] = mapColor[j] * 255.0;
                                    array[4 * width * x + 4 * y + 3] = mapColor[3] * 255.0 * m_opacityScale;
                                }
                            }
                        }
                    }
                    break;
                }
                case TRIANGLE:
                {
                    for( int x = xMin; x < xMax; ++x )
                    {
                        for( int y = yMin; y < yMax; ++y )
                        {
                            if( isPointInTriangle( w.points, WidgetPoint( x * 300.0 / width, y * 300.0 / height ) ) )
                            {
                                WColor mapColor;
                                if( w.localMapping )
                                {
                                    mapColor = m_mapper.getColorForWidget( w.mapsFirst, w.mapsSecond, x, y, anchorX, anchorY,
                                                                        minAnchorX, minAnchorY, color );
                                }
                                else
                                {
                                    mapColor = m_mapper.getColorForWidget( w.mapsFirst, w.mapsSecond, x, y, width, height, 0, 0, color );
                                }
                                for( int j = 0; j < 3; ++j )
                                {
                                    if( w.mapsFirst.size() < 1 && w.mapsSecond.size() < 1 )
                                    {
                                        array[4 * width * x + 4 * y + j] = color[j] * 255.0;
                                        array[4 * width * x + 4 * y + 3] = color[3] * 255.0 * m_opacityScale;
                                    }
                                    else
                                    {
                                        array[4 * width * x + 4 * y + j] = mapColor[j] * 255.0;
                                        array[4 * width * x + 4 * y + 3] = mapColor[3] * 255.0 * m_opacityScale;
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                case QUADRANGLE:
                {
                    for( int x = xMin; x < xMax; ++x )
                    {
                        for( int y = yMin; y < yMax; ++y )
                        {
                            if( isPointInQuadrangle( w.points, WidgetPoint( x * 300.0 / width, y * 300.0 / height ), WidgetPoint( xMin, yMin ),
                                                                                                                     WidgetPoint( xMax, yMax ) ) )
                            {
                                for( int j = 0; j < 3; ++j )
                                {
                                    if( colorSet[4 * width * x + 4 * y + j] == false )
                                    {
                                        array[4 * width * x + 4 * y + j] = color[j] * 255.0;
                                        array[4 * width * x + 4 * y + 3] = color[3] * 255. * m_opacityScale;
                                        colorSet[4 * width * x + 4 * y + j] = true;
                                    }
                                    else
                                    {
                                        array[4 * width * x + 4 * y + j] = ( ( 0.5 * static_cast<double>( array[4 * width * x + 4 * y + j] )
                                                                            / 255.0 ) + 0.5 * color[j] ) * 255.0;
                                        array[4 * width * x + 4 * y + 3] = ( ( 0.5 * static_cast<double>( array[4 * width * x + 4 * y + 3] )
                                                                            / 255.0 ) + 0.5 * color[3] )* 255.0 * m_opacityScale;
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                case ELLIPSIS:
                {
                    for( int x = xMin; x < xMax; ++x )
                    {
                        for( int y = yMin; y < yMax; ++y )
                        {
                            if( isPointInEllipsis( w.points, WidgetPoint( x * 300.0 / width, y * 300.0 / height ) ) )
                            {
                                for( int j = 0; j < 3; ++j )
                                {
                                    if( colorSet[4 * width * x + 4 * y + j] == false )
                                    {
                                        array[4 * width * x + 4 * y + j] = color[j] * 255.0;
                                        array[4 * width * x + 4 * y + 3] = color[3] * 255. * m_opacityScale;
                                        colorSet[4 * width * x + 4 * y + j] = true;
                                    }
                                    else
                                    {
                                        array[4 * width * x + 4 * y + j] = ( ( 0.5 * static_cast<double>( array[4 * width * x + 4 * y + j] )
                                                                            / 255.0 ) + 0.5 * color[j] ) * 255.0;
                                        array[4 * width * x + 4 * y + 3] = ( ( 0.5 * static_cast<double>( array[4 * width * x + 4 * y + 3] )
                                                                            / 255.0 ) + 0.5 * color[3] )* 255.0 * m_opacityScale;
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
}

bool WTransferFunction2D::isPointInTriangle( const std::vector<WidgetPoint> trianglePoints, WidgetPoint point ) const
{
    float m1, m2, m3;
    WidgetPoint p, p1, p2, p3;
    p = point;
    p1 = trianglePoints[0];
    p2 = trianglePoints[1];
    p3 = trianglePoints[2];

    m1 = ( ( p2.y - p3.y ) * ( p.x - p3.x ) + ( p3.x - p2.x ) * ( p.y - p3.y ) ) /
         ( ( p2.y - p3.y ) * ( p1.x - p3.x ) + ( p3.x - p2.x ) * ( p1.y - p3.y ) );

    m2 = ( ( p3.y - p1.y ) * ( p.x - p3.x ) + ( p1.x - p3.x ) * ( p.y - p3.y ) ) /
         ( ( p2.y - p3.y ) * ( p1.x - p3.x ) + ( p3.x - p2.x ) * ( p1.y - p3.y ) );

    m3 = 1.0f - m1 - m2;

    if( m1 > 0 && m2 > 0 && m3 > 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool WTransferFunction2D::isPointInQuadrangle( const std::vector<WidgetPoint> quadranglePoints, WidgetPoint point, WidgetPoint min,
                                               WidgetPoint max ) const
{
    WidgetPoint a, b, c, d, p, crossX, crossY;
    p = point;
    a = quadranglePoints[0];
    b = quadranglePoints[1];
    c = quadranglePoints[2];
    d = quadranglePoints[3];

    crossY = getLineIntersection( a, d, b, c );
    crossX = getLineIntersection( a, b, c, d );

    if( crossY.x != -1 )
    {
        if( crossY.x < min.x || crossY.x > max.x || crossY.y < min.y || crossY.y > max.y )
        {
            std::vector<WidgetPoint> triangleA;
            triangleA.push_back( crossY );
            triangleA.push_back( b );
            triangleA.push_back( a );

            std::vector<WidgetPoint> triangleB;
            triangleB.push_back( crossY );
            triangleB.push_back( d );
            triangleB.push_back( c );

            if( isPointInTriangle( triangleA, point ) || isPointInTriangle( triangleB, point ) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else if( crossX.x != -1 )
    {
        if( crossX.x < min.x || crossX.x > max.x || crossX.y < min.y || crossX.y > max.y )
        {
            std::vector<WidgetPoint> triangleA;
            triangleA.push_back( crossX );
            triangleA.push_back( d );
            triangleA.push_back( a );

            std::vector<WidgetPoint> triangleB;
            triangleB.push_back( crossX );
            triangleB.push_back( b );
            triangleB.push_back( c );

            if( isPointInTriangle( triangleA, point ) || isPointInTriangle( triangleB, point ) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        float diagLengthAC = sqrt( pow( c.x - a.x, 2 ) + pow( c.y - a.y, 2 ) * 1.0 );
        float diagLengthBD = sqrt( pow( d.x - b.x, 2 ) + pow( d.y - b.y, 2 ) * 1.0 );
        if( diagLengthAC < diagLengthBD )
        {
            std::vector<WidgetPoint> triangleA;
            triangleA.push_back( a );
            triangleA.push_back( b );
            triangleA.push_back( c );

            std::vector<WidgetPoint> triangleB;
            triangleB.push_back( a );
            triangleB.push_back( d );
            triangleB.push_back( c );

            if( isPointInTriangle( triangleA, point ) || isPointInTriangle( triangleB, point ) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            std::vector<WidgetPoint> triangleA;
            triangleA.push_back( d );
            triangleA.push_back( a );
            triangleA.push_back( b );

            std::vector<WidgetPoint> triangleB;
            triangleB.push_back( b );
            triangleB.push_back( c );
            triangleB.push_back( d );

            if( isPointInTriangle( triangleA, point ) || isPointInTriangle( triangleB, point ) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

WTransferFunction2D::WidgetPoint WTransferFunction2D::getLineIntersection( WidgetPoint pointA, WidgetPoint pointB, WidgetPoint pointC,
                                                                           WidgetPoint pointD ) const
{
    float lineAB[3];
    lineAB[0] = pointB.y - pointA.y;
    lineAB[1] = pointA.x - pointB.x;
    lineAB[2] = lineAB[0] * pointA.x + lineAB[1] * pointA.y;

    float lineCD[3];
    lineCD[0] = pointD.y - pointC.y;
    lineCD[1] = pointC.x - pointD.x;
    lineCD[2] = lineCD[0] * pointC.x + lineCD[1] * pointC.y;

    float determinant = lineAB[0] * lineCD[1] - lineAB[1] * lineCD[0];

    if( determinant == 0 )
    {
        return WidgetPoint( -1, -1 );
    }
    else
    {
        float x = ( lineCD[1] * lineAB[2] - lineAB[1] * lineCD[2] ) / determinant;
        float y = ( lineAB[0] * lineCD[2] - lineCD[0] * lineAB[2] ) / determinant;
        return WidgetPoint( x, y );
    }
}


bool WTransferFunction2D::isPointInEllipsis( const std::vector<WidgetPoint> ellipsisPoints, WidgetPoint point ) const
{
    WidgetPoint a, b, c, d, p, centre;
    p = point;
    a = ellipsisPoints[0];
    b = ellipsisPoints[1];
    c = ellipsisPoints[2];
    d = ellipsisPoints[3];

    centre = WidgetPoint( ( a.x + c.x ) / 2, ( a.y + c.y ) / 2 );

    float rx = centre.x - a.x;
    float ry = centre.y - a.y;

    if( ( pow( point.x - centre.x, 2 ) / pow( rx, 2 ) + pow( point.y - centre.y, 2 ) / pow( ry, 2 ) ) <= 1 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool WTransferFunction2D::operator==( const WTransferFunction2D &rhs ) const
{
    if( m_histogram != rhs.m_histogram )
    {
        return false;
    }
    if( m_widgets.size() != rhs.m_widgets.size() )
    {
        return false;
    }

    std::vector<WidgetEntry>::const_iterator it1 = m_widgets.begin();
    std::vector<WidgetEntry>::const_iterator it2 = rhs.m_widgets.begin();

    for( ;
         it1 != m_widgets.end();
         ++it1, ++it2 )
    {
        if( !( *it1 == *it2 ) )
        {
            return false;
        }
    }
    return true;
}

bool WTransferFunction2D::operator!=( const WTransferFunction2D &rhs ) const
{
    return !( ( *this ) == rhs );
}

void WTransferFunction2D::setHistogram( const std::shared_ptr< WHistogram2D >& histogram )
{
    if( m_histogram != histogram )
    {
        m_histogram = histogram;
    }
}

void WTransferFunction2D::addWidget( Shapes shape, WidgetPoint points[], std::vector<MapType> mapsA, std::vector<MapType> mapsB, bool mapping,
                                    double anchorX, double anchorY, double minAnchorX, double minAnchorY, double scalarPosX, double scalarPosY,
                                    double width, double height, const WColor &color )
{
    m_widgets.emplace_back( WidgetEntry( shape, points, mapsA, mapsB, mapping, anchorX, anchorY, minAnchorX, minAnchorY, scalarPosX, scalarPosY,
                            width, height, color ) );
}

std::vector<WTransferFunction2D::WidgetEntry> WTransferFunction2D::getWidgetList() const
{
    return m_widgets;
}




