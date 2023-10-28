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

#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QWidgetAction>

#include "../WQtGui.h"
#include "../WMainWindow.h"
#include "../WIconManager.h"

#include "core/common/WLogger.h"

#include "../controlPanel/WQtPropertyGroupWidget.h"
#include "WQtPropertyBoolAction.h"
#include "WQtPropertyTriggerAction.h"
#include "WQtDockTitleWidget.h"

#include "WQtDockWidget.h"

WQtDockWidget::WQtDockWidget( const QString& title, QWidget* parent, Qt::WindowFlags flags ):
    QDockWidget( title, parent, flags )
{
    setObjectName( title );

    // thats it. we now have the title bar
    m_titleBar = new WQtDockTitleWidget( this );
    setTitleBarWidget( m_titleBar );
    m_titleBar->updateHelp();

    // some standard dock features
    setAllowedAreas( Qt::AllDockWidgetAreas );
    setFeatures( QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable );
}

WQtDockWidget::WQtDockWidget( QWidget* parent, Qt::WindowFlags flags ):
    QDockWidget( parent, flags )
{
    // thats it. we now have the title bar
    m_titleBar = new WQtDockTitleWidget( this );
    setTitleBarWidget( m_titleBar );
    m_titleBar->updateHelp();

    // some standard dock features
    setAllowedAreas( Qt::AllDockWidgetAreas );
    setFeatures( QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable );
}

WQtDockWidget::~WQtDockWidget()
{
    // cleanup
}

void WQtDockWidget::addTitleAction( QAction* action, bool instantPopup )
{
    m_titleBar->addTitleAction( action, instantPopup );
}

void WQtDockWidget::addTitleButton( QToolButton* button )
{
    m_titleBar->addTitleButton( button );
}

void WQtDockWidget::removeTitleAction( QAction* action )
{
    m_titleBar->removeTitleAction( action );
}

void WQtDockWidget::addTitleSeperator()
{
    m_titleBar->addTitleSeperator();
}

void WQtDockWidget::addTitleWidget( QWidget* widget )
{
    m_titleBar->addTitleWidget( widget );
}

void WQtDockWidget::removeTitleWidget( QWidget* widget )
{
    m_titleBar->removeTitleWidget( widget );
}

void WQtDockWidget::setHelpContext( const QString& id )
{
    m_helpContextId = id;
    m_titleBar->updateHelp();
}

const QString& WQtDockWidget::getHelpContext()
{
    return m_helpContextId;
}

void WQtDockWidget::showHelp()
{
    // do something here
}

void WQtDockWidget::saveSettings()
{
    WQtGui::getSettings().setValue( objectName() + "/geometry", saveGeometry() );
}

void WQtDockWidget::restoreSettings()
{
    // nothing to do
    restoreGeometry( WQtGui::getSettings().value( objectName() + "/geometry", "" ).toByteArray() );
}

void WQtDockWidget::closeEvent( QCloseEvent *event )
{
    saveSettings();
    QDockWidget::closeEvent( event );
}

void WQtDockWidget::disableCloseButton( bool disable )
{
    m_titleBar->disableCloseButton( disable );
}

void WQtDockWidget::addTitleProperty( WPropTrigger prop, WGEImage::SPtr icon )
{
    WQtPropertyTriggerAction* propAction = new WQtPropertyTriggerAction( prop, this );
    if( !icon )
    {
        propAction->setIcon(  WQtGui::getMainWindow()->getIconManager()->getIcon( "configure" ) );
    }
    else
    {
        propAction->setIcon( WIconManager::convertToIcon( icon ) );
    }

    addTitleAction( propAction );
}

void WQtDockWidget::addTitleProperty( WPropBool prop, WGEImage::SPtr icon )
{
    WQtPropertyBoolAction* propAction = new WQtPropertyBoolAction( prop, this );
    if( !icon )
    {
        propAction->setIcon(  WQtGui::getMainWindow()->getIconManager()->getIcon( "configure" ) );
    }
    else
    {
        propAction->setIcon( WIconManager::convertToIcon( icon ) );
    }

    addTitleAction( propAction );
}

void WQtDockWidget::addTitleProperty( WPropGroup prop, WGEImage::SPtr icon )
{
    // create property widgets for each effect
    WQtPropertyGroupWidget* viewPropsWidget = WQtPropertyGroupWidget::createPropertyGroupWidget( prop );
    QWidget* viewPropsBox =  WQtPropertyGroupWidget::createPropertyGroupBox( viewPropsWidget );

    // create container for all the config widgets
    QWidget* viewConfigWidget = new QWidget();
    QVBoxLayout* viewConfigLayout = new QVBoxLayout();
    viewConfigLayout->setAlignment( Qt::AlignTop );
    viewConfigWidget->setLayout( viewConfigLayout );

    // force the widget to shrink when the content shrinks.
    QSizePolicy sizePolicy( QSizePolicy::Preferred, QSizePolicy::Maximum );
    sizePolicy.setHorizontalStretch( 0 );
    sizePolicy.setVerticalStretch( 0 );
    viewConfigWidget->setSizePolicy( sizePolicy );

    // add the property widgets to container
    viewConfigLayout->addWidget( viewPropsBox );

    // Create the toolbutton and the menu containing the config widgets
    QWidgetAction* viewerConfigWidgetAction = new QWidgetAction( this );
    viewerConfigWidgetAction->setDefaultWidget( viewConfigWidget );
    QMenu* viewerConfigMenu = new QMenu();
    viewerConfigMenu->addAction( viewerConfigWidgetAction );

    QToolButton* viewerConfigBtn = new QToolButton( this );
    viewerConfigBtn->setPopupMode( QToolButton::InstantPopup );

    if( !icon )
    {
        viewerConfigBtn->setIcon(  WQtGui::getMainWindow()->getIconManager()->getIcon( "configure" ) );
    }
    else
    {
        viewerConfigBtn->setIcon( WIconManager::convertToIcon( icon ) );
    }

    viewerConfigBtn->setToolTip( QString::fromStdString( prop->getDescription() ) );
    viewerConfigBtn->setMenu( viewerConfigMenu );

    // hide config button when properties are hidden
    connect( viewPropsWidget, SIGNAL( hideSignal( bool ) ), viewerConfigBtn, SLOT( setHidden( bool ) ) );

    addTitleButton( viewerConfigBtn );
}
