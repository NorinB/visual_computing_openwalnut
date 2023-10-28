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


#ifndef WTRANSFERFUNCTION2DSHAPEWIDGET_H
#define WTRANSFERFUNCTION2DSHAPEWIDGET_H

#include <vector>
#include <list>

#include "QGraphicsItem"

#include "WTransferFunction2DGUIWidget.h"
#include "W2DTFAnimator.h"
#include "WTransferFunction2DShape.h"
#include "WTransferFunction2DControlPoint.h"
#include "WTransferFunction2DEnums.h"
#include "WTransferFunction2DWidgetMapData.h"
#include "WTransferFunction2DWidgetAnimationData.h"

class W2DTFAnimator;
class WTransferFunction2DGUIWidget;
/**
 * This class defines a resizable triangle and is used as a
 * manipulation widget for the 2D Transfer Function.
 * With this widget you select how the data is depicted
 * later, through setting a color and opacity.
 *
 */
class WTransferFunction2DShapeWidget : public QGraphicsObject
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new WTransferFunction2DShapeWidget object
     * 
     * @param parent 
     * @param shape 
     * @param color 
     * @param points 
     */
    explicit WTransferFunction2DShapeWidget( WTransferFunction2DGUIWidget *parent, Shapes shape, QColor color, std::vector<QPointF> points );


    /**
     * @brief Destroy the WTransferFunction2DShapeWidget object
     * 
     */
    ~WTransferFunction2DShapeWidget();

    /**
     * @brief return the bounding rect of the widget
     * 
     * @return QRectF 
     */
    QRectF boundingRect() const override;

    /**
     * @brief paints the shape
     * 
     * @param painter 
     * @param option 
     * @param widget 
     */
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr ) override;

    /**
     * @brief Get the Color object
     * 
     * @return QColor 
     */
    QColor getColor();

    /**
     * @brief Get the maps for the first or second dataset based on the bool parameter ( true = firstDataset )
     * 
     * @param firstDataset 
     * @return std::vector<MapType> 
     */
    std::vector<MapType> getMaps( bool firstDataset = true );

    /**
     * @brief Get the Shape Object object
     * 
     * @return WTransferFunction2DShape 
     */
    WTransferFunction2DShape getShapeObject();

    /**
     * @brief Set the Color object
     * 
     * @param newColor 
     */
    void setColor( QColor newColor );

    /**
     * @brief Get the Shape of the widget
     * 
     * @return Shapes 
     */
    Shapes getShape();

    /** Sets all control points in their desired corner of the rect */
    void setControlPointsToCorner();

    /**
     * @brief Get the Control Point object at index
     * 
     * @param index 
     * @return WTransferFunction2DControlPoint* 
     */
    WTransferFunction2DControlPoint* getControlPoint( int index );

    /**
     * @brief Get the Control Points connected to this widget
     * 
     * @return std::vector<WTransferFunction2DControlPoint*> 
     */
    std::vector<WTransferFunction2DControlPoint*> getControlPoints();

    /**
     * @brief Get the speed of the animation as float
     * 
     * @return float 
     */
    float getAnimSpeed();

    /**
     * @brief Get the Mapping State object
     * 
     * @return true = localMapping
     * @return false = globalMapping
     */
    bool getMappingState();

    /**
     * @brief Set the speed of the animation
     * 
     * @param newSpeed 
     */
    void setAnimSpeed( float newSpeed );

    /**
     * @brief Get the Animation Data object
     * 
     * @return WTransferFunction2DWidgetAnimationData 
     */
    WTransferFunction2DWidgetAnimationData getAnimationData();

public slots:
    /**
     * Called by the color dialog every time the user changes the color.
     *
     * \param color the new color
     */
    void colorSelected( const QColor &color );

    /**
     * Sets the resize handle to a new position
     *
     * \param handle handle location e.g. TOPLEFT
     * \param position position where it was moved to
     * \param onRelease state of the mouse button while moving a control point
     */
    void setResizeHandle( ResizePoints handle, QPointF position, bool onRelease );

    /**
     * Removes the widget
     */
    void removeWidget();

    /**
     * Duplicates the widget
     * 
     */
    void duplicateWidget();

    /**
     * @brief selects/deselects the widgetMapData specified by the paramter
     * @param firstDataset
     * @param mapData 
     */
    void toggleMapSelection( WTransferFunction2DWidgetMapData mapData, bool firstDataset );
    /**
     * @brief selects/deselects the widgetAnimationData specified by the parameter
     * 
     * @param animationData 
     */
    void toggleAnimationSelection( WTransferFunction2DWidgetAnimationData animationData );

    /**
     * @brief Changes the Mapping State to the opposite
     */
    void toggleMappingState();

    /**
     * @brief get triggered when the animation speed is changed in the contextMenu
     * 
     * @param newSpeed 
     */
    void animationSpeedChanged( float newSpeed );

    /**
     * @brief Connects the action to the specified map-slot
     * 
     * @param action 
     * @param mapData 
     * @param isFirstDataSet
     */
    void connectActionToMap( QAction* action, WTransferFunction2DWidgetMapData mapData, bool isFirstDataSet );

    /**
     * @brief Conntects the action to the specified lambda function slot for toggling animations
     * 
     * @param action 
     * @param animData 
     */
    void connectActionToAnimation( QAction* action, WTransferFunction2DWidgetAnimationData animData );

    /**
     * @brief Conntects the action to the specified lambda function slot for toggling the speed-selection
     * 
     * @param action 
     * @param speed 
     */
    void connectActionToSpeed( QAction* action, float speed );

    /**
     * @brief Resets the maps and starts redraw
     */
    void resetMaps();
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
    /** Show the color picker dialog. */
    void showColorPicker();

    /**
     * @brief Sets the ColorMap For the Widget
     * 
     * @param isFirstDataSet 
     * @return QLinearGradient 
     */
    QLinearGradient setColorMapForWidget( bool isFirstDataSet );
    /**
     * @brief creates and shows the context menu of the widget
     * 
     * @param event 
     */
    void showContextMenu( QGraphicsSceneMouseEvent *event );

    /** Flag of current selected resize point */
    ResizePoints m_resizePoints;

    /** The parent object */
    WTransferFunction2DGUIWidget *m_parent;

    /** The color of the box */
    QColor m_color;

    /** The different control handles in the corners */
    std::vector<WTransferFunction2DControlPoint *> m_controlPoints;

    /** The shapeInstance connected to the widget */
    WTransferFunction2DShape m_shapeInstance;

    /** The name of the shape represented by this widget */
    Shapes m_shape;

    /** list of maps that have been selected for the first dataset **/
    std::vector<MapType> m_selectedMapsFirstDS;

    /** list of maps that have been selected for the second dataset **/
    std::vector<MapType> m_selectedMapsSecondDS;

    /** the currently selected animation of this widget**/
    WTransferFunction2DWidgetAnimationData m_selectedAnimation;

    /** speed of the animation for this widget **/
    float m_animationSpeed;

    /** Defines whether the mapping should be local or global**/
    bool m_localMapping;

    /** The gradient applied to the brush in the paint-method when a map for the x-axis has been selected */
    QLinearGradient m_colorMapX;

    /** The gradient applied to the brush in the paint-method when a map for the y-axis has been selected */
    QLinearGradient m_colorMapY;
};

#endif  // WTRANSFERFUNCTION2DSHAPEWIDGET_H
