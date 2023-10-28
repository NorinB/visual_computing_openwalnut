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

#include <QMenu>
#include <QKeyEvent>
#include "QGraphicsSceneContextMenuEvent"
#include "QApplication"
#include "QBrush"
#include "QPainter"
#include "QColorDialog"
#include "QGraphicsScene"
#include "QPolygonF"

#include "WTransferFunction2DTriangle.h"
#include "WTransferFunction2DTriangleWidget.h"

#include "core/common/WLogger.h"

WTransferFunction2DTriangleWidget::WTransferFunction2DTriangleWidget( WTransferFunction2DGUIWidget *parent,
                                                                      WTransferFunction2DTriangle triangle,
                                                                      QColor color )
{
    setFlag( ItemIsMovable );
    setFlag( ItemSendsScenePositionChanges );
    setFlag( ItemIsSelectable );
    setFlag( ItemIsFocusable );

    setZValue( 3 );
    // Note: this is the local coordinate system of the box widget, not of the scene
    m_triangle = triangle;
    m_parent = parent;
    m_color = color;
    m_resizePoints = NONE;

    m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_triangle.left(), LEFT_TRI ) );
    m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_triangle.mid(), MID_TRI ) );
    m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_triangle.right(), RIGHT_TRI ) );


    connect( m_controlPoints[0], SIGNAL( resizeHandleChanged( ResizePoints, QPointF ) ),
            this, SLOT( setResizeHandle( ResizePoints, QPointF ) ) );
    connect( m_controlPoints[1], SIGNAL( resizeHandleChanged( ResizePoints, QPointF ) ),
            this, SLOT( setResizeHandle( ResizePoints, QPointF ) ) );
    connect( m_controlPoints[2], SIGNAL( resizeHandleChanged( ResizePoints, QPointF ) ),
            this, SLOT( setResizeHandle( ResizePoints, QPointF ) ) );
}

WTransferFunction2DTriangleWidget::~WTransferFunction2DTriangleWidget()
{
}

QRectF WTransferFunction2DTriangleWidget::boundingRect() const
{
    return m_triangle.getTriangle().boundingRect();
}

void WTransferFunction2DTriangleWidget::setControlPointsToCorner()
{
    prepareGeometryChange();
    m_controlPoints[0]->setPos( m_triangle.left() );    // top right
    m_controlPoints[1]->setPos( m_triangle.mid() ); // bottom right
    m_controlPoints[2]->setPos( m_triangle.right() );  // bottom left
    // We also need to update the m_width and m_height property of the box
    //m_width = (m_box.right() - m_box.left());
    //m_height = (m_box.bottom() - m_box.top());
    update();
    m_parent->dataChanged();
}

QVariant WTransferFunction2DTriangleWidget::itemChange( GraphicsItemChange change, const QVariant &value )
{
    if( change == ItemPositionChange && scene() )
    {
        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        // We create a bounding reactangle with the size of the parent bounds.
        // Because this Rect is always moved when moving the widget,
        // we have to translate it back into (0,0) of the parent bounds
        // by using the inverse of the origin of this widget
        rect.translate( -this->boundingRect().topLeft() );
        rect.setRight( rect.right() - ( this->boundingRect().width() ) - 1 );
        rect.setBottom( rect.bottom() - ( this->boundingRect().height() ) - 1 );

        if( !rect.contains( newPos ) )
        {
            // Keep the item inside the scene
            newPos.setX( qMin( rect.right(), qMax( newPos.x(), rect.left() ) ) );
            newPos.setY( qMin( rect.bottom(), qMax( newPos.y(), rect.top() ) ) );

            return newPos;
        }
    }
    return QGraphicsItem::itemChange( change, value );
}

void WTransferFunction2DTriangleWidget::setColor( QColor color )
{
    m_color = color;
    this->update();
    m_parent->dataChanged();
}

void WTransferFunction2DTriangleWidget::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{
    QBrush brush( m_color );
    painter->setBrush( brush );
    painter->drawPolygon( m_triangle.getTriangle(), Qt::OddEvenFill );
}

void WTransferFunction2DTriangleWidget::setResizeHandle( ResizePoints handle, QPointF position )
{
    m_resizePoints = handle;
    prepareGeometryChange();
    switch( m_resizePoints )
    {
    case LEFT_TRI:
        m_triangle.setLeft( position );
        setControlPointsToCorner();
        break;
    case MID_TRI:
        m_triangle.setMid( position );
        setControlPointsToCorner();
        break;
    case RIGHT_TRI:
        m_triangle.setRight( position );
        setControlPointsToCorner();
        break;
    default:
        break;
    }
    update();
    m_parent->dataChanged();
}

void WTransferFunction2DTriangleWidget::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    update();
    m_parent->dataChanged();
    QGraphicsItem::mousePressEvent( event );
}

void WTransferFunction2DTriangleWidget::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
    update();
    m_parent->dataChanged();
    QGraphicsItem::mouseMoveEvent( event );
}

void WTransferFunction2DTriangleWidget::mouseReleaseEvent( QGraphicsSceneMouseEvent *event )
{
    update();
    m_parent->dataChanged();
    QGraphicsItem::mouseReleaseEvent( event );
}

void WTransferFunction2DTriangleWidget::mouseDoubleClickEvent( QGraphicsSceneMouseEvent *event )
{
    event->accept();
    QGraphicsObject::mouseDoubleClickEvent( event );
    update();
    showColorPicker();
}

void WTransferFunction2DTriangleWidget::colorSelected( const QColor &newcolor )
{
    m_color = newcolor;
    if( m_parent )
    {
        m_parent->dataChanged();
    }
}


void WTransferFunction2DTriangleWidget::showColorPicker()
{
    // Create a color dialog to create an RGBA quadrupel
    QColorDialog *dialog = new QColorDialog();
    dialog->setCurrentColor( m_color );
    dialog->setOption( QColorDialog::NoButtons );
    dialog->setOption( QColorDialog::ShowAlphaChannel );
    dialog->setOption( QColorDialog::DontUseNativeDialog );
    connect( dialog, SIGNAL( currentColorChanged( const QColor & ) ), this, SLOT( colorSelected( const QColor & ) ) );
    dialog->open();
}

void WTransferFunction2DTriangleWidget::keyPressEvent( QKeyEvent *event )
{
    if( event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete )
    {
        //m_parent->removeTriangleWidget( this );
    }
}
