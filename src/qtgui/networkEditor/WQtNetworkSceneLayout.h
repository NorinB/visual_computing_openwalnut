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

#ifndef WQTNETWORKSCENELAYOUT_H
#define WQTNETWORKSCENELAYOUT_H

#include <map>
#include <memory>
#include <string>
#include <utility>


#include "core/common/WSharedAssociativeContainer.h"

class WQtNetworkEditor;
class WQtNetworkScene;
class WQtNetworkItem;
class WQtNetworkItemGrid;

/**
 * Layout manager class for a QGraphicsScene. As the QGraphicsScene itself does not provide virtual methods for item addition and removal, we
 * need to write a separate layout class.
 */
class WQtNetworkSceneLayout
{
public:
    /**
     * Convenience typedef for a std::shared_ptr< WQtNetworkSceneLayout >.
     */
    typedef std::shared_ptr< WQtNetworkSceneLayout > SPtr;

    /**
     * Convenience typedef for a std::shared_ptr< const WQtNetworkSceneLayout >.
     */
    typedef std::shared_ptr< const WQtNetworkSceneLayout > ConstSPtr;

    /**
     * Default constructor.
     *
     * \param scene the scene to manage
     * \param grid the grid to work in
     */
    WQtNetworkSceneLayout( WQtNetworkScene* scene, WQtNetworkItemGrid* grid );

    /**
     * Destructor.
     */
    virtual ~WQtNetworkSceneLayout();

    /**
     * Add an item to the layout
     *
     * \param item the item to add.
     */
    virtual void addItem( WQtNetworkItem* item );

    /**
     * Remove the item from the layout
     *
     * \param item the item to remove
     */
    virtual void removeItem( WQtNetworkItem* item );

    /**
     * Two module got connected.
     *
     * \param outItem the output module
     * \param inItem the input module
     */
    virtual void connection( WQtNetworkItem* outItem, WQtNetworkItem* inItem );

    /**
     * Two modules got disconnected.
     *
     * \param outItem the output module
     * \param inItem the input module
     */
    void disconnection( WQtNetworkItem* outItem, WQtNetworkItem* inItem );

    /**
     * Snap the item to the nearest layout element. The coordinates specified are in world space. The snapping is temporary. You can undo it or
     * accept it later to actually modify layout.
     *
     * \param item the item
     * \param worldCoords world space coordinates
     * \param noPhysicalMove disable movement of item if you handle it for yourself
     */
    void snapTemporarily( WQtNetworkItem* item, QPointF worldCoords, bool noPhysicalMove = false );

    /**
     * Accept the current item position and update layout accordingly.
     *
     * \param item the item
     * \param worldCoords world space coordinates
     */
    void snapAccept( WQtNetworkItem* item, QPointF worldCoords );

    /**
     * Allows blending in the underlaying layout structure.
     */
    void blendIn();

    /**
     * Allows blending out the underlaying layout structure.
     */
    void blendOut();

    /**
     * Return the bounding box of this layout.
     *
     * \return the bb
     */
    QRectF getBoundingBox();

    /**
     * Get the grid used for the layout.
     *
     * \return the grid.
     */
    WQtNetworkItemGrid* getGrid() const;

    /**
     * Set a default position for a given module. The layouter will position a module at the given coordinate now, or in future.
     *
     * \param module the module
     * \param coord the coordinate
     */
    void setModuleDefaultPosition( WModule::SPtr module, QPoint coord );

    /**
     * Set a default flag combination for the given module. The layouter might use them.
     *
     * \param module the module
     * \param layedOut flag if the item was layed out already.
     * \param manuallyLayedOut flag if the item was manually layed out.
     */
    void setModuleDefaultFlags( WModule::SPtr module, bool layedOut, bool manuallyLayedOut );

protected:
private:
    WQtNetworkItemGrid* m_grid; //!< we use a grid to place the items

    /**
     * Map between module UUID and network coord
     */
    typedef std::map< std::string, QPoint > ModuleDefaultCoordinates;

    /**
     * Some flags used in the layouter as defaults.
     */
    struct LayoutFlags
    {
        /**
         * Automatically layed out
         */
        bool m_layedOut;

        /**
         * Manual layout done
         */
        bool m_manuallyLayedOut;
    };

    /**
     * Map between module UUID and network flags
     */
    typedef std::map< std::string, LayoutFlags > ModuleDefaultFlags;

    /**
     * The type inside the map
     */
    typedef std::pair< std::string, QPoint > ModuleDefaultCoordinatesItem;

    /**
     * The mapping of network coordinates for each module. This is wrapped by a thread save WSharedObject, since the loader might run in a thread
     * that is not the GUI thread.
     */
    WSharedAssociativeContainer< ModuleDefaultCoordinates > m_moduleDefaultCoords;

    /**
     * The mapping of network flags for each module. This is wrapped by a thread save WSharedObject, since the loader might run in a thread
     * that is not the GUI thread.
     */
    WSharedAssociativeContainer< ModuleDefaultFlags > m_moduleDefaultFlags;
};

#endif  // WQTNETWORKSCENELAYOUT_H

