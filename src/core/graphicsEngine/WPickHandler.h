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

#ifndef WPICKHANDLER_H
#define WPICKHANDLER_H

#include <string>

#include <boost/signals2/signal.hpp>

#include <osgViewer/View>


#include "WPickInfo.h"


/**
 * Class to handle events with a pick.
 *
 * The handler ignores any geometry whose name starts with an underscore ("_").
 */
class WPickHandler: public osgGA::GUIEventHandler
{
public:
    /**
     * Constructor that initalizes members with sensible defaults.
     */
    WPickHandler();

    /**
     * Constructor that initalizes members with sensible defaults and sets the name of the viewer
     *
     * \param viewerName name of the viewer
     */
    explicit WPickHandler( std::string viewerName );

    /**
     * Deals with the events found by the osg.
     * \param ea Event class for storing Keyboard, mouse and window events.
     * \param aa Interface by which GUIEventHandlers may request actions of the GUI system
     *
     * \return true if the event was handled.
     */
    bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );

    /**
     * Send a pick signal with the pick information as string
     * \param view the view in which we pick.
     * \param ea Event class for storing Keyboard, mouse and window events.
     */
    virtual void pick( osgViewer::View* view, const osgGA::GUIEventAdapter& ea );

    /**
     * Send a pick signal with the unpickString
     */
    virtual void unpick();

    /**
     * Gives information about the picked object.
     *
     * \return info object for this hit
     */
    WPickInfo getHitResult();

    /**
     * \return the m_pickSignal to for registering to it.
     */
    boost::signals2::signal< void( WPickInfo ) >* getPickSignal();

    /**
     * setter for paint mode
     * \deprecated use variant taking bool instead.
     * \param mode the paint mode
     */
    OW_API_DEPRECATED void setPaintMode( int mode );

    /**
     * Set in paint mode
     * \param paintMode Should we switch to paint mode?
     */
    void setPaintMode( bool paintMode );

    inline static const std::string unpickString = "unpick"; //!< The string indicating picking has stopped.

protected:
    /**
     * Virtual destructor needed because of virtual function.
     *
     * This desctructor is protected to avoid accidentally deleting
     * an instance of WPickHandler.
     * This follows the philosophy of OSG to avoid problems in multithreaded
     * environments, since these pointers are used deep in the OSG where
     * a deletion could cause a segfault.
     */
    virtual ~WPickHandler();

private:
    /**
     * Sets the current modifiers to the provided pickInfo
     *
     * \param pickInfo This pickInfo will be updated.
     */
    void updatePickInfoModifierKeys( WPickInfo* pickInfo );

    boost::signals2::signal< void( WPickInfo ) > m_pickSignal; //!< One can register to this signal to receive pick events.

    WPickInfo m_hitResult; //!< Textual representation of the result of a pick.
    WPickInfo m_startPick; //!< Indicates what was first picked. Should be "" after unpick.
    bool m_shift; //!< Is shift pressed?
    bool m_ctrl; //!< Is ctrl pressed?
    std::string m_viewerName; //!< Which viewer sends the signal
    bool m_paintMode; //!< The paint mode
    WPickInfo::WMouseButton m_mouseButton; //!< Stores mouse button that initiated the pick

    bool m_inPickMode;  //!< If true, the pick handler currently is in pick mode.

    int32_t m_scrollWheel; //!< The virtual value of the scrollwheel
};

#endif  // WPICKHANDLER_H
