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

#ifndef WTRANSFERFUNCTION2DWIDGETMAPDATA_H
#define WTRANSFERFUNCTION2DWIDGETMAPDATA_H

#include <string>
#include "WTransferFunction2DEnums.h"

/**
 * Class that holds all information necessary to enable map selection in the context menu of a classification widget in the 2DTF-module.
 * This class only represents data for the UI and does not help with color- or opacity-mapping. 
 */


class WTransferFunction2DWidgetMapData
{
public:
    /**
     * @brief Construct a new WTransferFunction2DWidgetMapData object
     * 
     * @param name 
     * @param maptype (COLOR || OPACITY)
     */
    WTransferFunction2DWidgetMapData( std::string name, MapType maptype );

    /**
     * @brief Destroy the WTransferFunction2DWidgetMapData object
     * 
     */
    ~WTransferFunction2DWidgetMapData();

    /**
     * @brief Get the Name object
     * 
     * @return std::string 
     */
    std::string getName();

    /**
     * @brief Get the Type object
     * 
     * @return MapType 
     */
    MapType getType();

private:
    /** name of the map **/
    std::string m_name;

    /** type of the map*/
    MapType m_mapType;
};

#endif  // WTRANSFERFUNCTION2DWIDGETMAPDATA_H
