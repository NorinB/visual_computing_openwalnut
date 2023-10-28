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

#ifndef WPICKINFO3D_H
#define WPICKINFO3D_H

#include <string>

#include <osg/Vec3>
#include <osg/Quat>

#include "../common/math/linearAlgebra/WVectorFixed.h"
#include "../common/math/linearAlgebra/WPosition.h"

/**
 * Encapsulates the data for the 3D pick.
 */
class WPickInfo3D
{
public:
    /**
     * Different button types
     */
    typedef enum
    {
        NONE    = 0x0,
        TRIGGER = 0x1,
        GRIP    = 0x2
    }
    WVRButton;

    /**
     * Creates an object with the needed information.
     * \param name The name of the picked object.
     * \param position The position of the controller.
     * \param rotation The rotation of the controller.
     * \param buttons The controller buttons.
     * \param pickPosition The position of the pick.
     * \param pickNormal The normal of the picked surface.
     * \param pickPath The path of the pick.
     */
    inline WPickInfo3D( std::string name,
                        osg::Vec3 position = osg::Vec3(),
                        osg::Quat rotation = osg::Quat(),
                        int buttons = WVRButton::NONE,
                        WPosition pickPosition = WPosition(),
                        WVector3d pickNormal = WVector3d(),
                        std::string pickPath = "" );

    /**
     * Creates an empty object.
     */
    inline WPickInfo3D();

    /**
     * Get name of picked object.
     *
     * \return object name
     */
    inline std::string getName() const;

    /**
     * Get name of all picked objects in ray.
     *
     * \return Names
     */
    inline std::string getPickPath() const;

    /**
     * Gets the position of the controller.
     * 
     * \return The position
     */
    inline osg::Vec3 getPosition() const;

    /**
     * Gets the rotation of the controller.
     * 
     * \return The rotation 
     */
    inline osg::Quat getRotation() const;

    /**
     * Gets the pressed buttons
     *
     * \return The buttons
     */
    inline int getButtons() const;

    /**
     * Get position where object was hit.
     *
     * \return the pick position
     */
    inline WPosition getPickPosition() const;

    /**
     * Get normal at position where object was hit.
     *
     * \return pick normal
     */
    inline WVector3d getPickNormal() const;


    /**
     * Set pick path string.
     *
     * \param pickPath String representing the pick path
     */
    inline void setPickPath( std::string pickPath );

    /**
     * Add object to pick path.
     *
     * \param name Name of new object in path.
     */
    inline void appendToPickPath( std::string name );

    /**
     * Tests two pick infos for equality
     * \param rhs right hand side of comparison
     *
     * \return true if equal
     */
    inline bool operator==( WPickInfo3D rhs ) const;

    /**
     * Tests two pick infos for inequality
     *
     * \param rhs right hand side of comparison
     *
     * \return true if not equal
     */
    inline bool operator!=( WPickInfo3D rhs ) const;

    /**
     * Tests whether this pick info is empty.
     * \return true if empty
     */
    inline bool empty() const;

private:
    std::string m_name; //!< Name of the picked object.
    std::string m_pickPath; //!< Name of all picked objects along the path.

    osg::Vec3 m_position; //!< The controller position.
    osg::Quat m_rotation; //!< The controller rotation.

    int m_buttons; //!< The pressed buttons.

    WPosition m_pickPosition; //!< Position where object was hit.
    WVector3d m_pickNormal; //!< Normal at position where object was hit.
};


WPickInfo3D::WPickInfo3D( std::string name,
                          osg::Vec3 position,
                          osg::Quat rotation,
                          int buttons,
                          WPosition pickPosition,
                          WVector3d pickNormal,
                          std::string pickPath ) :
    m_name( name ),
    m_pickPath( pickPath ),
    m_position( position ),
    m_rotation( rotation ),
    m_buttons( buttons ),
    m_pickPosition( pickPosition ),
    m_pickNormal( pickNormal )
{
}

WPickInfo3D::WPickInfo3D() :
    m_name( "" ),
    m_pickPath( "" ),
    m_position( osg::Vec3() ),
    m_rotation( osg::Quat() ),
    m_buttons( WPickInfo3D::NONE ),
    m_pickPosition( WPosition() ),
    m_pickNormal( WVector3d() )
{
}

std::string WPickInfo3D::getName() const
{
    return m_name;
}

std::string WPickInfo3D::getPickPath() const
{
    return m_pickPath;
}

osg::Vec3 WPickInfo3D::getPosition() const
{
    return m_position;
}

osg::Quat WPickInfo3D::getRotation() const
{
    return m_rotation;
}

int WPickInfo3D::getButtons() const
{
    return m_buttons;
}

WPosition WPickInfo3D::getPickPosition() const
{
    return m_pickNormal;
}

WVector3d WPickInfo3D::getPickNormal() const
{
    return m_pickNormal;
}

void WPickInfo3D::setPickPath( std::string pickPath )
{
    m_pickPath = pickPath;
}

void WPickInfo3D::appendToPickPath( std::string name )
{
    m_pickPath += " -- " + name + "\n ";
}

bool WPickInfo3D::operator==( WPickInfo3D rhs ) const
{
    return ( this->m_name == rhs.m_name
             && this->m_position  == rhs.m_position
             && this->m_rotation  == rhs.m_rotation
             && this->m_buttons   == rhs.m_buttons );
}

bool WPickInfo3D::operator!=( WPickInfo3D rhs ) const
{
    return !( *this == rhs );
}

bool WPickInfo3D::empty() const
{
    return m_name == "" || m_name == "nothing";
}

#endif  // WPICKINFO3D_H
