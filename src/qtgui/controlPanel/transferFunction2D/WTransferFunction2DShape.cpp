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

#include "WTransferFunction2DShape.h"

WTransferFunction2DShape::WTransferFunction2DShape( std::vector<QPointF> points, Shapes shape  )
{
    switch( shape )
    {
        case BOX:
            m_shape = BOX;
            m_points.push_back( points[0] );
            m_points.push_back( points[1] );
            m_points.push_back( points[2] );
            m_points.push_back( points[3] );
            m_pointCount = 4;
            m_polygon = QPolygonF( QVector<QPointF>
                                    {
                                        m_points[0], m_points[1], m_points[2], m_points[3]
                                    } );
            calculateCentre();
            break;
        case TRIANGLE:
            m_shape = TRIANGLE;
            m_points.push_back( points[0] );
            m_points.push_back( points[1] );
            m_points.push_back( points[2] );
            m_pointCount = 3;
            m_polygon = QPolygonF( QVector<QPointF>
                                    {
                                        m_points[0], m_points[1], m_points[2]
                                    } );
            calculateCentre();
            break;
        case QUADRANGLE:
            m_shape = QUADRANGLE;
            m_points.push_back( points[0] );
            m_points.push_back( points[1] );
            m_points.push_back( points[2] );
            m_points.push_back( points[3] );
            m_pointCount = 4;
            m_polygon = QPolygonF( QVector<QPointF>
                                    {
                                        m_points[0], m_points[1], m_points[2], m_points[3]
                                    } );
            calculateCentre();
            break;
        case ELLIPSIS:
            m_shape = ELLIPSIS;
            m_points.push_back( points[0] );
            m_points.push_back( points[1] );
            m_points.push_back( points[2] );
            m_points.push_back( points[3] );
            m_pointCount = 4;
            m_polygon = QPolygonF( QVector<QPointF>
                                    {
                                        m_points[0], m_points[1], m_points[2], m_points[3]
                                    } );
            calculateCentre();
            break;
        default:
            break;
        }
}

WTransferFunction2DShape::~WTransferFunction2DShape()
{
}

Shapes WTransferFunction2DShape::getShape()
{
    return m_shape;
}

std::vector<QPointF> WTransferFunction2DShape::getPoints()
{
    return m_points;
}

QPointF WTransferFunction2DShape::getPoint( int index )
{
    return m_points[index];
}

QPolygonF WTransferFunction2DShape::getPolygon() const
{
    return m_polygon;
}

int WTransferFunction2DShape::getPointCount()
{
    return m_pointCount;
}

QPointF WTransferFunction2DShape::getCentralPoint()
{
    return m_centralPoint;
}

void WTransferFunction2DShape::setPoint( int index, QPointF newPosition )
{
    m_points[index] = newPosition;
    updateProperties();
}

void WTransferFunction2DShape::updateProperties()
{
    switch( m_shape )
    {
        case BOX:
            m_polygon = QPolygonF( QVector<QPointF>
                                    {
                                        m_points[0], m_points[1], m_points[2], m_points[3]
                                    } );
            calculateCentre();
            break;
        case TRIANGLE:
            m_polygon = QPolygonF( QVector<QPointF>
                                    {
                                        m_points[0], m_points[1], m_points[2]
                                    } );
            calculateCentre();
            break;
        case QUADRANGLE:
            m_polygon = QPolygonF( QVector<QPointF>
                                    {
                                        m_points[0], m_points[1], m_points[2], m_points[3]
                                    } );
            calculateCentre();
            break;
        case ELLIPSIS:
            m_polygon = QPolygonF( QVector<QPointF>
                                    {
                                        m_points[0], m_points[1], m_points[2], m_points[3]
                                    } );
            calculateCentre();
            break;
        default:
            break;
    }
}

void WTransferFunction2DShape::calculateCentre()
{
    switch( m_shape )
    {
    case BOX:
        m_centralPoint = QPointF( ( m_points[0].x() + m_points[2].x() ) / 2, ( m_points[0].y() + m_points[2].y() ) / 2 );
        break;
    case TRIANGLE:
        m_centralPoint = QPointF( ( m_points[0].x() + m_points[1].x() + m_points[2].x() ) / 3,
                                 ( m_points[0].y() + m_points[1].y() + m_points[2].y() ) / 3 );
        break;
    default:
        break;
    }
}
