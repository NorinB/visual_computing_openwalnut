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

#ifndef WTRANSFERFUNCTION2DTRIANGLE_H
#define WTRANSFERFUNCTION2DTRIANGLE_H

#include "QPolygonF"
#include "core/common/WLogger.h"

/**
 * (WIP) A class for creating a triangle that is used in creating TriangleWidgets for the 2D-TransferFunction Module. 
 */
class WTransferFunction2DTriangle
{
    public:
        /**
         * Default Constructor of a triangle.
         * Takes three QPoint-Objects as parameters.
         * \param left the point of the triangle titled "left"
         * \param mid the point of the triangle titled "mid"
         * \param right the point of the triangle titled "right"
         */
        WTransferFunction2DTriangle( QPointF left = QPointF( 1.0, 1.0 ), QPointF mid = QPointF( 1.50, 1.5 ), QPointF right = QPointF( 2.0, 1.0 ) );

        /**
         * Destroy the WTransferFunction2DTriangle object
         * Default Destructor
         */
        ~WTransferFunction2DTriangle();

        /**
         * Get the QPolygonF-Object which presents the triangle
         * 
         * @return QPolygonF 
         */
        QPolygonF getTriangle() const
        {
            return m_triangle;
        }
        /**
         * @brief Returns a QPoint of the triangle with the title "left"
         * 
         * @return QPointF 
         */
        QPointF left()
        {
            return m_left;
        }
        /**
         * @brief Returns a QPoint of the triangle with the title "mid"
         *
         * @return QPointF
         */
        QPointF mid()
        {
            return m_mid;
        }
        /**
         * @brief Returns a QPoint of the triangle with the title "right"
         * 
         * @return QPointF 
         */
        QPointF right()
        {
            return m_right;
        }
        /**
         * @brief Sets the "left" QPoint of the triangle and updates the QPolygonF triangle
         * 
         * @param point 
         */
        void setLeft( QPointF point )
        {
            m_left = point;
            updateTriangle();
        }
        /**
         * @brief Sets the "mid" QPoint of the triangle and updates the QPolygonF triangle
         *
         * @param point
         */
        void setMid( QPointF point )
        {
            m_mid = point;
            updateTriangle();
        }
        /**
         * @brief Sets the "right" QPoint of the triangle and updates the QPolygonF triangle
         *
         * @param point
         */
        void setRight( QPointF point )
        {
            m_right = point;
            updateTriangle();
        }
        /**
         * @brief Updates the QPolygonF-Triangle. Used after an independet triangle-point is set
         * 
         */
        void updateTriangle()
        {
            m_triangle[0] = m_left;
            m_triangle[1] = m_mid;
            m_triangle[2] = m_right;
        }
        /**
         * @brief Update the independent triangle-points after the QPolygonF-Triangle has been changed
         * 
         */
        void updateTrianglePoints()
        {
            m_left = m_triangle[0];
            m_mid = m_triangle[1];
            m_right = m_triangle[2];
        }

    private:
        /** QPoint which presents the "left" triangle point*/
        QPointF m_left;
        /** QPoint which presents the "mid" triangle point*/
        QPointF m_mid;
        /** QPoint which presents the "right" triangle point*/
        QPointF m_right;
        /** QPolygonF-Object which holds all the triangle points and is used for drawing and managing the triangle*/
        QPolygonF m_triangle;
};

#endif  // WTRANSFERFUNCTION2DTRIANGLE_H
