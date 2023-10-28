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

#ifndef WTRANSFERFUNCTION2DCONTROLPOINT_H
#define WTRANSFERFUNCTION2DCONTROLPOINT_H

#include "QGraphicsItem"
#include "WTransferFunction2DEnums.h"

/**
 * This class represents a control point which can be used in a 2D TF Widget
 * to control the size of e.g. the box.
 */
class WTransferFunction2DControlPoint : public QGraphicsObject
        {
    Q_OBJECT

public:
    /** type of base class */
    typedef QGraphicsObject BaseClass;

    /**
     * Constructor
     *
     * @param parent the parent object/widget
     * @param position the coordinate where the control point should be placed
     * @param handleLocation the location of the handle e.g. top left
     */
    explicit WTransferFunction2DControlPoint( BaseClass *parent, QPointF position, ResizePoints handleLocation );

    /**
     * Destructor
     */
    ~WTransferFunction2DControlPoint();

    /**
     * Defines the bounding rectangle of this item and returns it
     *
     * @return the bounding rect
     */
    QRectF boundingRect() const override;
    /**
     * Method for painting which must be overriden by this subclass
     *
     * @param painter the painting device
     * @param option style options for the painter
     * @param widget optional: a pointer to the widget where to paint on
     */
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr ) override;

    /**
     * Set position of this item
     *
     * @param position
     * */
    void setPosition( QPointF position );

public slots:
    /**
     * @brief slot that is called after a specific update time when a controlPoint was moved by an animation
     * 
     */
    void controlPointMoved();

protected:
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
     * Fires event, when mouse button is pressed
     *
     * @param event
     */
    void mousePressEvent( QGraphicsSceneMouseEvent *event ) override;

    /**
     * Fires event, when mouse enters hover area
     *
     * @param event
     */
    void hoverEnterEvent( QGraphicsSceneHoverEvent *event ) override;

    /**
     * Fires event, when mouse leaves hover area
     *
     * @param event
     */
    void hoverLeaveEvent( QGraphicsSceneHoverEvent *event ) override;
signals:
    /**
     * The signal which is emited when the user selects a different resize handle
     *
     * @param location the handler e.g. top left
     * @param position position of the handler to resize the box
     * @param onRelease state that tells that mouse was released
     * */
    void resizeHandleChanged( ResizePoints location, QPointF position, bool onRelease );

private:
    BaseClass *m_parent; /*!< parent of this graphicsobject */
    QPointF m_position; /*!< position of this graphicsobject */
    double m_radius; /*!< radius of this graphicsobject */
    ResizePoints m_handleLocation; /*!< Type of resize handler, which is currently selected */
    bool m_pressed; /*!< Flag to check if mouse button is pressed */
};


#endif  // WTRANSFERFUNCTION2DCONTROLPOINT_H
