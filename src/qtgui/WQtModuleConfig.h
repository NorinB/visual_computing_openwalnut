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

#ifndef WQTMODULECONFIG_H
#define WQTMODULECONFIG_H

#include <map>
#include <vector>
#include <string>

#include <QAction>
#include <QDialog>
#include <QListWidget>
#include <QCheckBox>
#include <QComboBox>

#include "core/kernel/WModule.h"

/**
 * A class which acts as a binary predicate to check exclusion of modules by name using a whitelist and a blacklist. It automatically handles the
 * settings for it and provides proper QActions.
 */
class WQtModuleConfig: public QDialog
{
    Q_OBJECT
public:
    /**
     * Constructs excluder dialog and loads needed settings.
     *
     * \param parent parent widget
     * \param f window flags
     */
    WQtModuleConfig( QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

    /**
     * Destructor.
     */
    virtual ~WQtModuleConfig();

    /**
     * Checks exclusion by name.
     *
     * \param name the name of the module.
     *
     * \return true if it should be excluded.
     */
    bool operator()( std::string const& name ) const;

    /**
     * Checks exclusion by name.
     *
     * \param module the module to check. Internally, the name is used.
     *
     * \return true if it should be excluded.
     */
    bool operator()( WModule::ConstSPtr module ) const;

    /**
     * Creates an action instance allowing the configuration.
     *
     * \return the action which triggers this dialog
     */
    QAction* getConfigureAction() const;

    /**
     * This function initializes the path helper by loading the module path settings. This is needed since the pathhelper needs to know all paths
     * before the GUI really shows up.
     */
    static void initPathHelper();

signals:
    /**
     * Signal getting emitted if the exclusion-lists changes.
     */
    void updated();

public slots:
    /**
     * Uses a modal dialog to allow the user modifying it.
     */
    void configure();

    /**
     * Hides the dialog, updates the internal lists and emits updated-signal.
     */
    virtual void accept();

    /**
     * Hides the dialog, does not update the internal lists.
     */
    virtual void reject();

    /**
     * Add a path to m_pathList;
     */
    virtual void addModulePath();

    /**
     * Remove the selected item from m_pathList;
     */
    virtual void removeModulePath();

private slots:

    /**
     * Call this notify the remove button whether something is selected in m_pathList or not
     */
    virtual void pathListSelectionChanged();

    /**
     * Call this to reset all checkboxes in the list of modules
     */
    void resetAllModuleCheckboxes();

    /**
     * Call this to refresh the list of selected modules, e.g. 
     */
    void refreshModuleCheckboxes();

    /**
     * Call this to show or hide the preset combobox 
     */
    void toggleComboboxVisibility( int );

protected:
private:
    /**
     * The list of available modules.
     */
    std::vector< WModule::ConstSPtr > m_moduleList;

    /**
     * Maps between a name and a checkbox widget.
     */
    typedef std::map< std::string, QCheckBox* > ModuleItemMapType;

    /**
     * List for all allowed/active modules.
     */
    typedef std::vector< std::string > AllowedModuleList;

    /**
     * Maps between module name and item.
     */
    ModuleItemMapType m_moduleItemMap;

    /**
     * The list of modules that are allowed
     */
    AllowedModuleList m_allowedModules;

    /**
     * Reloads the whitelist and the blacklist from the QSettings.
     *
     * \param defaultModulePaths if true, the module path list is set to default too.
     */
    void loadListsFromSettings( bool defaultModulePaths = false );

    /**
     * Call this to refresh the combobox items
     */
    void refreshComboboxItems();

    /**
     * Saves the whitelist and the blacklist to the settings.
     */
    void saveListToSettings();

    /**
     * This widget contains the allowed module list
     */
    QListWidget* m_list;

    /**
     * This list widget contains all additional search paths
     */
    QListWidget* m_pathList;

    /**
     * Checkbox controlling whether all modules should be shown all the time.
     */
    QCheckBox* m_showThemAll;

    /**
     * Control whether the list is interpreted as black list
     */
    QCheckBox* m_asBlackList;

    /**
     * Check if you want to use a preset module list
     */
    QCheckBox* m_usePreset;

    /**
     * Combobox to select a black list
     */
    QComboBox* m_selectPresetBlacklist;

    /**
     * Button responsible for removing the currently selected path in m_pathList.
     */
    QPushButton* m_removePathButton;

private slots:

    /**
     * Triggered by the m_showThemAll checkbox.
     */
    void showThemAllUpdated();

    /**
     * called by the reset button
     */
    void reset();
};

#endif  // WQTMODULECONFIG_H
