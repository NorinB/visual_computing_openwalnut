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

#ifndef WPICKHANDLER3D_H
#define WPICKHANDLER3D_H

#include <string>
#include <utility>

#include <boost/signals2/signal.hpp>

#include <osgUtil/RayIntersector>
#include <osgViewer/View>

#include "WPickInfo3D.h"

/**
 * Class to handle events with a pick in 3D.
 *
 * The handler ignores any geometry whose name starts with an underscore ("_").
 */
class WPickHandler3D : public osg::Referenced
{
public:
    /**
     * Constructor that initalizes members with sensible defaults.
     */
    WPickHandler3D();

    /**
     * Call this when picking in 3D.
     * \param camera The camera that the pick was done through.
     * \param leftPosition The position of the left controller.
     * \param rightPosition The position of the right controller.
     * \param leftRotation The rotation of the left controller.
     * \param rightRotation The rotation of the right controller.
     * \param leftButtons The pressed buttons on the left controller.
     * \param rightButtons The pressed buttons on the right controller.
     */
    void pick( osg::Camera* camera,
               osg::Vec3 leftPosition,
               osg::Vec3 rightPosition,
               osg::Quat leftRotation,
               osg::Quat rightRotation,
               int leftButtons,
               int rightButtons );

    /**
     * Send a pick signal with the unpickString for the left controller
     */
    void unpickLeft();

    /**
     * Send a pick signal with the unpickString for the right controller
     */
    void unpickRight();

    /**
     * Gives information about the picked object on the left controller.
     *
     * \return info object for this hit
     */
    WPickInfo3D getHitResultLeft();

    /**
     * Gives information about the picked object on the right controller.
     *
     * \return info object for this hit
     */
    WPickInfo3D getHitResultRight();

    /**
     * \return the m_pickSignal to for registering to it.
     */
    boost::signals2::signal< void( std::pair< WPickInfo3D, WPickInfo3D > ) >* getPickSignal();

    static const std::string unpickString; //!< The string indicating picking has stopped.

private:
    boost::signals2::signal< void( std::pair< WPickInfo3D, WPickInfo3D > ) > m_pickSignal; //!< Register to this signal to receive pick events.

    WPickInfo3D m_hitResultLeft; //!< The info for the left hit.
    WPickInfo3D m_hitResultRight; //!< The info for the right hit.
    WPickInfo3D m_startPickLeft; //!< Where the left side was picked first.
    WPickInfo3D m_startPickRight; //!< Where the right side was picked first.
};

#endif  // WPICKHANDLER3D_H
