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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <QtCore/QDir>
#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>

#include "core/common/WPathHelper.h"
#include "core/kernel/WModuleFactory.h"
#include "WMainWindow.h"
#include "WQtGui.h"
#include "WQtModuleConfig.h"

bool nameSort( WModule::ConstSPtr i, WModule::ConstSPtr j )
{
    return ( i->getName() < j->getName() );
}

WQtModuleConfig::WQtModuleConfig( QWidget* parent, Qt::WindowFlags f ):
    QDialog( parent, f )
{
    // configure the dialog
    setModal( true );

    // some minimum size
    resize( 600, 400 );

    // get a list of all the modules available
    WModuleFactory::PrototypeSharedContainerType::ReadTicket r = WModuleFactory::getModuleFactory()->getPrototypes();
    typedef WModuleFactory::PrototypeContainerConstIteratorType ProtoIter;
    for( ProtoIter iter = r->get().begin(); iter != r->get().end(); ++iter )
    {
        m_moduleList.push_back( *iter );
    }
    std::sort( m_moduleList.begin(), m_moduleList.end(), nameSort );

    // initialize members
    QVBoxLayout* layoutAllowedModules = new QVBoxLayout;
    QWidget* p1 = new QWidget();
    p1->setLayout( layoutAllowedModules );

    QVBoxLayout* layoutModulePaths = new QVBoxLayout;
    QWidget* p2 = new QWidget();
    p2->setLayout( layoutModulePaths );

    // setup tab widget.
    QTabWidget* tab = new QTabWidget( this );
    tab->addTab( p1, "Allowed Modules" );
    tab->addTab( p2, "Module Paths" );
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget( tab );
    setLayout( mainLayout );

    QString helpText = "This dialog allows you to modify the list of modules used everywhere in OpenWalnut. The list contains all loaded modules. "
                       "By default, the list is interpreted as white-list. This means, you have to select the modules you want "
                       "to use and disable those you won't use. You can switch to black-listing. This allows you to select all modules "
                       "that should not be used.";
    QLabel* hint = new QLabel( helpText );
    hint->setWordWrap( true );
    layoutAllowedModules->addWidget( hint );

    QString helpTextPaths = "You can add more search paths here, where OpenWalnut searches modules during startup. Each path is searched "
                            "recursively. Use this list to help OpenWalnut find your downloaded or self-made modules. An alternative option is to "
                            "set the environment variable \"OW_MODULE_PATH\", which is a semicolon-separated list of search paths. After "
                            "restarting OpenWalnut, the modules in the added paths appear in the list of allowed modules.";
    QLabel* hintPaths = new QLabel( helpTextPaths );
    hintPaths->setWordWrap( true );
    layoutModulePaths->addWidget( hintPaths );



    // always show all modules?
    m_showThemAll = new QCheckBox( "Always show all modules.", this );
    m_showThemAll->setToolTip(
        "Recommended option. This ensures that all modules get shown all them time, regardless of the list below."
    );
    connect( m_showThemAll, SIGNAL( stateChanged( int ) ), this, SLOT( showThemAllUpdated() ) );
    layoutAllowedModules->addWidget( m_showThemAll );

    m_asBlackList = new QCheckBox( "Use as black-list", this );
    m_asBlackList->setToolTip( "Activate this option if you want all modules to be active in OpenWalnut that are not explicitly deactivated here." );
    layoutAllowedModules->addWidget( m_asBlackList );

    QHBoxLayout* blacklistPresetRow = new QHBoxLayout();
    layoutAllowedModules->addLayout( blacklistPresetRow );

    m_usePreset = new QCheckBox( "Use a preset module list", this );
    m_usePreset->setToolTip( "Activate this option if you want to use a list of preselected "
                                "modules which may be specific for different research areas. " );
    connect( m_usePreset, SIGNAL( stateChanged( int ) ), this, SLOT( refreshModuleCheckboxes() ) );
    connect( m_usePreset, SIGNAL( stateChanged( int ) ), this, SLOT( toggleComboboxVisibility( int ) ) );
    blacklistPresetRow->addWidget( m_usePreset );

    // Set presets here
    QString presetSIVERT = "Anisotropic Filter,Calculate GFA,Calculate Tensors,Cluster Display,ClusterDisplayVoxels,"
                            "Data Type Conversion,Diffusion Tensor Scalars,EEG View,Effective Connectivity Cluster,Fiber Data Creator,"
                            "Fiber translator,Functional MRI Viewer,Hierarchical Clustering Display,Image Space LIC,Image Space Tensor LIC,"
                            "Merge Components To Vector,Mori Det. Tracking,Partition To Mesh,Picking in DVR Evaluation,"
                            "Probabilistic Tract Rendering with multi transparent iso surfaces.,"
                            "Read Amira Mesh,Read Dipoles,Read Raw Data,Read Simple Text Line Data,Read Spherical Harmonics,Read VCL,"
                            "Read VIM,Scalar Data Creator,Spline Surface,Superquadric Glyphs,Surface Parameter Animator,"
                            "Template,Template Colormapping,Template Containers,Template Data Loader,Template Render Pipelines,"
                            "Template Shaders,Template UI,Vector Align,Vector Data Creator,Vector Normalize,Vector Operator,"
                            "Vector Plot,Vector Scaling,WebGL Support,Write Amira Mesh,Write Dendrogram,";

    WQtGui::getSettings().setValue( "qtgui/modules/preset/ ", QString::fromStdString( "" ) );
    WQtGui::getSettings().setValue( "qtgui/modules/preset/SIVERT", presetSIVERT );

    // combobox for black-list presets
    m_selectPresetBlacklist = new QComboBox( this );
    m_selectPresetBlacklist->setDisabled( true );
    m_selectPresetBlacklist->setToolTip( "Select a preset or create a new one by selecting modules in the list below "
                                            "and type in a name here." );
    m_selectPresetBlacklist->setFixedSize( 120, 26 );
    m_selectPresetBlacklist->setEditable( true );
    m_selectPresetBlacklist->setInsertPolicy( QComboBox::InsertAtBottom );

    refreshComboboxItems();

    if( m_asBlackList->checkState() )
    {
        m_selectPresetBlacklist->setDisabled( false );
    }
    connect( m_selectPresetBlacklist, SIGNAL( currentIndexChanged( int ) ), this, SLOT( refreshModuleCheckboxes() ) );
    blacklistPresetRow->addWidget( m_selectPresetBlacklist );
    QSpacerItem* horizSpacer = new QSpacerItem( 1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed );
    blacklistPresetRow->addSpacerItem( horizSpacer );

    // create the module list
    m_list = new QListWidget();
    layoutAllowedModules->addWidget( m_list );

    // the path list
    m_pathList = new QListWidget();
    layoutModulePaths->addWidget( m_pathList );

    // the path list also needs some add/remove buttons
    QHBoxLayout* addRemLayout = new QHBoxLayout();
    QWidget* addRemWidget = new QWidget();
    addRemWidget->setLayout( addRemLayout );
    layoutModulePaths->addWidget( addRemWidget );
    QPushButton* addButton = new QPushButton( "Add Path" );
    m_removePathButton = new QPushButton( "Remove Path" );
    m_removePathButton->setEnabled( false );
    addRemLayout->addWidget( addButton );
    addRemLayout->addWidget( m_removePathButton );

    connect( addButton, SIGNAL( clicked( bool ) ), this, SLOT( addModulePath() ) );
    connect( m_removePathButton, SIGNAL( clicked( bool ) ), this, SLOT( removeModulePath() ) );
    connect( m_pathList, SIGNAL( itemSelectionChanged() ), this, SLOT( pathListSelectionChanged() ) );

    // for modules without icon, use this
    QIcon noIcon = WQtGui::getMainWindow()->getIconManager()->getIcon( "DefaultModuleIcon" );

    // fill the list item
    for( std::vector< WModule::ConstSPtr >::const_iterator iter = m_moduleList.begin(); iter != m_moduleList.end(); ++iter )
    {
        // Create a custom widget which contains the name and description
        QWidget* widget = new QWidget( m_list );
        {
            QGridLayout* layoutWidget = new QGridLayout();

            QSizePolicy sizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ); // <-- scale it down

            int column = 0;

            // create a checkbox for this module
            QCheckBox* check = new QCheckBox();
            check->setSizePolicy( sizePolicy );
            layoutWidget->addWidget( check, 0, 0, 2, 1 );

            // we later need to find the checkbox for one module easily:
            m_moduleItemMap[ ( *iter )->getName() ] = check;

            ++column;

            // now, an icon
            QLabel* icon = new QLabel();
            icon->setSizePolicy( sizePolicy );

            // we need to enforce some size
            QIcon modIco = WQtGui::getMainWindow()->getIconManager()->getIcon( ( *iter )->getName(), noIcon );
            QPixmap qicon( modIco.pixmap( 32, 32 ) );
            qicon = qicon.scaled( 32, 32, Qt::KeepAspectRatio );
            icon->setPixmap( qicon );

            layoutWidget->addWidget( icon, 0, column, 2, 1 );
            ++column;

            // Add Name and Description
            layoutWidget->addWidget( new QLabel( "<b>" + QString::fromStdString( ( *iter )->getName() )+ "</b>" ), 0, column );
            // if there is no description -> no widget added to save space
            if( !( *iter )->getDescription().empty() )
            {
                layoutWidget->addWidget(  new QLabel( QString::fromStdString( ( *iter )->getDescription() ) ), 1, column );
            }

            layoutWidget->setSizeConstraint( QLayout::SetMaximumSize );
            widget->setLayout( layoutWidget );
        }

        QListWidgetItem* item = new QListWidgetItem( m_list );
        item->setSizeHint( widget->sizeHint() );

        m_list->addItem( item );
        m_list->setItemWidget( item, widget );
        m_list->setMinimumHeight( 150 );
    }

    // provide some default buttons here
    QDialogButtonBox* defButtons = new QDialogButtonBox( QDialogButtonBox::Save | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults,
                                                         Qt::Horizontal, this );
    connect( defButtons, SIGNAL( accepted() ), this, SLOT( accept() ) );
    connect( defButtons, SIGNAL( rejected() ), this, SLOT( reject() ) );
    connect( defButtons->button( QDialogButtonBox::RestoreDefaults ), SIGNAL( clicked() ), this, SLOT( reset() ) );
    mainLayout->addWidget( defButtons );

    // initialize the widgets
    loadListsFromSettings();
}

WQtModuleConfig::~WQtModuleConfig()
{
    // cleanup
}

void WQtModuleConfig::initPathHelper()
{
    // we allow the user to specify additional module paths. They need to be loaded before the WModuleFactory initiates the module-load stuff.
    // Therefore, we grab the setting here and add it to WPathHelper
    QList< QVariant > paths = WQtGui::getSettings().value( "qtgui/additionalModulePaths" ).toList();
    for( QList< QVariant >::const_iterator it = paths.begin(); it != paths.end(); ++it )
    {
        std::string p = ( *it ).toString().toStdString();
        WPathHelper::getPathHelper()->addAdditionalModulePath( p );
    }
}

void WQtModuleConfig::loadListsFromSettings( bool defaultModulePaths )
{
    // update checkbox too
    bool ignoreAllowedList = WQtGui::getSettings().value( "qtgui/modules/IgnoreAllowedList", true ).toBool();
    m_showThemAll->setCheckState( ignoreAllowedList ? Qt::Checked : Qt::Unchecked );

    bool asBlackList = WQtGui::getSettings().value( "qtgui/modules/asBlackList", false ).toBool();
    m_asBlackList->setCheckState( asBlackList ? Qt::Checked : Qt::Unchecked );

    bool usePreset = WQtGui::getSettings().value( "qtgui/modules/usePreset", false ).toBool();
    m_usePreset->setCheckState( usePreset ? Qt::Checked : Qt::Unchecked );

    if( !defaultModulePaths )
    {
        // now, also fill the list
        // NOTE: we do not use the list in WPathHelper. This list will NOT be updated directly to ensure consistency between the path list in
        // WPathHelper and the loaded modules in WModuleFactory. WPathHelper is set correctly on next restart.
        QList< QVariant > paths = WQtGui::getSettings().value( "qtgui/additionalModulePaths" ).toList();
        for( QList< QVariant >::const_iterator it = paths.begin(); it != paths.end(); ++it )
        {
            std::string p = ( *it ).toString().toStdString();
            m_pathList->addItem( QString::fromStdString( p ) );
        }
    }
}

void WQtModuleConfig::saveListToSettings()
{
    // rebuild list of allowed modules
    m_allowedModules.clear();
    std::string allowedAsString;    // this is needed since QList cannot be stored in a QSettings in a read-able format right now.

    // iterate the widgets and store in settings:
    for( ModuleItemMapType::const_iterator iter = m_moduleItemMap.begin(); iter != m_moduleItemMap.end(); ++iter )
    {
        // if it is checked, use.
        if( iter->second->checkState() == Qt::Checked ) // save only checked items
        {
            m_allowedModules.push_back( iter->first );
            allowedAsString += iter->first + ",";
        }
    }

    // store this list in settings
    WQtGui::getSettings().setValue( "qtgui/modules/allowedList", QString::fromStdString( allowedAsString ) );
    WQtGui::getSettings().setValue( "qtgui/modules/IgnoreAllowedList", ( m_showThemAll->checkState() == Qt::Checked ) );
    WQtGui::getSettings().setValue( "qtgui/modules/asBlackList", ( m_asBlackList->checkState() == Qt::Checked ) );

    WQtGui::getSettings().setValue( "qtgui/modules/usePreset", m_usePreset->checkState() );
    WQtGui::getSettings().setValue( "qtgui/modules/selectedPreset", m_selectPresetBlacklist->currentText() );

    // -1 means, that the preset name is not in the list of presets
    if( m_selectPresetBlacklist->findText( m_selectPresetBlacklist->currentText() ) == -1 )
    {
        WQtGui::getSettings().setValue( "qtgui/modules/preset/" + m_selectPresetBlacklist->currentText(), QString::fromStdString( allowedAsString ) );
    }

    // also write the path list
    QList< QVariant > paths;
    for( int i = 0; i < m_pathList->count(); ++i )
    {
        paths.push_back( m_pathList->item( i )->text() );
    }
    WQtGui::getSettings().setValue( "qtgui/additionalModulePaths", paths );
}

bool WQtModuleConfig::operator()( std::string const& name ) const
{
    bool blackList = ( m_asBlackList->checkState() == Qt::Checked );
    bool ignoreList = ( m_showThemAll->checkState() == Qt::Checked );
    bool isInList = ( std::find( m_allowedModules.begin(), m_allowedModules.end(), name ) != m_allowedModules.end() );

    return !ignoreList && ( ( blackList && isInList ) || ( !blackList && !isInList ) );
}

bool WQtModuleConfig::operator()( WModule::ConstSPtr module ) const
{
    return operator()( module->getName() );
}

void WQtModuleConfig::configure()
{
    show();
}

QAction* WQtModuleConfig::getConfigureAction() const
{
    QAction* a = new QAction( "Configure Modules", parent() );
    a->setToolTip( "Allows you to configure the list of modules, which is used for selecting modules in OpenWalnut (i.e. in the toolbar)." );
    connect( a, SIGNAL( triggered( bool ) ), this, SLOT( configure() ) );
    return a;
}

void WQtModuleConfig::accept()
{
    saveListToSettings();
    refreshComboboxItems();
    emit updated();
    QDialog::accept();
}

void WQtModuleConfig::reject()
{
    // reset everything to the current state in the settings:
    loadListsFromSettings();

    QDialog::reject();
}

void WQtModuleConfig::showThemAllUpdated()
{
    if( m_showThemAll->checkState() == Qt::Checked )
    {
        m_list->setDisabled( true );
    }
    else
    {
        m_list->setDisabled( false );
    }
}

void WQtModuleConfig::reset()
{
    m_pathList->clear();

    resetAllModuleCheckboxes();
    loadListsFromSettings( true );

    m_showThemAll->setCheckState( Qt::Unchecked );
    m_asBlackList->setCheckState( Qt::Unchecked );
    m_usePreset->setCheckState( Qt::Unchecked );

    m_list->setDisabled( false );
}

void WQtModuleConfig::addModulePath()
{
    QString dir = QFileDialog::getExistingDirectory( this, "Select Directory",
                                                    QString::fromStdString( WPathHelper::getHomePath().string() ),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog );
    m_pathList->addItem( dir );
}

void WQtModuleConfig::removeModulePath()
{
    qDeleteAll( m_pathList->selectedItems() );
}

void WQtModuleConfig::pathListSelectionChanged()
{
    if( m_pathList->selectedItems().size() )
    {
        m_removePathButton->setEnabled( true );
    }
    else
    {
        m_removePathButton->setEnabled( false );
    }
}

void WQtModuleConfig::resetAllModuleCheckboxes()
{
    for( std::vector< WModule::ConstSPtr >::const_iterator iter = m_moduleList.begin(); iter != m_moduleList.end(); ++iter )
    {
        // we later need to find the checkbox for one module easily:
        m_moduleItemMap[ ( *iter )->getName() ]->setCheckState( Qt::Unchecked );
    }
}

void WQtModuleConfig::refreshModuleCheckboxes()
{
    resetAllModuleCheckboxes();
    std::string allowedModules = "";

    // read settings
    if( m_usePreset->isChecked() )
    {
        allowedModules = WQtGui::getSettings().value( "qtgui/modules/preset/" + m_selectPresetBlacklist->currentText(), "" ).toString().toStdString();
    }
    else
    {
        allowedModules = WQtGui::getSettings().value( "qtgui/modules/allowedList", "" ).toString().toStdString();
    }

    m_allowedModules = string_utils::tokenize( allowedModules, "," );

    // set dialog according to the settings
    for( AllowedModuleList::const_iterator iter = m_allowedModules.begin(); iter != m_allowedModules.end(); ++iter )
    {
        if( m_moduleItemMap.count( *iter ) )
        {
            m_moduleItemMap[ *iter ]->setCheckState( Qt::Checked );
        }
    }
}

void WQtModuleConfig::toggleComboboxVisibility( int usePresetState )
{
    // 0 = checkbox not ticked, 2 = checkbox is ticked
    if( usePresetState == 0 )
    {
        m_selectPresetBlacklist->setDisabled( true );
    }
    else
    {
        m_selectPresetBlacklist->setDisabled( false );
    }
}

void WQtModuleConfig::refreshComboboxItems()
{
    //Clear list before updating
    m_selectPresetBlacklist->clear();

    // read preset names from settings
    QSettings* settings = &WQtGui::getSettings();
    settings->beginGroup( "qtgui/modules/preset/" );
    QStringList childKeys = settings->childKeys();
    m_selectPresetBlacklist->addItems( childKeys );
    settings->endGroup();

    int selectedPresetIndex = m_selectPresetBlacklist->findText( WQtGui::getSettings().value( "qtgui/modules/selectedPreset", "" ).toString() );
    // -1 means selectedPresetIndex not found
    if( selectedPresetIndex != -1 )
    {
        m_selectPresetBlacklist->setCurrentIndex( selectedPresetIndex );
    }
    else
    {
        m_selectPresetBlacklist->setCurrentIndex( 0 );
    }
}
