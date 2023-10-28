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

#ifndef WTRANSFERFUNCTION2DGUIWIDGET_H
#define WTRANSFERFUNCTION2DGUIWIDGET_H

#include <vector>

#include "QGraphicsView"
#include "core/common/WHistogram2D.h"
#include "WTransferFunction2DShape.h"
#include "W2DTFAnimator.h"
#include "WTransferFunction2DShapeWidget.h"
#include "WTransferFunction2DBackground.h"


class QGraphicsScene;
class WTransferFunction2DShapeWidget;
class W2DTFAnimator;

/**
 * The class managing the widget that wants to receive updates whenever
 * a change occurs. This is only here to provide an interface and a better
 * separation between gui code and the transfer function code
 */
struct WTransferFunction2DGuiNotificationClass
{
    /**
     * default destructor
     */
    virtual ~WTransferFunction2DGuiNotificationClass()
    {
    }

    /**
     * Is called when the GUI is changed
     * \param tf the new transfer function
     */
    virtual void guiUpdate( const WTransferFunction2D& tf ) = 0;
};

/**
 * A widget that holds a scene to display and modify the 2D transfer function.
 *
 * Currently most data storage is done in this class, which is not a great
 * design. Thus, we should try to split the model and the view a bit more,
 * even though this is not intended by QGraphicsView.
 */
class WTransferFunction2DGUIWidget : public QGraphicsView
{
    Q_OBJECT

public:
    /** type of our base class for easier coding */
    typedef QGraphicsView BaseClass;

    /**
     * Constructor. Create a TF widget with a given parent.
     *
     * \param qparent parent widget
     * \param parent  a class that receives notifications
     */
    WTransferFunction2DGUIWidget( QWidget* qparent = NULL, WTransferFunction2DGuiNotificationClass* parent = NULL );

    /**
     * Destructor.
     */
    virtual ~WTransferFunction2DGUIWidget();

    /**
     * Redraw the widget
     */
    void forceRedraw();

    /**
     * Sets the histogram
     *
     * \param newHistogram is the histogram which is to be set here
     */
    void setHistogram( const std::shared_ptr< WHistogram2D >& newHistogram );

    /**
     * Removes the specified shape-widget
     *
     * \param widget widget which is to be deleted
     */
    void removeWidget( WTransferFunction2DShapeWidget *widget );

    /**
    * Updates the transfer function.
    */
    void updateTransferFunction();

    /**
     * @brief Adds a widget to the scene and list of widgets
     * 
     * @param color the color of the widget
     * @param shape
     */
    void insertWidget( Shapes shape, const QColor * const color );

    /**
     * @brief Updates a GUI-Widget based on an existing number of points
     * 
     * @param shape 
     * @param points 
     * @param color 
     * @param pos
     */
    void updateWidget( Shapes shape, std::vector<QPointF> points, const QColor * const color, [[maybe_unused]] const QPointF &pos );

    /**
     * @brief Get the pointer to the Animator connected to the 2DTF
     * 
     * @return W2DTFAnimator* 
     */
    W2DTFAnimator* getAnimator();

    /**
     * @brief Returns the state of "animating"-member
     * 
     * @return true 
     * @return false 
     */
    bool isAnimating();

public slots:
    /**
    * Removes all transfer function widgets from the scene
    */
    void cleanTransferFunction();

    /** 
     * adds a Widget with a box shape
     */
    void addBoxWidget();

    /**
     * adds a Widget with a triangle shape
     */
    void addTriangleWidget();

    /**
     * adds a Widget with a quadrangle shape
     */
    void addQuadrangleWidget();

    /**
     * adds a Widget with a ellipsis shape
     */
    void addEllipsisWidget();

    /**
     * Notification that the data changed, i.e., a control point has been moved or a color changed.
     */
    void dataChanged();

    /**
     * Plays all animation that are currently set active
     */
    void playAnimations();

    /**
     * Stops all currently playing animations 
     */
    void stopAnimations();

    /**
     * Pauses all currently playing animations
     */
    void pauseAnimations();

    /**
     * @brief get called when the updateRate has been changed in the context menu of the GUI
     * 
     * @param newRate 
     */
    void updateRateChanged( int newRate );

private slots:

    /**
    * Opens a context menu
     *
     * \param pos the position on the screen where the context menu should pop up
    */
    void showContextMenu( const QPoint &pos );

protected:
    /**
     * Draws the background.
     *
     * \param painter the painter to use
     * \param rect the QRectF to repaint
     */
    virtual void drawBackground( QPainter *painter, const QRectF &rect );

    /**
     * Internal helper function to update the QGraphicsPixmapItem that holds a representation
     * of the current histogram and displays it as a background of the widget.
     */
    void setMyBackground();
private:
    WTransferFunction2DGuiNotificationClass *parent; /*!< the class that receives our update notifications */

    std::vector<WTransferFunction2DShapeWidget* > m_widgets; /*!< List of GUI-Widgets representing the 2DTF */

    QGraphicsScene *scene; /*!< The scene that holds the GraphicItems */

    WTransferFunction2DBackground *background; /*!< background that displays the 2D histogram */

    std::shared_ptr< WHistogram2D > hist; /*!< 2D histogram which is displayed on the background */

    bool initialized; /*!< set to true after initialization */

    W2DTFAnimator* m_animator; /*!< pointer to the connected animator object */

    const int xMin = 0; /*!< Minimum x-coordinate of widget */
    const int yMin = 0; /*!< Minimum y-coordinate of widget */
    const int xMax = 300; /*!< Maximum x-coordinate of widget */
    const int yMax = 300; /*!< Maximum y-coordinate of widget */

    bool animating; /*!< set to true while animating */

    std::vector<QPointF> anchorPoints; /*!< Anchor points for the animations */

    std::vector<QPointF> anchorPointsMin; /*!< minimum Anchor points for the animations */
};

#endif  // WTRANSFERFUNCTION2DGUIWIDGET_H
