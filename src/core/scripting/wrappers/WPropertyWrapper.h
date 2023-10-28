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

#ifndef WPROPERTYWRAPPER_H
#define WPROPERTYWRAPPER_H

#include <memory>
#include <string>


#include "WColorWrapper.h"
#include "core/common/WPropertyBase.h"

/**
 * \class WPropertyWrapper
 *
 * Encapsulates a WProperty. Used to expose the properties to scripts.
 */
class WPropertyWrapper
{
public:
    /**
     * Constructor.
     *
     * \param prop The property.
     */
    explicit WPropertyWrapper( std::shared_ptr< WPropertyBase > prop );

    /**
     * Return the name of the property.
     *
     * \return The name of the property.
     */
    std::string getName() const;

    /**
     * Return the description of the property.
     *
     * \return The description of the property.
     */
    std::string getDescription() const;

    /**
     * Get the value of a boolean property.
     *
     * \param notify If true, informs the property that it was read.
     * \return The current value of the property.
     */
    bool getBool( bool notify = false ) const;

    /**
     * Get the value of an integer property.
     *
     * \param notify If true, informs the property that it was read.
     * \return The current value of the property.
     */
    int getInt( bool notify = false ) const;

    /**
     * Get the value of a string property.
     *
     * \param notify If true, informs the property that it was read.
     * \return The current value of the property.
     */
    std::string getString( bool notify = false ) const;

    /**
     * Get the value of a double property.
     *
     * \param notify If true, informs the property that it was read.
     * \return The current value of the property.
     */
    double getDouble( bool notify = false ) const;

    /**
     * Get the filename of a filename property.
     *
     * \param notify If true, informs the property that it was read.
     * \return The current value of the property.
     */
    std::string getFilename( bool notify = false ) const;

    /**
     * Get the (first) selected item of a selection property.
     *
     * \param notify If true, informs the property that it was read.
     * \return The first of the currently selected items.
     */
    int getSelection( bool notify = false ) const;

    /**
     * Get the color of a color property.
     *
     * \param notify If true, informs the property that it was read.
     *
     * \return The color of the property.
     */
    WColorWrapper getColor( bool notify = false ) const;

    /**
     * Set the value of a boolean property.
     *
     * \param b The new value.
     */
    void setBool( bool b );

    /**
     * Set the value of an integer property.
     *
     * \param i The new value.
     */
    void setInt( int i );

    /**
     * Set the value of a string property.
     *
     * \param s The new value.
     */
    void setString( std::string const& s );

    /**
     * Set the value of a double property.
     *
     * \param d The new value.
     */
    void setDouble( double d );

    /**
     * Set the filename of the filename property.
     *
     * \param fn The new value.
     */
    void setFilename( std::string const& fn );

    /**
     * Sets the selected item of a selection. All other items will be deselected.
     *
     * \param s The index of the selected item.
     */
    void setSelection( int s );

    /**
     * Set the color of a color property.
     *
     * \param col The new color.
     */
    void setColor( WColorWrapper col );

    /**
     * Trigger a trigger property.
     */
    void click();

    /**
     * Wait for the property to update its value.
     */
    void waitForUpdate();

private:
    //! The property.
    std::shared_ptr< WPropertyBase > m_prop;
};

#endif  // WPROPERTYWRAPPER_H
