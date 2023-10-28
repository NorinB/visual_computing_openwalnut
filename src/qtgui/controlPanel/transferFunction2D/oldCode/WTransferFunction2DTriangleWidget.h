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

#ifndef WTRANSFERFUNCTION2DTRIANGLEWIDGET_H
#define WTRANSFERFUNCTION2DTRIANGLEWIDGET_H

#include <vector>

#include "QGraphicsItem"

#include "../WTransferFunction2DGUIWidget.h"
#include "../WTransferFunction2DControlPoint.h"
#include "../WTransferFunction2DEnums.h"
#include "WTransferFunction2DTriangle.h"
class WTransferFunction2DGUIWidget;
/**
 * This class defines a resizable triangle and is used as a
 * manipulation widget for the 2D Transfer Function.
 * With this widget you select how the data is depicted
 * later, through setting a color and opacity.
 *
 */
class WTransferFunction2DTriangleWidget : public QGraphicsObject
{
    Q_OBJECT
public:
    /**
     * Constructor
     *
     * \param parent of the triangle
     * \param triangle of the widget
     * \param color of the triangle
     */
    explicit WTransferFunction2DTriangleWidget( WTransferFunction2DGUIWidget *parent, WTransferFunction2DTriangle triangle, QColor color );

    /**
     * Destructor
     */
    ~WTransferFunction2DTriangleWidget();

    /**
     * Defines the bounding rectangle of this item and returns it
     *
     * @return
     */
    QRectF boundingRect() const override;

    /**
     * Method for painting which must be overriden by this subclass
     *
     * \param painter
     * \param option
     * \param widget
     */
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr ) override;

    /**
     * Get the color of the triangle.
     *
     * \return  the color of the triangle
     */
    QColor getColor()
    {
        return m_color;
    }
    /**
     * Get the Triangle object
     * 
     * @return WTransferFunction2DTriangle 
     */
    WTransferFunction2DTriangle getTriangle()
    {
        return m_triangle;
    }

    /**
     * Set the color of the box.
     *
     * \param color the new color
     */
    void setColor( QColor color );

public slots:
    /**
     * Called by the color dialog every time the user changes the color.
     *
     * \param color the new color
     */
    void colorSelected( const QColor& color );

    /**
     * Sets the resize handle to a new position
     *
     * \param handle handle location e.g. TOPLEFT
     * \param position position where it was moved to
     */
    void setResizeHandle( ResizePoints handle, QPointF position );

protected:
    /**
     * Fires event, when mouse button is pressed
     *
     * @param event
     */
    void mousePressEvent( QGraphicsSceneMouseEvent *event ) override;

    /**
     * Fires event, when mouse button is moved
     *
     * @param event
     */
    void mouseMoveEvent( QGraphicsSceneMouseEvent *event ) override;

    /**
     * Fires event, when mouse button is released
     *
     * @param event
     */
    void mouseReleaseEvent( QGraphicsSceneMouseEvent *event ) override;

    /**
      * Fires event, when mouse button is double clicked
      *
      * @param event
      */
    void mouseDoubleClickEvent( QGraphicsSceneMouseEvent *event ) override;

    /**
      * Fires event, when a key is pressed
      *
      * @param event
      */
    void keyPressEvent( QKeyEvent *event ) override;

    /**
     *  Handles events, when state of this item changes
     *
     *  from QtDocs:
     *  @param change is the parameter of the item that is changing
     *  @param value is the new value
     *
     *  @return a Qt datatype
     */
    QVariant itemChange( GraphicsItemChange change, const QVariant &value ) override;

private:
    /**
     * @brief updates the triangle data
     * 
     * @param newPos 
     * @param startPos 
     */
    void updateTriangleData( QPointF newPos, QPointF startPos );

    /**
     * Show the color picker dialog.
     **/
    void showColorPicker();

    /**
     * Sets all control points in their desired corner of the rect
     * */
    void setControlPointsToCorner();

    ResizePoints m_resizePoints; /*!< Flag of current selected resize point */
    WTransferFunction2DGUIWidget* m_parent;  /*!< The parent object */
    QColor m_color;  /*!< The color of the box */
    std::vector< WTransferFunction2DControlPoint* > m_controlPoints; /*!< The different control handles in the corners */
    WTransferFunction2DTriangle m_triangle; /*!< The triangle which is painted */
};

#endif  // WTRANSFERFUNCTION2DTRIANGLEWIDGET_H

