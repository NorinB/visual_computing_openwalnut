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

#ifndef WTRANSFERFUNCTION2DWIDGETANIMATIONDATA_H
#define WTRANSFERFUNCTION2DWIDGETANIMATIONDATA_H

#include <string>

#include "WTransferFunction2DEnums.h"


/**
 * Class for storing animation information to be used in the UI
 */
class WTransferFunction2DWidgetAnimationData
{
    public:
    /**
     * @brief Construct a new WTransferFunction2DWidgetAnimationData object
     * 
     * @param name 
     * @param type
     */
    WTransferFunction2DWidgetAnimationData( std::string name = "Null", AnimationType type = NO_ANIM );

    /**
     * @brief Destroy the WTransferFunction2DWidgetAnimationData object
     * 
     */
    ~WTransferFunction2DWidgetAnimationData();

    /**
     * @brief Get the Name object
     * 
     * @return std::string 
     */
    std::string getName();

    /**
     * @brief Set the Name object
     * 
     * @param newName 
     */
    void setName( std::string newName );

    /**
     * @brief Get the Type object
     * 
     * @return AnimationType 
     */
    AnimationType getType();

    private:
        /**
         * @brief type of animation
         * 
         */
        AnimationType m_type;

        /**
         * @brief name of the animation
         * 
         */
        std::string m_name;
};

#endif  // WTRANSFERFUNCTION2DWIDGETANIMATIONDATA_H
