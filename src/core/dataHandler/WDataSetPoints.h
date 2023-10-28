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

#ifndef WDATASETPOINTS_H
#define WDATASETPOINTS_H

#include <any>
#include <memory>
#include <string>
#include <utility>
#include <vector>


#include "../common/WBoundingBox.h"
#include "WDataSet.h"

/**
 * Dataset to store a bunch of points without order or topology.
 */
class WDataSetPoints : public WDataSet // NOLINT
{
public:
    // some type alias for the used arrays.
    /**
     * Pointer to dataset.
     */
    typedef std::shared_ptr< WDataSetPoints > SPtr;

    /**
     * Pointer to const dataset.
     */
    typedef std::shared_ptr< const WDataSetPoints > ConstSPtr;

    /**
     * List of vertex coordinates in term of components of vertices.
     */
    typedef std::shared_ptr< std::vector< float > > VertexArray;

    /**
     * Colors for each vertex in VertexArray.
     */
    typedef std::shared_ptr< std::vector< float > > ColorArray;

    /**
     * Constructs a new set of points. If no color is specified, white is used for all points.
     *
     * \note the number of floats in vertices must be a multiple of 3
     * \note the number of floats in colors (if not NULL) must be vertices->size() / 3  times one of 1,3, or 4
     *
     * \param vertices the vertices of the points, stored in x1,y1,z1,x2,y2,z2, ..., xn,yn,zn scheme
     * \param colors the colors of each vertex. Can be NULL. Stored as R1,G1,B1,A1, ... Rn,Gn,Bn,An
     * \param boundingBox The bounding box of the points (first minimum, second maximum).
     */
    WDataSetPoints( VertexArray vertices, ColorArray colors,
                    WBoundingBox boundingBox );

    /**
     * Constructs a new set of points. The bounding box is calculated during construction. If no color is specified, white is used for all
     * points.
     *
     * \note the number of floats in vertices must be a multiple of 3
     * \note the number of floats in colors (if not NULL) must be vertices->size() / 3  times one of 1,3, or 4
     *
     * \param vertices the vertices of the points, stored in x1,y1,z1,x2,y2,z2, ..., xn,yn,zn scheme
     * \param colors optional colors of each vertex. Stored as R1,[G1,B1,[A1,]] ... Rn,[Gn,Bn,[An]]
     * \param data optional extra data.
     */
    WDataSetPoints( VertexArray vertices, ColorArray colors = NULL, std::any data = NULL );

    /**
     * Constructs a new set of points. The constructed instance is empty.
     */
    WDataSetPoints();

    /**
     * Destructor.
     */
    virtual ~WDataSetPoints();

    /**
     * Get number of points in this data set.
     *
     * \return number of points
     */
    size_t size() const;

    /**
     * Determines whether this dataset can be used as a texture.
     *
     * \return true if usable as texture.
     */
    virtual bool isTexture() const;

    /**
     * Gets the name of this prototype.
     *
     * \return the name.
     */
    virtual const std::string getName() const;

    /**
     * Gets the description for this prototype.
     *
     * \return the description
     */
    virtual const std::string getDescription() const;

    /**
     * Returns a prototype instantiated with the true type of the deriving class.
     *
     * \return the prototype.
     */
    static std::shared_ptr< WPrototyped > getPrototype();

    /**
     * Getter for the point vertices
     * \return The vertices
     */
    VertexArray getVertices() const;

    /**
     * Getter for the point colors
     * \return The colors
     */
    ColorArray getColors() const;

    /**
     * Getter for the data set
     * \return The data set
     */
    std::any getData() const;

    /**
     * Get the bounding box.
     * \return The bounding box of all points.
     */
    WBoundingBox getBoundingBox() const;

    /**
     * Query coordinates of a given point.
     *
     * \throw WOutOfBounds if invalid index is used.
     * \param pointIdx the point index.
     *
     * \return the coordinates
     */
    WPosition operator[]( const size_t pointIdx ) const;

    /**
     * Query coordinates of a given point.
     *
     * \throw WOutOfBounds if invalid index is used.
     * \param pointIdx the point index.
     *
     * \return the coordinates
     */
    WPosition getPosition( const size_t pointIdx ) const;

    /**
     * The color of a given point.
     *
     * \throw WOutOfBounds if invalid index is used.
     * \param pointIdx the point index.
     *
     * \return the color
     */
    WColor getColor( const size_t pointIdx ) const;

    /**
     * Is this a valid point index?
     *
     * \param pointIdx the index to check
     *
     * \return true if yes.
     */
    bool isValidPointIdx( const size_t pointIdx ) const;

    /**
     * The type of colors we have for each point.
     */
    enum ColorType
    {
        GRAY = 1,
        RGB = 3,
        RGBA =4
    };

    /**
     * Check the type of color.
     *
     * \return the type
     */
    ColorType getColorType() const;
protected:
    /**
     * The prototype as singleton.
     */
    static std::shared_ptr< WPrototyped > m_prototype;

private:
    /**
     * Point vector for all points
     */
    VertexArray m_vertices;

    /**
     * An array of the colors per vertex.
     */
    ColorArray m_colors;

    /**
     * An optional vector for data per vertex.
     */
    std::any m_data;

    /**
     * Which colortype do we use in m_colors.
     */
    ColorType m_colorType;

    /**
     * Axis aligned bounding box for all point-vertices of this dataset.
     */
    WBoundingBox m_bb;

    /**
     * Initialize arrays and bbox if needed. Used during construction.
     *
     * \param calcBB if true, the bounding box is calculated
     */
    void init( bool calcBB = false );
};

#endif  // WDATASETPOINTS_H
