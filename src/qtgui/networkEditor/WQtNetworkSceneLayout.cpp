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

#include "core/common/WLogger.h"

#include "WQtNetworkEditor.h"
#include "WQtNetworkScene.h"
#include "WQtNetworkItem.h"
#include "WQtNetworkItemGrid.h"

#include "WQtNetworkSceneLayout.h"

WQtNetworkSceneLayout::WQtNetworkSceneLayout( WQtNetworkScene* /* scene */, WQtNetworkItemGrid* grid ):
    m_grid( grid )
{
    // initialize members
}

WQtNetworkSceneLayout::~WQtNetworkSceneLayout()
{
    // cleanup
}

void WQtNetworkSceneLayout::addItem( WQtNetworkItem* item )
{
    // do we have a default?
    WSharedAssociativeContainer< ModuleDefaultCoordinates >::ReadTicket r = m_moduleDefaultCoords.getReadTicket();
    WSharedAssociativeContainer< ModuleDefaultFlags >::ReadTicket rflags = m_moduleDefaultFlags.getReadTicket();
    ModuleDefaultCoordinates::const_iterator defaultCoord = r->get().find( item->getModule()->getUUID() );
    if( defaultCoord == r->get().end() )
    {
        // NO. No default found. Do naive placement to next free column.
        // add in first row of the next free column
        int nextX = m_grid->getFirstFreeColumn();
        m_grid->setItem( item, nextX, 0 );
    }
    else
    {
        // default found. Place there and mark item as already layed out
        m_grid->setItem( item, ( *defaultCoord ).second );

        ModuleDefaultFlags::const_iterator defaultFlags = rflags->get().find( item->getModule()->getUUID() );
        if( defaultFlags != rflags->get().end() )
        {
            item->setLayedOut( ( *defaultFlags ).second.m_layedOut );
            item->setManuallyPlaced( ( *defaultFlags ).second.m_manuallyLayedOut );
        }
        else    // no default flag found.
        {
            item->setLayedOut( );
        }
    }
}

void WQtNetworkSceneLayout::removeItem( WQtNetworkItem* item )
{
    // remove from grid
    m_grid->removeItem( item );
}

void WQtNetworkSceneLayout::connection( WQtNetworkItem* outItem, WQtNetworkItem* inItem )
{
    // was layouted earlier?
    if( inItem->wasLayedOut() || inItem->wasManuallyPlaced() )
    {
        return;
    }

    // get out item position
    QPoint out = m_grid->whereIs( outItem );
    QPoint in = m_grid->whereIs( outItem );

    // first guess: y + 1
    QPoint target( out.x(), out.y() + 1 );

    // maybe the x position is already occupied?
    while( m_grid->isOccupied( target ) && ( target != in ) )
    {
        target.rx()++;
    }

    // move there
    m_grid->moveItem( inItem, target );
    inItem->setLayedOut();
}

void WQtNetworkSceneLayout::disconnection( WQtNetworkItem* /* outItem */, WQtNetworkItem* /* inItem */ )
{
    // leave item on its current position.
}

void WQtNetworkSceneLayout::snapTemporarily( WQtNetworkItem* item, QPointF worldCoords, bool noPhysicalMove )
{
    // the grid knows where to snap:
    QPoint cell = m_grid->findNearestCell( worldCoords );
    QPoint oldCell = m_grid->whereIs( item );

    if( oldCell != cell )
    {
        bool isUsed = m_grid->isOccupied( cell );
        m_grid->highlightCell( cell, isUsed ? QColor( 230, 40, 40, 128 ) : QColor( 90, 220, 90, 128 ) );
    }
    else
    {
        // explicitly turn of highlight
        m_grid->highlightCell();
    }
    if( !noPhysicalMove )
    {
        m_grid->physicalMoveTo( item, cell, false );
    }
}

void WQtNetworkSceneLayout::snapAccept( WQtNetworkItem* item, QPointF worldCoords )
{
    // disable highlight
    m_grid->highlightCell();

    // something changed?
    QPoint newCell = m_grid->findNearestCell( worldCoords );
    QPoint oldCell = m_grid->whereIs( item );

    if( oldCell != newCell )
    {
        // user moved it somewhere. Mark as already positioned. (But only if start and end cell are different)
        item->setManuallyPlaced();
    }

    // move in layout
    if( !m_grid->moveItem( item, newCell ) )
    {
        m_grid->physicalMoveTo( item, oldCell, true );
    }
}

void WQtNetworkSceneLayout::blendIn()
{
    m_grid->blendIn();
}

void WQtNetworkSceneLayout::blendOut()
{
    m_grid->blendOut();
}

QRectF WQtNetworkSceneLayout::getBoundingBox()
{
    return m_grid->boundingRect();
}

WQtNetworkItemGrid* WQtNetworkSceneLayout::getGrid() const
{
    return m_grid;
}

void WQtNetworkSceneLayout::setModuleDefaultPosition( WModule::SPtr module, QPoint coord )
{
    WSharedAssociativeContainer< ModuleDefaultCoordinates >::WriteTicket w = m_moduleDefaultCoords.getWriteTicket();
    w->get()[ module->getUUID() ] = coord;
}

void WQtNetworkSceneLayout::setModuleDefaultFlags( WModule::SPtr module, bool layedOut, bool manuallyLayedOut )
{
    WSharedAssociativeContainer< ModuleDefaultFlags >::WriteTicket w = m_moduleDefaultFlags.getWriteTicket();
    w->get()[ module->getUUID() ].m_layedOut = layedOut;
    w->get()[ module->getUUID() ].m_manuallyLayedOut = manuallyLayedOut;
}

