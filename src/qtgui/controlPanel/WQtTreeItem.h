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

#ifndef WQTTREEITEM_H
#define WQTTREEITEM_H

#include <memory>
#include <string>
#include <vector>

#include <QProgressBar>
#include <QTreeWidgetItem>
#include <QtCore/QTimer>
#include <boost/signals2/connection.hpp>

#include "WTreeItemTypes.h"
#include "core/kernel/WModule.h"

/**
 * Base class for all items in the control panel tree.
 */
class WQtTreeItem: public QObject,
                   public QTreeWidgetItem
{
    Q_OBJECT

public:
    /**
     * Constructor creates an empty item.
     *
     * \param parent The widget managing this widget
     * \param module The represented module
     * \param type the type used for the treeitem. Used to identify the items.
     */
    WQtTreeItem( QTreeWidgetItem* parent, WTreeItemType type, std::shared_ptr< WModule > module );

    /**
     * Destructor.
     */
    virtual ~WQtTreeItem();

    /**
     * Get for the module pointer.
     *
     * \return the pointer to the module associated with this item.
     */
    WModule::SPtr getModule();

    /**
     * Returns the name used for this tree item.
     *
     * \return the name.
     */
    std::string getName();

    /**
     * Gets called by the GUI whenever the module was removed from the root container and should now be deleted.
     */
    virtual void gotRemoved();

    /**
     * The name of the input represented by this item.
     *
     * \return handled input
     */
    std::string getHandledInput() const;

    /**
     * Sets the name of the input represented by this item.
     *
     * \param in the input name.
     */
    void setHandledInput( std::string in );

    /**
     * The name of the output represented by this item.
     *
     * \return handled output
     */
    std::string getHandledOutput() const;

    /**
     * Sets the name of the output represented by this item.
     *
     * \param out the output name.
     */
    void setHandledOutput( std::string out );

    /**
     * Handle changes in check state.
     */
    virtual void handleCheckStateChange();

    /**
     * Create tooltip for a given module. This can be used by all the widgets needing a tooltip for a module.
     *
     * \param module the module to create the tooltip for
     *
     * \return the tooltip.
     */
    static std::string createTooltip( WModule::SPtr module );
public slots:

    /**
     * Gets called by m_updateTimer in some interval to update the item state, basing on the state of m_module.
     */
    void update();

protected:
    /**
     * Updates the state of the tree item basing on the module's state.
     */
    virtual void updateState();

    /**
     * Updates this item in regular intervals.
     */
    std::shared_ptr< QTimer > m_updateTimer;

    /**
     * Name of the tree item.
     */
    std::string m_name;

    /**
     * True if the treeitem and the module gets deleted currently.
     */
    bool m_deleteInProgress;

    /**
     * True if no delete event has been posted yet.
     */
    bool m_needPostDeleteEvent;

    /**
     * The property containing the name of the module.
     */
    WPropString m_nameProp;

    /**
     * The name of the input connector represented by this item.
     */
    std::string m_handledInput;

    /**
     * The output name handled by this item
     */
    std::string m_handledOutput;

private:
    /**
     * The module represented by this tree item.
     */
    std::shared_ptr< WModule > m_module;

    /**
     * Called when the name property changes.
     */
    void nameChanged();

    /**
     * The output connector update connections. The NEED to be disconnected on destruction manually!
     */
    std::vector< boost::signals2::connection > m_outputUpdateConnections;

    /**
     * Called on output-connector update.
     *
     * \param connector the connector that was updated.
     */
    void slotDataChanged( std::shared_ptr< WModuleConnector > connector );
};

#endif  // WQTTREEITEM_H
