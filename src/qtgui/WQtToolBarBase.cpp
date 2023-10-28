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

#include "WMainWindow.h"

#include "WSettingMenu.h"

#include "WQtToolBarBase.h"

WQtToolBarBase::WQtToolBarBase( const QString& title, WMainWindow* parent ):
    QToolBar( title, parent )
{
    setObjectName( title );

    setAllowedAreas( Qt::AllToolBarAreas );

    setMinimumWidth( 60 );
    setMinimumHeight( 40 );

    // automatism for toolbar style
    QList< QString > styleOptions;
    styleOptions.push_back( "Icon Only" );
    styleOptions.push_back( "Text Only" );
    styleOptions.push_back( "Text Besides Icon" );
    styleOptions.push_back( "Text Under Icon" );
    styleOptions.push_back( "Follow Style" );
    m_styleOptionMenu = new WSettingMenu( parent, "qtgui/" + windowTitle().toStdString() + "toolbarStyle",
                                                  title.toStdString(),
                                                  "Allows one to change the style of toolbars.",
                                                  0,
                                                  styleOptions );
    connect( m_styleOptionMenu, SIGNAL( change( unsigned int ) ), this, SLOT( handleStyleUpdate( unsigned int ) ) );
    handleStyleUpdate( m_styleOptionMenu->get() );
}

WQtToolBarBase::~WQtToolBarBase()
{
    // cleanup
}

QMenu* WQtToolBarBase::getStyleMenu( QString title ) const
{
    m_styleOptionMenu->setTitle( title );
    return m_styleOptionMenu;
}

void WQtToolBarBase::handleStyleUpdate( unsigned int index )
{
    setToolButtonStyle( static_cast< Qt::ToolButtonStyle >( index ) );
}

