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

#ifndef W2DTFMAPPER_H
#define W2DTFMAPPER_H

#include <vector>

#include "WColor.h"
#include "qtgui/controlPanel/transferFunction2D/WTransferFunction2DEnums.h"

/**
 * Class that handles the process of mapping values to color in the "2D transfer function"-module.
 * Also contains information about all available maps and how specific colors are calculated with interpolation in the 2DTF+DVR context
 */
class W2DTFMapper
{
public:
    /**
     * @brief Construct a new W2DTFMapper object
     * important: In here the color and opacity maps are described by their Steps (see Step-Struct in W2DTFMapper-Class)
     * if you want to change maps or add new ones this is the place to do so 
     */
    W2DTFMapper();

    /**
     * @brief Destroy the W2DTFMapper object
     */
    ~W2DTFMapper();

    /** Struct that represents a pair of a scalar value and a color value*/
    struct Step
    {
        /**
         * @brief Construct a new Step
         * 
         * @param stepValue 
         * @param stepColor 
         */
        Step( float stepValue, WColor stepColor )
        {
            value = stepValue;
            color = stepColor;
        }

        /** The scalar value of the step */
        float value;
        /** The color of the step */
        WColor color;
    };

    /**
     * @brief Get the Color for a point of a widget
     * 
     * @param mapsFirst 
     * @param mapsSecond 
     * @param posX 
     * @param posY 
     * @param maxX
     * @param maxY 
     * @param current
     * @param minX
     * @param minY
     * @return WColor 
     */
    WColor getColorForWidget( std::vector<MapType> mapsFirst, std::vector<MapType> mapsSecond, int posX, int posY, int maxX, int maxY,
                                int minX, int minY, WColor current ) const;

    /**
     * @brief Interpolates between to colors defined by the weight parameter
     * 
     * @param first first color
     * @param second second color
     * @param weight weight for the interpolation
     * @param isColorMap state to differentiate if caller is ColorMap or OpactiyMap
     * @return WColor 
     */
    WColor interpolate( WColor first, WColor second, float weight, bool isColorMap ) const;

    /**
     * @brief Blends the first and second color together. If "onlyColor" is set to false the opacity will also be included in the blending 
     * 
     * @param first 
     * @param second 
     * @param onlyColor
     * @param firstOpacity
     * @return WColor 
     */
    WColor blendColors( WColor first, WColor second, bool onlyColor, bool firstOpacity ) const;

    /**
     * @brief Get the Map
     * 
     * @param map 
     * @return std::vector<Step> 
     */
    std::vector<Step> getMap( MapType map );
private:
    /**
     * @brief Calculates the color for the specific map
     * 
     * @param map 
     * @param scalarValue 
     * @param mapSteps 
     * @param pos 
     * @param max 
     * @param isOpacity 
     * @return WColor 
     */
    WColor calculateColorForMap( std::vector<Step> map, float scalarValue, int mapSteps, [[maybe_unused]] float pos, float max,
                                    bool isOpacity ) const;
    /** The color that is modified each time the mapper maps a value to color*/
    WColor m_mappedColor;
    /** Viridis colormap described by steps*/
    std::vector<Step> c_viridis;
    /** Inversed Viridis colormap described by steps*/
    std::vector<Step> c_inv_viridis;
    /** Green/Yellow/Red continuous colormap described by steps*/
    std::vector<Step> c_GYR;
    /** Inversed GreenYelloRed colormap described by steps*/
    std::vector<Step> c_inv_GYR;
    /** Black-to-white continuous colormap described by steps*/
    std::vector<Step> c_BWcont;
    /** Inversed Black-to-white continuous colormap described by steps*/
    std::vector<Step> c_inv_BWcont;
    /** Decrease Opacity continuously with increasing value opacityMap described by steps*/
    std::vector<Step> o_decrease;
    /** Increase Opacity with increasing value opacityMap described by steps*/
    std::vector<Step> o_increase;
    /** Inferno colormap described by steps*/
    std::vector<Step> c_inferno;
    /** Inversed Inferno colormap described by steps*/
    std::vector<Step> c_inv_inferno;
    /** RedBlue colormap described by steps*/
    std::vector<Step> c_redblue;
    /** Inversed RedBlue colormap described by steps*/
    std::vector<Step> c_inv_redblue;
    /** Twilight colormap described by steps*/
    std::vector<Step> c_twilight;
    /** Inversed Twilight colormap described by steps*/
    std::vector<Step> c_inv_twilight;
};

#endif  // W2DTFMAPPER_H
