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

#include <iostream>

#include "QPainter"
#include "QStyleOption"
#include "QGraphicsSceneMouseEvent"

#include "WTransferFunction2DBackground.h"
#include "WTransferFunction2DGUIWidget.h"

WTransferFunction2DBackground::WTransferFunction2DBackground( QWidget * /*parent*/ ) : BaseClass()
{
    setOpacity( 1.0 );
    setZValue( -1 );
    setPos( QPointF( 0, 0 ) );
}

void WTransferFunction2DBackground::setMyPixmap( const QPixmap& newpixmap )
{
    if( newpixmap.width() > 0 && newpixmap.height() > 0 )
    {
        QTransform m( scene()->sceneRect().width()/( double )newpixmap.width(), 0, 0,
                      0, scene()->sceneRect().height()/( double )newpixmap.height(), 0,
                      0, 0, 1 );
        setTransform( m );
    }
    BaseClass::setPixmap( newpixmap );
}

WTransferFunction2DBackground::~WTransferFunction2DBackground()
{
}

QRectF WTransferFunction2DBackground::boundingRect() const
{
    return scene()->sceneRect();
}

