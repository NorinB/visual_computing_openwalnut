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

#ifndef WTRANSFERFUNCTION2D_H
#define WTRANSFERFUNCTION2D_H

#include <iosfwd>
#include <vector>

#include "WColor.h"
#include "WHistogram2D.h"
#include "core/dataHandler/WValueSetBase.h"
#include "W2DTFMapper.h"
#include "qtgui/controlPanel/transferFunction2D/WTransferFunction2DEnums.h"

/**
 * A class that stores a 2D transfer function texture and scales it to
 * the desired size given by the user. Also holds a reference to the 2D Histogram
 * and the manipulation widgets.
 */
class WTransferFunction2D // NOLINT problem with macro
{
public:
    /**
     * Default constructor of a meaningless 2D transfer function
     */
    WTransferFunction2D() : m_opacityScale( 1.0 ),
                            m_histogram( nullptr )
    {
    }

    /**
     * Deep copy constructor.
     *
     * \param rhs the value to histogram
     */
    WTransferFunction2D( const WTransferFunction2D &rhs )
            : m_opacityScale( rhs.m_opacityScale ),
              m_histogram( rhs.m_histogram ),
              m_widgets( rhs.m_widgets )
    {
    }

    /**
     * Struct to represent points of a widget-shape e.g. a triangle or box
     * 
     * TODO( T. Neeb ): Implement a standard 2D-Position-Class in OpenWalnut/math 
     */
    struct WidgetPoint
    {
        /**
         * Default constructor for a WidgetPoint
         *
         * @param xc x-coordinate
         * @param yc y-coordinate
         */
        WidgetPoint( float xc = 0, float yc = 0 )
        {
            x = xc;
            y = yc;
        }

        /** x-coordiante of the point */
        float x;

        /** y-coordinate of the point */
        float y;
    };

    /**
     * Prototype for a storage element
     */
    struct Entry
    {
        /**
         * Default constructor
         * \param scalarPosX pos x
         * \param scalarPosY pos y
         */
        explicit Entry( double scalarPosX, double scalarPosY ) : scalarPosX( scalarPosX ), scalarPosY( scalarPosY )
        {
        }

        /**
         * comparison by scalarPosvalue
         * \param rhs entry to compare t
         * \returns true if this->scalarPos <=  rhs.scalarPos
         */
        bool operator <= ( const Entry &rhs ) const
        {
            return scalarPosX <= rhs.scalarPosX && scalarPosY <= rhs.scalarPosY;
        }

        /** the scalarPosvalue x aka. the position x */
        double scalarPosX;
        /** the scalarPosvalue y aka. the position y */
        double scalarPosY;
    };

    /**
     * Entry of a shape widget with ist position and color
     */
    struct WidgetEntry : public Entry
    {
        /** default constructor
         * \param scalarPosX the x pos
         * \param scalarPosY the y pos
         * \param width the width of the shape
         * \param height the height of the shape
         * \param color the color of the shape
         * \param points the points of the shape
         * \param shape the shape of the widgetEntry
         * \param mapsA the maps selected for the first dataset
         * \param mapsB the maps selected for the second dataset
         * \param mapping true = localMapping, false = globalMapping
         * \param anchorX
         * \param anchorY
         * \param minAnchorX
         * \param minAnchorY
         */
        WidgetEntry( Shapes shape, WidgetPoint points[], std::vector<MapType> mapsA, std::vector<MapType> mapsB, bool mapping, double anchorX,
                                        double anchorY, double minAnchorX, double minAnchorY, double scalarPosX, double scalarPosY, double width,
                                        double height, WColor color )
                                        : Entry( scalarPosX, scalarPosY ), width( width ), height( height ), color( color )
        {
            switch( shape )
            {
            case BOX:
                WidgetEntry::points.push_back( points[0] );
                WidgetEntry::points.push_back( points[1] );
                WidgetEntry::points.push_back( points[2] );
                WidgetEntry::points.push_back( points[3] );
                break;
            case TRIANGLE:
                WidgetEntry::points.push_back( points[0] );
                WidgetEntry::points.push_back( points[1] );
                WidgetEntry::points.push_back( points[2] );
                break;
            case QUADRANGLE:
                WidgetEntry::points.push_back( points[0] );
                WidgetEntry::points.push_back( points[1] );
                WidgetEntry::points.push_back( points[2] );
                WidgetEntry::points.push_back( points[3] );
                break;
            case ELLIPSIS:
                WidgetEntry::points.push_back( points[0] );
                WidgetEntry::points.push_back( points[1] );
                WidgetEntry::points.push_back( points[2] );
                WidgetEntry::points.push_back( points[3] );
                break;
            case NOSHAPE:
                break;
            default:
                break;
            }
            entryShape = shape;

            mapsFirst = mapsA;
            mapsSecond = mapsB;
            localMapping = mapping;
            xAnchor = anchorX;
            yAnchor = anchorY;
            xMinAnchor = minAnchorX;
            yMinAnchor = minAnchorY;
        }

        /**
         * comparison operator to check for changes
         * \param rhs WidgetEntry to compare to
         * \returns true if rhs equals this
         */
        bool operator==( const WidgetEntry &rhs ) const
        {
            return scalarPosX == rhs.scalarPosX && scalarPosY == rhs.scalarPosY && color == rhs.color && points[0].x == rhs.points[0].x
                        && points[0].y == rhs.points[0].y && rhs.points[1].x == points[1].x && points[1].y == rhs.points[1].y
                        && points[2].x == rhs.points[2].x && points[2].y == rhs.points[2].y && entryShape == rhs.entryShape
                        && mapsFirst == rhs.mapsFirst && mapsSecond == rhs.mapsSecond && localMapping == rhs.localMapping
                        && xAnchor == rhs.xAnchor && yAnchor == rhs.yAnchor;
        }

        /** the shape of the widget */
        Shapes entryShape;
        /** the points of the shape */
        std::vector<WidgetPoint> points;
        /** the width of the shape */
        double width;
        /** the height of the shape */
        double height;
        /** the color of the shape */
        WColor color;
        /** The color and opacity maps selected for the first dataset */
        std::vector<MapType> mapsFirst;
        /** The color and opacity maps selected for the second dataset */
        std::vector<MapType> mapsSecond;
        /** Mapping State (local = color scale applied related to widget, global = color scale applied related to scene)*/
        bool localMapping;
        /** width-Anchor for animations */
        double xAnchor;
        /** height-Anchor for animations */
        double yAnchor;
        /** minimum width-Anchor for animations */
        double xMinAnchor;
        /** minimum height-Anchor for animations */
        double yMinAnchor;
    };

    /**
     * Deep copy operator
     *
     * \param rhs the value to copy
     * \returns reference to current object
     */
    WTransferFunction2D& operator=( const WTransferFunction2D &rhs )
    {
            this->m_opacityScale = rhs.m_opacityScale;
            setHistogram( rhs.m_histogram );
            this->m_widgets = rhs.m_widgets;
            return ( *this );
    }

    /**
     * Check equivalence of two transfer functions.
     *
     * \returns true if this object contains exactly the same
     * data as rhs
     * \param rhs object to compare with
     */
    bool operator==( const WTransferFunction2D &rhs ) const;

    /**
     * Check equivalence of two transfer functions.
     *
     * \returns negated result of operator==
     * \param rhs the value to compare with
     */
    bool operator!=( const WTransferFunction2D &rhs ) const;

    /**
     * Set the histogram going along with the transfer function
     *
     * \param histogram the 2D histogram
     */
    void setHistogram( const std::shared_ptr< WHistogram2D>& histogram );

    /**
     * Set the scaling factor for the opacity.
     * \param factor scaling factor of opacity values
     */
    void setOpacityScale( double factor )
    {
        m_opacityScale = factor;
    }



    /**
     * Get the histogram going along with the transfer function
     *
     * \returns the stored histogram
     */
    std::shared_ptr< WHistogram2D > getHistogram( )
    {
        return m_histogram;
    }

    /**
     * Get the number of shape.widgets
     *
     * \returns the number of shape-widgets
     */
    size_t numWidgets() const
    {
        return m_widgets.size();
    }

    /**
     * The scalarPosvalue of the widget at a given index.
     * \param i the index widget in the list.
     * \returns the posY of the widget at index i
     */
    double getScalarPosY( size_t i ) const
    {
        return m_widgets.at( i ).scalarPosY;
    }

    /**
     * The scalarPosvalue of the widget at a given index.
     * \param i the index widget in the list.
     * \returns the posX of the widget at index i
     */
    double getScalarPosX( size_t i ) const
    {
        return m_widgets.at( i ).scalarPosX;
    }

    /**
     * The color of the i-th shapewidget in the list.
     *
     * \param i the index widget in the list.
     * \returns the color of the widget at index i
     */
    WColor getColor( size_t i ) const
    {
        return m_widgets.at( i ).color;
    }

    /**
     * @brief Get the list of widgets
     * 
     * @return std::vector<ShapeWidgetEntry> 
     */
    std::vector<WidgetEntry> getWidgetList() const;

    /**
     * The height of the shape widget at a given index.
     * \param i the index widget in the list.
     * \returns the height of the widget at index i
     */
    double getHeight( size_t i ) const
    {
        return m_widgets.at( i ).height;
    }

    /**
     * The width of the shape widget at a given index.
     * \param i the index widget in the list.
     * \returns the height of the widget at index i
     */
    double getWidth( size_t i ) const
    {
        return m_widgets.at( i ).width;
    }

    /**
     * Insert a new shape-widget
     *
     * \param points the points of the triangle to be added
     * \param scalarPosX the new scalarPosX value
     * \param scalarPosY the new scalarPosY value
     * \param width the new scalarPos
     * \param height the new scalarPos
     * \param color the new color at the given scalarPos value
     * \param shape the shape of the object according to the WTransferFunction2DEnums
     * \param mapsA mapsA
     * \param mapsB mapsB
     * \param mapping true = localMapping, false = globalMapping
    * \param anchorX
    * \param anchorY
    * \param minAnchorX
    * \param minAnchorY
     */
    void addWidget( Shapes shape, WidgetPoint points[], std::vector<MapType> mapsA, std::vector<MapType> mapsB, bool mapping,
                                    double anchorX, double anchorY, double minAnchorX, double minAnchorY, double scalarPosX, double scalarPosY,
                                    double width, double height, const WColor &color );

    /**
     * sample/render the transfer function into the given container as a set of RGBA quadruples.
     * \param array pointer to an allocated data structure
     * \param width is the number of RGBA samples in X direction.
     * \param height is the number of RGBA samples in Y direction.
     * \post array contains the sampled data
     * \pre array is allocated and has space for width * height elements
     */
    void sample2DTransferFunction( unsigned char*array, int width, int height ) const;

    /**
     * Using barycentric coordinates check if the point is in a triangle specified by an array of points
     * 
     * @param trianglePoints 
     * @param point 
     * @return true 
     * @return false 
     */
    bool isPointInTriangle( const std::vector<WidgetPoint> trianglePoints, WidgetPoint point ) const;


    /**
     * Check if the point is in a quadrangle specified by an array of points
     * 
     * @param quadranglePoints 
     * @param point 
     * @param min
     * @param max
     * @return true 
     * @return false 
     */
    bool isPointInQuadrangle( const std::vector<WidgetPoint> quadranglePoints, WidgetPoint point, WidgetPoint min, WidgetPoint max ) const;

    /**
     * Check if two lines intersect and return the intersection point
     * 
     * @param pointA
     * @param pointB
     * @param pointC
     * @param pointD
     * @return true 
     * @return false 
     */
    WidgetPoint getLineIntersection( WidgetPoint pointA, WidgetPoint pointB, WidgetPoint pointC, WidgetPoint pointD ) const;

    /**
     * @brief Check if a point lies inside an ellipsis
     * 
     * @param ellipsisPoints 
     * @param point 
     * @return true 
     * @return false 
     */
    bool isPointInEllipsis( const std::vector<WidgetPoint> ellipsisPoints, WidgetPoint point ) const;
private:
    /**
     * Factor by which the output opacity is scaled
     * to allow for easier specification of very small
     * opacity values.
     */
    double m_opacityScale;

    /**
     * Holds a reference to the histogram to be rendered
     */
    std::shared_ptr< WHistogram2D > m_histogram;

    /**
     * The widgets used in the 2D TF
     */
    std::vector<WidgetEntry> m_widgets;

    /**
     * The Mapper-Object that is used for color- and opacity-mapping
     */
    W2DTFMapper m_mapper;
};

#endif  // WTRANSFERFUNCTION2D_H
