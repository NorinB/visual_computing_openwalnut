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

#ifndef WTRANSFERFUNCTION2DSHAPE_H
#define WTRANSFERFUNCTION2DSHAPE_H


#include <vector>

#include "QPolygonF"
#include "QPointF"

#include "WTransferFunction2DEnums.h"

/**
 * Class representing a 2D-Shape in formal description as points and other properties
 * 
 * Based on the shape specified by an enum in "WTransferFunction2DEnums.h" a vector of points gets initialised
 * which represent the shape. A QPolygonF-Object is then instantiated based of the point-vector and is used for drawing or
 * getting information about the bounding rect and so on.  
 * 
 */
class WTransferFunction2DShape
{
public:
    /**
     * @brief Construct a new WTransferFunction2DShape object base on a specific shape-parameter
     * 
     * @param points
     * @param shape 
     */
    WTransferFunction2DShape( std::vector<QPointF> points = std::vector<QPointF>
                            {
                                QPointF( 0.0, 0.0 ),
                                QPointF( 50.0, 0.0 ),
                                QPointF( 50.0, 50.0 ),
                                QPointF( 0.0, 50.0 ) }, Shapes shape = BOX );

    /**
     * Destroy the WTransferFunction2DShape object
     */
    ~WTransferFunction2DShape();

    /**
     * @brief Returns the name of the shape this object represents
     * 
     * @return returns the name of the shape
     */
    Shapes getShape();

    /**
     * @brief Get the points of the shape-object
     * 
     * @return std::vector<QPointF> 
     */
    std::vector<QPointF> getPoints();

    /**
     * @brief Get a specific point of the shape-object
     * 
     * @param index 
     * @return QPointF 
     */
    QPointF getPoint( int index );

    /**
     * @brief Returns the QPolygonF-Object of the shape
     * 
     * Mainly used to access additional information about the shape
     * 
     * @return QPolygonF 
     */
    QPolygonF getPolygon() const;

    /**
     * @brief Returns the point count. Used in iterator and loops.
     * 
     * @return int 
     */
    int getPointCount();

    /**
     * @brief Returns the central point of the shape
     * 
     * @return QPointF 
     */
    QPointF getCentralPoint();

    /**
     * @brief Set point of the point vector to a new position.
     * 
     * Updates the shape-object automatically.
     * 
     * @param index 
     * @param newPosition 
     */
    void setPoint( int index, QPointF newPosition );

private:
    /**
     * @brief Updates the properties of the shape after something has been changed
     *
     */
    void updateProperties();

    /**
     * @brief Calcualte the centre point based on the shape of the object
     * 
     */
    void calculateCentre();

    /** The shape of the object */
    Shapes m_shape;

    /** The points of the shape */
    std::vector<QPointF> m_points;

    /** The polygon represented by the point vector */
    QPolygonF m_polygon;

    /** Count of points of the shape */
    int m_pointCount;

    /** The central point of the shape */
    QPointF m_centralPoint;
};

#endif  // WTRANSFERFUNCTION2DSHAPE_H
