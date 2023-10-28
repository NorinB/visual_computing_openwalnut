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

#include <vector>

#include <QMenu>
#include <QKeyEvent>
#include "QGraphicsSceneContextMenuEvent"
#include "QApplication"
#include "QBrush"
#include "QPainter"
#include "QColorDialog"
#include "QGraphicsScene"
#include "QPolygonF"
#include "QPixmap"

#include "core/common/W2DTFMapper.h"
#include "core/common/WLogger.h"
#include "WTransferFunction2DShapeWidget.h"

WTransferFunction2DShapeWidget::WTransferFunction2DShapeWidget( WTransferFunction2DGUIWidget *parent, Shapes shape, QColor color,
                                                                std::vector<QPointF> points )
{
    setFlag( ItemIsMovable );
    setFlag( ItemSendsScenePositionChanges );
    setFlag( ItemIsSelectable );
    setFlag( ItemIsFocusable );

    setZValue( 3 );

    m_shape = shape;
    m_localMapping = false;
    m_animationSpeed = 1.0;
    switch( shape )
    {
        case BOX:
            m_shapeInstance = WTransferFunction2DShape( points, BOX );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 0 ), FIRST ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 1 ), SECOND ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 2 ), THIRD ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 3 ), FOURTH ) );

            connect( m_controlPoints[0], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[1], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[2], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[3], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            break;
        case TRIANGLE:
            m_shapeInstance = WTransferFunction2DShape( points, TRIANGLE );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 0 ), FIRST ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 1 ), SECOND ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 2 ), THIRD ) );

            connect( m_controlPoints[0], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[1], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[2], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            break;
        case QUADRANGLE:
            m_shapeInstance = WTransferFunction2DShape( points, QUADRANGLE );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 0 ), FIRST ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 1 ), SECOND ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 2 ), THIRD ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 3 ), FOURTH ) );

            connect( m_controlPoints[0], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[1], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[2], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[3], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            break;
        case ELLIPSIS:
            m_shapeInstance = WTransferFunction2DShape( points, ELLIPSIS );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 0 ), FIRST ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 1 ), SECOND ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 2 ), THIRD ) );
            m_controlPoints.push_back( new WTransferFunction2DControlPoint( this, m_shapeInstance.getPoint( 3 ), FOURTH ) );

            connect( m_controlPoints[0], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[1], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[2], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            connect( m_controlPoints[3], SIGNAL( resizeHandleChanged( ResizePoints, QPointF, bool ) ),
                    this, SLOT( setResizeHandle( ResizePoints, QPointF, bool ) ) );
            break;
        default:
            break;
    }
    m_parent = parent;
    m_color = color;
    m_resizePoints = NONE;
}

WTransferFunction2DShapeWidget::~WTransferFunction2DShapeWidget()
{
}

QRectF WTransferFunction2DShapeWidget::boundingRect() const
{
    return m_shapeInstance.getPolygon().boundingRect();
}

void WTransferFunction2DShapeWidget::setControlPointsToCorner()
{
    switch( m_shape )
    {
        case BOX:
            prepareGeometryChange();
            m_controlPoints[0]->setPos( m_shapeInstance.getPoint( 0 ) );
            m_controlPoints[1]->setPos( m_shapeInstance.getPoint( 1 ) );
            m_controlPoints[2]->setPos( m_shapeInstance.getPoint( 2 ) );
            m_controlPoints[3]->setPos( m_shapeInstance.getPoint( 3 ) );
            update();
            m_parent->dataChanged();
            break;
        case TRIANGLE:
            prepareGeometryChange();
            m_controlPoints[0]->setPos( m_shapeInstance.getPoint( 0 ) );
            m_controlPoints[1]->setPos( m_shapeInstance.getPoint( 1 ) );
            m_controlPoints[2]->setPos( m_shapeInstance.getPoint( 2 ) );
            update();
            m_parent->dataChanged();
            break;
        case QUADRANGLE:
            prepareGeometryChange();
            m_controlPoints[0]->setPos( m_shapeInstance.getPoint( 0 ) );
            m_controlPoints[1]->setPos( m_shapeInstance.getPoint( 1 ) );
            m_controlPoints[2]->setPos( m_shapeInstance.getPoint( 2 ) );
            m_controlPoints[3]->setPos( m_shapeInstance.getPoint( 3 ) );
            update();
            m_parent->dataChanged();
            break;
        case ELLIPSIS:
            prepareGeometryChange();
            m_controlPoints[0]->setPos( m_shapeInstance.getPoint( 0 ) );
            m_controlPoints[1]->setPos( m_shapeInstance.getPoint( 1 ) );
            m_controlPoints[2]->setPos( m_shapeInstance.getPoint( 2 ) );
            m_controlPoints[3]->setPos( m_shapeInstance.getPoint( 3 ) );
            update();
            m_parent->dataChanged();
            break;
        default:
            break;
        }
}

QVariant WTransferFunction2DShapeWidget::itemChange( GraphicsItemChange change, const QVariant &value )
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

void WTransferFunction2DShapeWidget::setColor( QColor color )
{
    m_color = color;
    this->update();
    m_parent->dataChanged();
}

Shapes WTransferFunction2DShapeWidget::getShape()
{
    return m_shape;
}

float WTransferFunction2DShapeWidget::getAnimSpeed()
{
    return m_animationSpeed;
}

void WTransferFunction2DShapeWidget::animationSpeedChanged( float newSpeed )
{
    setAnimSpeed( newSpeed );
}

void WTransferFunction2DShapeWidget::setAnimSpeed( float newSpeed )
{
    m_animationSpeed = newSpeed;
}

WTransferFunction2DShape WTransferFunction2DShapeWidget::getShapeObject()
{
    return m_shapeInstance;
}

QColor WTransferFunction2DShapeWidget::getColor()
{
    return m_color;
}

std::vector<MapType> WTransferFunction2DShapeWidget::getMaps( bool firstDataset )
{
    if( firstDataset )
    {
        return m_selectedMapsFirstDS;
    }
    else
    {
        return m_selectedMapsSecondDS;
    }
}

bool WTransferFunction2DShapeWidget::getMappingState()
{
    return m_localMapping;
}

WTransferFunction2DControlPoint* WTransferFunction2DShapeWidget::getControlPoint( int index )
{
    return m_controlPoints[index];
}

std::vector<WTransferFunction2DControlPoint*> WTransferFunction2DShapeWidget::getControlPoints()
{
    return m_controlPoints;
}

WTransferFunction2DWidgetAnimationData WTransferFunction2DShapeWidget::getAnimationData()
{
    return m_selectedAnimation;
}

void WTransferFunction2DShapeWidget::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{
    painter->setOpacity( 1.0 );
    if( m_selectedMapsFirstDS.empty() && m_selectedMapsSecondDS.empty() )
    {
        QBrush brush( m_color );
        painter->setBrush( brush );
        if( m_shape == ELLIPSIS )
        {
            painter->drawEllipse( m_shapeInstance.getPolygon().boundingRect() );
        }
        else
        {
            painter->drawPolygon( m_shapeInstance.getPolygon(), Qt::OddEvenFill );
        }
    }
    else if( !m_selectedMapsFirstDS.empty() && m_selectedMapsSecondDS.empty() ) // Only maps for Y-axis
    {
        QBrush brush( m_colorMapX );
        painter->setBrush( brush );
        if( m_shape == ELLIPSIS )
        {
            painter->drawEllipse( m_shapeInstance.getPolygon().boundingRect() );
        }
        else
        {
            painter->drawPolygon( m_shapeInstance.getPolygon(), Qt::OddEvenFill );
        }
    }
    else if( m_selectedMapsFirstDS.empty() && !m_selectedMapsSecondDS.empty() ) // Only maps for X-Axise
    {
        QBrush brush( m_colorMapY );
        painter->setBrush( brush );
        if( m_shape == ELLIPSIS )
        {
            painter->drawEllipse( m_shapeInstance.getPolygon().boundingRect() );
        }
        else
        {
            painter->drawPolygon( m_shapeInstance.getPolygon(), Qt::OddEvenFill );
        }
    }
    else if( !m_selectedMapsFirstDS.empty() && !m_selectedMapsSecondDS.empty() ) // Maps selected for y- and x-axis
    {
        QBrush brush1( m_colorMapX );
        QBrush brush2( m_colorMapY );
        if( m_shape == ELLIPSIS )
        {
            painter->drawEllipse( m_shapeInstance.getPolygon().boundingRect() );
        }
        else
        {
            painter->setOpacity( 0.50 );
            painter->setBrush( brush1 );
            painter->drawPolygon( m_shapeInstance.getPolygon(), Qt::OddEvenFill );
            painter->setBrush( brush2 );
            painter->drawPolygon( m_shapeInstance.getPolygon(), Qt::OddEvenFill );
        }
    }
}

QLinearGradient WTransferFunction2DShapeWidget::setColorMapForWidget( bool isFirstDataSet )
{
    QLinearGradient newColorMap;
    W2DTFMapper mapper;
    std::vector<W2DTFMapper::Step> cMap;

    newColorMap.setCoordinateMode( QGradient::LogicalMode );
    if( isFirstDataSet )    // Selected map is for x-axis
    {
        if( m_localMapping )
        {
            newColorMap.setStart( QPointF( boundingRect().bottomLeft().x(), 0.5 * boundingRect().topRight().y() ) );
            newColorMap.setFinalStop( QPointF( boundingRect().bottomRight().x() , 0.5 * boundingRect().topRight().y() ) );
        }
        else
        {
            newColorMap.setStart( mapFromScene( QPointF( 0.0, 150.0 ) ) );
            newColorMap.setFinalStop( mapFromScene( QPointF( 300.0, 150.0 ) ) );
        }
        switch( m_selectedMapsFirstDS.size() )
        {
            case 1:
                // TODO(T.Neeb): Put the following lines into a function --> refactoring
                cMap = mapper.getMap( m_selectedMapsFirstDS[0] );
                for( size_t i = 0; i < cMap.size(); i++ )
                {
                    QColor col = QColor::fromRgbF( cMap[i].color[0],
                                                cMap[i].color[1],
                                                cMap[i].color[2],
                                                cMap[i].color[3] );
                    newColorMap.setColorAt( cMap[i].value, col );
                }
                return newColorMap;
                break;
            case 2:
                if( m_selectedMapsFirstDS[0] != 0 && m_selectedMapsFirstDS[0] != 10 ) // 0 and 10 are opacityMaps in enum MapType
                {
                    cMap = mapper.getMap( m_selectedMapsFirstDS[0] );
                    float index, size, alpha;
                    size = static_cast<float>( cMap.size() );
                    for( size_t i = 0; i < cMap.size(); i++ )
                    {
                        index = static_cast<float>( i );
                        if( m_selectedMapsFirstDS[1] == 0 )
                        {
                            alpha = 1.0 - index / size + 0.075;
                        }
                        else
                        {
                            alpha = index / size + 0.075;
                        }
                        if( alpha > 1.0 )
                        {
                            alpha = 1.0;
                        }
                        QColor col = QColor::fromRgbF( cMap[i].color[0],
                                                    cMap[i].color[1],
                                                    cMap[i].color[2],
                                                    alpha );
                        newColorMap.setColorAt( cMap[i].value, col );
                    }
                    return newColorMap;
                }
                if( m_selectedMapsFirstDS[1] != 0 && m_selectedMapsFirstDS[1] != 10 ) // 0 and 10 are opacityMaps in enum MapType
                {
                    cMap = mapper.getMap( m_selectedMapsFirstDS[1] );
                    float index, size, alpha;
                    size = static_cast<float>( cMap.size() );
                    for( size_t i = 0; i < cMap.size(); i++ )
                    {
                        index = static_cast<float>( i );
                        if( m_selectedMapsFirstDS[0] == 0 )
                        {
                            alpha = 1.0 - index / size + 0.075;
                        }
                        else
                        {
                            alpha = index / size + 0.075;
                        }
                        if( alpha > 1.0 )
                        {
                            alpha = 1.0;
                        }
                        QColor col = QColor::fromRgbF( cMap[i].color[0],
                                                    cMap[i].color[1],
                                                    cMap[i].color[2],
                                                    alpha );
                        newColorMap.setColorAt( cMap[i].value, col );
                    }
                    return newColorMap;
                }
                break;
            default:
                break;
        }
    }
    else    // Selected map is for y-axis
    {
        if( m_localMapping )
        {
            newColorMap.setStart( QPointF( 0.5 * boundingRect().bottomRight().x(), boundingRect().topLeft().y() ) );
            newColorMap.setFinalStop( QPointF( 0.5 * boundingRect().bottomRight().x() , boundingRect().bottomLeft().y() ) );
        }
        else
        {
            newColorMap.setStart(  mapFromScene( QPointF( 150.0, 0.0 ) ) );
            newColorMap.setFinalStop( mapFromScene( QPointF( 150.0, 300.0 ) ) );
        }
        switch( m_selectedMapsSecondDS.size() )
        {
            case 1:
                // TODO(T.Neeb): Put the following lines into a function --> refactoring
                cMap = mapper.getMap( m_selectedMapsSecondDS[0] );
                for( size_t i = 0; i < cMap.size(); i++ )
                {
                    QColor col = QColor::fromRgbF( cMap[i].color[0],
                                                cMap[i].color[1],
                                                cMap[i].color[2],
                                                cMap[i].color[3] );
                    newColorMap.setColorAt( cMap[i].value, col );
                }
                return newColorMap;
                break;
            case 2:
                if( m_selectedMapsSecondDS[0] != 0 && m_selectedMapsSecondDS[0] != 10 ) // 0 and 10 are opacityMaps in enum MapType
                {
                    cMap = mapper.getMap( m_selectedMapsSecondDS[0] );
                    float index, size, alpha;
                    size = static_cast<float>( cMap.size() );
                    for( size_t i = 0; i < cMap.size(); i++ )
                    {
                        index = static_cast<float>( i );
                        if( m_selectedMapsSecondDS[1] == 0 )
                        {
                            alpha = 1.0 - index / size + 0.075;
                        }
                        else
                        {
                            alpha = index / size + 0.075;
                        }
                        if( alpha > 1.0 )
                        {
                            alpha = 1.0;
                        }
                        QColor col = QColor::fromRgbF( cMap[i].color[0],
                                                    cMap[i].color[1],
                                                    cMap[i].color[2],
                                                    alpha );
                        newColorMap.setColorAt( cMap[i].value, col );
                    }
                    return newColorMap;
                }
                if( m_selectedMapsSecondDS[1] != 0 && m_selectedMapsSecondDS[1] != 10 ) // 0 and 10 are opacityMaps in enum MapType
                {
                    cMap = mapper.getMap( m_selectedMapsSecondDS[1] );
                    float index, size, alpha;
                    size = static_cast<float>( cMap.size() );
                    for( size_t i = 0; i < cMap.size(); i++ )
                    {
                        index = static_cast<float>( i );
                        if( m_selectedMapsSecondDS[0] == 0 )
                        {
                            alpha = 1.0 - index / size + 0.075;
                        }
                        else
                        {
                            alpha = index / size + 0.075;
                        }
                        if( alpha > 1.0 )
                        {
                            alpha = 1.0;
                        }
                        QColor col = QColor::fromRgbF( cMap[i].color[0],
                                                    cMap[i].color[1],
                                                    cMap[i].color[2],
                                                    alpha );
                        newColorMap.setColorAt( cMap[i].value, col );
                    }
                    return newColorMap;
                }
                break;
            default:
                break;
        }
    }
    return newColorMap;
}

void WTransferFunction2DShapeWidget::setResizeHandle( ResizePoints handle, QPointF position, bool onRelease )
{
    m_resizePoints = handle;
    prepareGeometryChange();
    switch( m_resizePoints )
    {
        case FIRST:
            if( m_shape == BOX || m_shape == ELLIPSIS )
            {
                m_shapeInstance.setPoint( 0, position );
                m_shapeInstance.setPoint( 1, QPointF( m_shapeInstance.getPoint( 1 ).x(), position.y() ) );
                m_shapeInstance.setPoint( 3, QPointF( position.x(), m_shapeInstance.getPoint( 3 ).y() ) );
            }
            else
            {
                m_shapeInstance.setPoint( 0, position );
            }
            setControlPointsToCorner();
            break;
        case SECOND:
            if( m_shape == BOX || m_shape == ELLIPSIS )
            {
                m_shapeInstance.setPoint( 1, position );
                m_shapeInstance.setPoint( 0, QPointF( m_shapeInstance.getPoint( 0 ).x(), position.y() ) );
                m_shapeInstance.setPoint( 2, QPointF( position.x(), m_shapeInstance.getPoint( 2 ).y() ) );
            }
            else
            {
                m_shapeInstance.setPoint( 1, position );
            }
            setControlPointsToCorner();
            break;
        case THIRD:
            if( m_shape == BOX || m_shape == ELLIPSIS )
            {
                m_shapeInstance.setPoint( 2, position );
                m_shapeInstance.setPoint( 3, QPointF( m_shapeInstance.getPoint( 3 ).x(), position.y() ) );
                m_shapeInstance.setPoint( 1, QPointF( position.x(), m_shapeInstance.getPoint( 1 ).y() ) );
            }
            else
            {
                m_shapeInstance.setPoint( 2, position );
            }
            setControlPointsToCorner();
            break;
        case FOURTH:
            if( m_shape == BOX || m_shape == ELLIPSIS )
            {
                m_shapeInstance.setPoint( 3, position );
                m_shapeInstance.setPoint( 2, QPointF( m_shapeInstance.getPoint( 2 ).x(), position.y() ) );
                m_shapeInstance.setPoint( 0, QPointF( position.x(), m_shapeInstance.getPoint( 0 ).y() ) );
            }
            else
            {
                m_shapeInstance.setPoint( 3, position );
            }
            setControlPointsToCorner();
            break;
        default:
            break;
    }
    if( onRelease )
    {
        toggleMappingState();
        toggleMappingState();
        if( m_parent->getAnimator()->isPaused() )
        {
            m_parent->stopAnimations();
        }
    }
    update();
    m_parent->dataChanged();
}

void WTransferFunction2DShapeWidget::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    QGraphicsItem::mousePressEvent( event );
    if( event->button() & Qt::RightButton )
    {
        showContextMenu( event );
    }
    update();
    m_parent->dataChanged();
}

void WTransferFunction2DShapeWidget::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
    update();
    m_parent->dataChanged();
    QGraphicsItem::mouseMoveEvent( event );
}

void WTransferFunction2DShapeWidget::mouseReleaseEvent( QGraphicsSceneMouseEvent *event )
{
    toggleMappingState();
    toggleMappingState();
    if( m_parent->getAnimator()->isPaused() )
    {
        m_parent->stopAnimations();
    }
    update();
    m_parent->dataChanged();
    QGraphicsItem::mouseReleaseEvent( event );
}

void WTransferFunction2DShapeWidget::mouseDoubleClickEvent( QGraphicsSceneMouseEvent *event )
{
    event->accept();
    QGraphicsObject::mouseDoubleClickEvent( event );
    update();
    showColorPicker();
}

void WTransferFunction2DShapeWidget::colorSelected( const QColor &newcolor )
{
    m_color = newcolor;
    if( m_parent )
    {
        m_parent->dataChanged();
    }
}

void WTransferFunction2DShapeWidget::showColorPicker()
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

void WTransferFunction2DShapeWidget::keyPressEvent( QKeyEvent *event )
{
    if( event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete )
    {
        m_parent->removeWidget( this );
    }
}

void WTransferFunction2DShapeWidget::removeWidget()
{
     m_parent->removeWidget( this );
}

void WTransferFunction2DShapeWidget::duplicateWidget()
{
    const QColor * color = new QColor( m_color.red(), m_color.green(), m_color.blue(), m_color.alpha() );
    m_parent->updateWidget( m_shape, m_shapeInstance.getPoints(), color, QPoint( 0.0, 0.0 ) );
}

void WTransferFunction2DShapeWidget::toggleMapSelection( WTransferFunction2DWidgetMapData mapData, bool firstDataSet )
{
    //First dataset
    if( firstDataSet )
    {
        if( m_selectedMapsFirstDS.size() > 0 )
        {
            for( auto i = 0; i < static_cast<int>( m_selectedMapsFirstDS.size() ); i++ )
            {
                if( m_selectedMapsFirstDS[i] == mapData.getType() )
                {
                    m_selectedMapsFirstDS.erase( m_selectedMapsFirstDS.begin() + i );
                    if( !m_selectedMapsFirstDS.empty() )
                    {
                        m_colorMapX = setColorMapForWidget( true );
                    }
                    update();
                    m_parent->dataChanged();
                    return;
                }
            }
            if( m_selectedMapsFirstDS.size() == 2 )
            {
                m_selectedMapsFirstDS.erase( m_selectedMapsFirstDS.begin() );
                update();
                m_parent->dataChanged();
            }
            m_selectedMapsFirstDS.push_back( mapData.getType() );
            m_colorMapX = setColorMapForWidget( true );
            update();
            m_parent->dataChanged();
        }
        else
        {
            m_selectedMapsFirstDS.push_back( mapData.getType() );
            m_colorMapX = setColorMapForWidget( true );
            update();
            m_parent->dataChanged();
        }
    }

    //Second dataset
    if( !firstDataSet )
    {
        if( m_selectedMapsSecondDS.size() > 0  && ( !firstDataSet ) )
        {
            for( auto i = 0; i < static_cast<int>( m_selectedMapsSecondDS.size() ); i++ )
            {
                if( m_selectedMapsSecondDS[i] == mapData.getType() )
                {
                    m_selectedMapsSecondDS.erase( m_selectedMapsSecondDS.begin() + i );
                    if( !m_selectedMapsSecondDS.empty() )
                    {
                        m_colorMapY = setColorMapForWidget( false );
                    }
                    update();
                    m_parent->dataChanged();
                    return;
                }
            }
            if( m_selectedMapsSecondDS.size() == 2 )
            {
                m_selectedMapsSecondDS.erase( m_selectedMapsSecondDS.begin() );
            }
            m_selectedMapsSecondDS.push_back( mapData.getType() );
            m_colorMapY = setColorMapForWidget( false );
            update();
            m_parent->dataChanged();
        }
        else
        {
            m_selectedMapsSecondDS.push_back( mapData.getType() );
            m_colorMapY = setColorMapForWidget( false );
            update();
            m_parent->dataChanged();
        }
    }
}

void WTransferFunction2DShapeWidget::resetMaps()
{
    m_selectedMapsFirstDS.clear();
    m_selectedMapsSecondDS.clear();
    m_parent->dataChanged();
}
void WTransferFunction2DShapeWidget::toggleAnimationSelection( WTransferFunction2DWidgetAnimationData animationData )
{
    if( m_selectedAnimation.getName() == animationData.getName() )
    {
        m_selectedAnimation = WTransferFunction2DWidgetAnimationData( "Null" );
        m_parent->getAnimator()->unsubscribeWidget( this );
    }
    else
    {
        m_selectedAnimation = animationData;
        m_parent->getAnimator()->subscribeWidget( this );
    }
}

void WTransferFunction2DShapeWidget::toggleMappingState()
{
    if( m_localMapping )
    {
        m_localMapping = false;
        if( !m_selectedMapsFirstDS.empty() )
        {
            m_colorMapX = setColorMapForWidget( true );
        }
        if( !m_selectedMapsSecondDS.empty() )
        {
            m_colorMapY = setColorMapForWidget( false );
        }
        m_parent->dataChanged();
    }
    else
    {
        m_localMapping = true;
        if( !m_selectedMapsFirstDS.empty() )
        {
            m_colorMapX = setColorMapForWidget( true );
        }
        if( !m_selectedMapsSecondDS.empty() )
        {
            m_colorMapY = setColorMapForWidget( false );
        }
        m_parent->dataChanged();
    }
}

void WTransferFunction2DShapeWidget::connectActionToMap( QAction* action, WTransferFunction2DWidgetMapData mapData, bool isFirstDataSet )
{
        connect( action, &QAction::triggered, this, [=]()
                                        {
                                            toggleMapSelection( mapData, isFirstDataSet );
                                        } );
}

void WTransferFunction2DShapeWidget::connectActionToAnimation( QAction* action, WTransferFunction2DWidgetAnimationData animData )
{
            connect( action, &QAction::triggered, this, [=]()
                                        {
                                            toggleAnimationSelection( animData );
                                        } );
}

void WTransferFunction2DShapeWidget::connectActionToSpeed( QAction* action, float speed )
{
            connect( action, &QAction::triggered, this, [=]()
                                        {
                                            animationSpeedChanged( speed );
                                        } );
}

void WTransferFunction2DShapeWidget::showContextMenu( QGraphicsSceneMouseEvent *event )
{
    //TODO(T.Neeb): ReName Actions to more meaningful values (!)
    //TODO(T.Neeb): Refactor this method into split methods and code-fragments to improve the overview

    // Color- and Opacity-Maps
    WTransferFunction2DWidgetMapData viridis = WTransferFunction2DWidgetMapData( "Viridis", C_VIRIDIS );
    WTransferFunction2DWidgetMapData GYRcont = WTransferFunction2DWidgetMapData( "Green Yellow Red", C_GYR_CONT );
    WTransferFunction2DWidgetMapData BWcont = WTransferFunction2DWidgetMapData( "Black White", C_BW_CONT );
    WTransferFunction2DWidgetMapData decreaseOpacityGrad = WTransferFunction2DWidgetMapData( "Decrease Opacity", O_DECREASE_CONT );
    WTransferFunction2DWidgetMapData constRed = WTransferFunction2DWidgetMapData( "Red", C_CONST_RED );
    WTransferFunction2DWidgetMapData constGreen = WTransferFunction2DWidgetMapData( "Green", C_CONST_GREEN );
    WTransferFunction2DWidgetMapData constBlue = WTransferFunction2DWidgetMapData( "Blue", C_CONST_BLUE );
    WTransferFunction2DWidgetMapData inferno = WTransferFunction2DWidgetMapData( "Inferno", C_INFERNO );
    WTransferFunction2DWidgetMapData redblue = WTransferFunction2DWidgetMapData( "RedBlue", C_REDBLUE );
    WTransferFunction2DWidgetMapData twilight = WTransferFunction2DWidgetMapData( "Twilight", C_TWILIGHT );

    // Inverted Maps
    WTransferFunction2DWidgetMapData increaseOpacityGrad = WTransferFunction2DWidgetMapData( "Increase Opacity", O_INCREASE_CONT );
    WTransferFunction2DWidgetMapData inv_viridis = WTransferFunction2DWidgetMapData( "Viridis (inverted)", C_INV_VIRIDIS );
    WTransferFunction2DWidgetMapData inv_GYRcont = WTransferFunction2DWidgetMapData( "Green Yellow Red (inverted)", C_INV_GYR_CONT );
    WTransferFunction2DWidgetMapData inv_BWcont = WTransferFunction2DWidgetMapData( "Black White (inverted)", C_INV_BW_CONT );
    WTransferFunction2DWidgetMapData inv_inferno = WTransferFunction2DWidgetMapData( "Inferno (inverted)", C_INV_INFERNO );
    WTransferFunction2DWidgetMapData inv_redblue = WTransferFunction2DWidgetMapData( "RedBlue (inverted)", C_INV_REDBLUE );
    WTransferFunction2DWidgetMapData inv_twilight = WTransferFunction2DWidgetMapData( "Twilight (inverted)", C_INV_TWILIGHT );

    // Animations
    WTransferFunction2DWidgetAnimationData sUpDown = WTransferFunction2DWidgetAnimationData( "Scale - TopDown", S_TOPDOWN );
    WTransferFunction2DWidgetAnimationData sDownUp = WTransferFunction2DWidgetAnimationData( "Scale - BottomUp", S_BOTTOMUP );
    WTransferFunction2DWidgetAnimationData sMaxY = WTransferFunction2DWidgetAnimationData( "Scale - To MAX Y", S_MAX_Y );
    WTransferFunction2DWidgetAnimationData sMinY = WTransferFunction2DWidgetAnimationData( "Scale - To MIN Y", S_MIN_Y );
    WTransferFunction2DWidgetAnimationData sLTR = WTransferFunction2DWidgetAnimationData( "Scale - Left to Right", S_LEFT_TO_RIGHT );
    WTransferFunction2DWidgetAnimationData sRTL = WTransferFunction2DWidgetAnimationData( "Scale - Right to Left", S_RIGHT_TO_LEFT );
    WTransferFunction2DWidgetAnimationData sMaxX = WTransferFunction2DWidgetAnimationData( "Scale - To MAX X", S_MAX_X );
    WTransferFunction2DWidgetAnimationData sMinX = WTransferFunction2DWidgetAnimationData( "Scale -To MIN X", S_MIN_X );

    // Standard widget operations
    QAction action1( "Duplicate", m_parent );
    QAction action2( "Remove", m_parent );
    QAction mappingState( "Local Mapping", m_parent );
    QAction resetMaps( "Reset Maps", m_parent );

    // First Color- and Opacity-Maps
    QAction* first_viridis = new QAction( QString::fromStdString( viridis.getName() ), m_parent );
    QAction* first_GYRcont = new QAction( QString::fromStdString( GYRcont.getName() ), m_parent );
    QAction* first_decreaseOpacityGrad = new QAction( QString::fromStdString( decreaseOpacityGrad.getName() ), m_parent );
    QAction* first_increaseOpacityGrad = new QAction( QString::fromStdString( increaseOpacityGrad.getName() ), m_parent );
    QAction* first_BWcont = new QAction( QString::fromStdString( BWcont.getName() ), m_parent );
    QAction* first_red = new QAction( QString::fromStdString( constRed.getName() ), m_parent );
    QAction* first_green = new QAction( QString::fromStdString( constGreen.getName() ), m_parent );
    QAction* first_blue = new QAction( QString::fromStdString( constBlue.getName() ), m_parent );
    QAction* first_inferno = new QAction( QString::fromStdString( inferno.getName() ), m_parent );
    QAction* first_redblue = new QAction( QString::fromStdString( redblue.getName() ), m_parent );
    QAction* first_twilight = new QAction( QString::fromStdString( twilight.getName() ), m_parent );

    QAction* first_inv_twilight = new QAction( QString::fromStdString( inv_twilight.getName() ), m_parent );
    QAction* first_inv_viridis = new QAction( QString::fromStdString( inv_viridis.getName() ), m_parent );
    QAction* first_inv_GYRcont = new QAction( QString::fromStdString( inv_GYRcont.getName() ), m_parent );
    QAction* first_inv_BWcont = new QAction( QString::fromStdString( inv_BWcont.getName() ), m_parent );
    QAction* first_inv_inferno = new QAction( QString::fromStdString( inv_inferno.getName() ), m_parent );
    QAction* first_inv_redblue = new QAction( QString::fromStdString( inv_redblue.getName() ), m_parent );

    // Second Color- and Opacity-Maps
    QAction* second_viridis = new QAction( QString::fromStdString( viridis.getName() ), m_parent );
    QAction* second_GYRcont = new QAction( QString::fromStdString( GYRcont.getName() ), m_parent );
    QAction* second_decreaseOpacityGrad = new QAction( QString::fromStdString( decreaseOpacityGrad.getName() ), m_parent );
    QAction* second_increaseOpacityGrad = new QAction( QString::fromStdString( increaseOpacityGrad.getName() ), m_parent );
    QAction* second_BWcont = new QAction( QString::fromStdString( BWcont.getName() ), m_parent );
    QAction* second_red = new QAction( QString::fromStdString( constRed.getName() ), m_parent );
    QAction* second_green = new QAction( QString::fromStdString( constGreen.getName() ), m_parent );
    QAction* second_blue = new QAction( QString::fromStdString( constBlue.getName() ), m_parent );
    QAction* second_inferno = new QAction( QString::fromStdString( inferno.getName() ), m_parent );
    QAction* second_redblue = new QAction( QString::fromStdString( redblue.getName() ), m_parent );
    QAction* second_twilight = new QAction( QString::fromStdString( twilight.getName() ), m_parent );

    QAction* second_inv_twilight = new QAction( QString::fromStdString( inv_twilight.getName() ), m_parent );
    QAction* second_inv_viridis = new QAction( QString::fromStdString( inv_viridis.getName() ), m_parent );
    QAction* second_inv_GYRcont = new QAction( QString::fromStdString( inv_GYRcont.getName() ), m_parent );
    QAction* second_inv_BWcont = new QAction( QString::fromStdString( inv_BWcont.getName() ), m_parent );
    QAction* second_inv_inferno = new QAction( QString::fromStdString( inv_inferno.getName() ), m_parent );
    QAction* second_inv_redblue = new QAction( QString::fromStdString( inv_redblue.getName() ), m_parent );

    // Animations
    QAction* action5 = new QAction( QString::fromStdString( sUpDown.getName() ), m_parent );
    QAction* action14 = new QAction( QString::fromStdString( sMaxY.getName() ), m_parent );
    QAction* action15 = new QAction( QString::fromStdString( sMinY.getName() ), m_parent );
    QAction* action16 = new QAction( QString::fromStdString( sDownUp.getName() ), m_parent );
    QAction* action17 = new QAction( QString::fromStdString( sLTR.getName() ), m_parent );
    QAction* action18 = new QAction( QString::fromStdString( sRTL.getName() ), m_parent );
    QAction* action19 = new QAction( QString::fromStdString( sMaxX.getName() ), m_parent );
    QAction* action20 = new QAction( QString::fromStdString( sMinX.getName() ), m_parent );

    // Speed
    QAction* action7 = new QAction( " 1/8 " , m_parent );
    QAction* action8 = new QAction( " 1/4 " , m_parent );
    QAction* action9 = new QAction( " 1/2 " , m_parent );
    QAction* action10 = new QAction( " 1 " , m_parent );
    QAction* action11 = new QAction( " 2 " , m_parent );
    QAction* action12 = new QAction( " 4 " , m_parent );
    QAction* action13 = new QAction( " 8 " , m_parent );


    // Setting visual selected/unselected states
    QFont font;
    font.setBold( true );
    font.setPointSize( 10 );

    if( m_localMapping )
    {
        mappingState.setFont( font );
    }
    // First Dataset Selection Feedback
    for( auto i = 0; i < static_cast<int>( m_selectedMapsFirstDS.size() ); i++ )
    {
        switch( m_selectedMapsFirstDS[i] )
        {
            case C_VIRIDIS:
                first_viridis->setFont( font );
                break;
            case C_INV_VIRIDIS:
                first_inv_viridis->setFont( font );
                break;
            case C_GYR_CONT:
                first_GYRcont->setFont( font );
                break;
            case O_DECREASE_CONT:
                first_decreaseOpacityGrad->setFont( font );
                break;
            case O_INCREASE_CONT:
                first_increaseOpacityGrad->setFont( font );
                break;
            case C_BW_CONT:
                first_BWcont->setFont( font );
                break;
            case C_CONST_RED:
                first_red->setFont( font );
                break;
            case C_CONST_GREEN:
                first_green->setFont( font );
                break;
            case C_CONST_BLUE:
                first_blue->setFont( font );
                break;
            case C_INFERNO:
                first_inferno->setFont( font );
                break;
            case C_REDBLUE:
                first_redblue->setFont( font );
                break;
            case C_TWILIGHT:
                first_twilight->setFont( font );
                break;
            case C_INV_GYR_CONT:
                first_inv_GYRcont->setFont( font );
                break;
            case C_INV_BW_CONT:
                first_inv_BWcont->setFont( font );
                break;
            case C_INV_INFERNO:
                first_inv_inferno->setFont( font );
                break;
            case C_INV_REDBLUE:
                first_inv_redblue->setFont( font );
                break;
            case C_INV_TWILIGHT:
                first_inv_twilight->setFont( font );
                break;
        }
    }

    // Second Dataset Selection Feedback
    for( auto i = 0; i < static_cast<int>( m_selectedMapsSecondDS.size() ); i++ )
    {
        switch( m_selectedMapsSecondDS[i] )
        {
            case C_VIRIDIS:
                second_viridis->setFont( font );
                break;
            case C_INV_VIRIDIS:
                second_inv_viridis->setFont( font );
                break;
            case C_GYR_CONT:
                second_GYRcont->setFont( font );
                break;
            case O_DECREASE_CONT:
                second_decreaseOpacityGrad->setFont( font );
                break;
            case O_INCREASE_CONT:
                second_increaseOpacityGrad->setFont( font );
                break;
            case C_BW_CONT:
                second_BWcont->setFont( font );
                break;
            case C_CONST_RED:
                second_red->setFont( font );
                break;
            case C_CONST_GREEN:
                second_green->setFont( font );
                break;
            case C_CONST_BLUE:
                second_blue->setFont( font );
                break;
            case C_INFERNO:
                second_inferno->setFont( font );
                break;
            case C_REDBLUE:
                second_redblue->setFont( font );
                break;
            case C_TWILIGHT:
                second_twilight->setFont( font );
                break;
            case C_INV_GYR_CONT:
                second_inv_GYRcont->setFont( font );
                break;
            case C_INV_BW_CONT:
                second_inv_BWcont->setFont( font );
                break;
            case C_INV_INFERNO:
                second_inv_inferno->setFont( font );
                break;
            case C_INV_REDBLUE:
                second_inv_redblue->setFont( font );
                break;
            case C_INV_TWILIGHT:
                second_inv_twilight->setFont( font );
                break;
        }
    }

    // Animmation-Speed selection feedback
    switch( static_cast<int>( m_animationSpeed * 1000 ) )
    {
        case 125:
            action7->setFont( font );
            break;
        case 250:
            action8->setFont( font );
            break;
        case 500:
            action9->setFont( font );
            break;
        case 1000:
            action10->setFont( font );
            break;
        case 2000:
            action11->setFont( font );
            break;
        case 4000:
            action12->setFont( font );
            break;
        case 8000:
            action13->setFont( font );
            break;
    }

    // Animation selection feedback
    if( m_selectedAnimation.getName() == sUpDown.getName() )
    {
        action5->setFont( font );
    }
    if( m_selectedAnimation.getName() == sMaxY.getName() )
    {
        action14->setFont( font );
    }
    if( m_selectedAnimation.getName() == sMinY.getName() )
    {
        action15->setFont( font );
    }
    if( m_selectedAnimation.getName() == sDownUp.getName() )
    {
        action16->setFont( font );
    }
    if( m_selectedAnimation.getName() == sLTR.getName() )
    {
        action17->setFont( font );
    }
    if( m_selectedAnimation.getName() == sRTL.getName() )
    {
        action18->setFont( font );
    }
    if( m_selectedAnimation.getName() == sMaxX.getName() )
    {
        action19->setFont( font );
    }
    if( m_selectedAnimation.getName() == sMinX.getName() )
    {
        action20->setFont( font );
    }

    // Connecting singals to slots
    connect( &action1, SIGNAL( triggered() ), this, SLOT( duplicateWidget() ) );

    connect( &action2, &QAction::triggered, m_parent, [=]()
                                        {
                                            m_parent->removeWidget( this );
                                        } );

    connect( &mappingState, SIGNAL( triggered() ), this, SLOT( toggleMappingState() ) );
    connect( &resetMaps, SIGNAL( triggered() ), this, SLOT( resetMaps() ) );
    connectActionToMap( first_viridis, viridis, true );
    connectActionToMap( first_GYRcont, GYRcont, true );
    connectActionToMap( first_decreaseOpacityGrad, decreaseOpacityGrad, true );
    connectActionToMap( first_increaseOpacityGrad, increaseOpacityGrad, true );
    connectActionToMap( first_BWcont, BWcont, true );
    connectActionToMap( first_red, constRed, true );
    connectActionToMap( first_green, constGreen, true );
    connectActionToMap( first_blue, constBlue, true );
    connectActionToMap( first_inferno, inferno, true );
    connectActionToMap( first_redblue, redblue, true );
    connectActionToMap( first_twilight, inv_twilight, true );
    connectActionToMap( first_inv_viridis, inv_viridis, true );
    connectActionToMap( first_inv_GYRcont, inv_GYRcont, true );
    connectActionToMap( first_inv_BWcont, inv_BWcont, true );
    connectActionToMap( first_inv_inferno, inv_inferno, true );
    connectActionToMap( first_inv_redblue, inv_redblue, true );
    connectActionToMap( first_inv_twilight, inv_twilight, true );
    connectActionToMap( second_viridis, viridis, false );
    connectActionToMap( second_GYRcont, GYRcont, false );
    connectActionToMap( second_decreaseOpacityGrad, decreaseOpacityGrad, false );
    connectActionToMap( second_increaseOpacityGrad, increaseOpacityGrad, false );
    connectActionToMap( second_BWcont, BWcont, false );
    connectActionToMap( second_red, constRed, false );
    connectActionToMap( second_green, constGreen, false );
    connectActionToMap( second_blue, constBlue, false );
    connectActionToMap( second_inferno, inferno, false );
    connectActionToMap( second_redblue, redblue, false );
    connectActionToMap( second_twilight, twilight, false );
    connectActionToMap( second_inv_viridis, inv_viridis, false );
    connectActionToMap( second_inv_GYRcont, inv_GYRcont, false );
    connectActionToMap( second_inv_BWcont, inv_BWcont, false );
    connectActionToMap( second_inv_inferno, inv_inferno, false );
    connectActionToMap( second_inv_redblue, inv_redblue, false );
    connectActionToMap( second_inv_twilight, inv_twilight, false );
    connectActionToAnimation( action5, sUpDown );
    connectActionToAnimation( action14, sMaxY );
    connectActionToAnimation( action15, sMinY );
    connectActionToAnimation( action16, sDownUp );
    connectActionToAnimation( action17, sLTR );
    connectActionToAnimation( action18, sRTL );
    connectActionToAnimation( action19, sMaxX );
    connectActionToAnimation( action20, sMinX );
    connectActionToSpeed( action7, 0.125 );
    connectActionToSpeed( action8, 0.25 );
    connectActionToSpeed( action9, 0.5 );
    connectActionToSpeed( action10, 1.0 );
    connectActionToSpeed( action11, 2.0 );
    connectActionToSpeed( action12, 4.0 );
    connectActionToSpeed( action13, 8.0 );

    //Menu-Initalization
    QMenu menu( m_parent );
    QMenu* editSubMenu = menu.addMenu( "Edit" );
    QMenu* animationsSubMenu = menu.addMenu( "Animations" );
    QMenu* mapsFirstDataset = menu.addMenu( "Maps (x)" );
    QMenu* mapsSecondDataset = menu.addMenu( "Maps (y)" );
    QMenu* speedSubMenu = menu.addMenu( "Speed" );
    QMenu* constantFirst = mapsFirstDataset->addMenu( "Constant" );
    QMenu* constantSecond = mapsSecondDataset->addMenu( "Constant" );
    QMenu* opacityFirst = mapsFirstDataset->addMenu( "Opacity" );
    QMenu* opacitySecond = mapsSecondDataset->addMenu( "Opacity" );

    // Add actions to Edit
    editSubMenu->addAction( &action1 );
    editSubMenu->addAction( &action2 );

    //Add actions to Map-Submenus

    constantFirst->addAction( first_red );
    constantFirst->addAction( first_blue );
    constantFirst->addAction( first_green );
    opacityFirst->addAction( first_decreaseOpacityGrad );
    opacityFirst->addAction( first_increaseOpacityGrad );
    mapsFirstDataset->addAction( first_viridis );
    mapsFirstDataset->addAction( first_inferno );
    mapsFirstDataset->addAction( first_BWcont );
    mapsFirstDataset->addAction( first_GYRcont );
    mapsFirstDataset->addAction( first_redblue );
    mapsFirstDataset->addAction( first_twilight );
    mapsFirstDataset->addSeparator();
    mapsFirstDataset->addAction( first_inv_viridis );
    mapsFirstDataset->addAction( first_inv_inferno );
    mapsFirstDataset->addAction( first_inv_BWcont );
    mapsFirstDataset->addAction( first_inv_GYRcont );
    mapsFirstDataset->addAction( first_inv_redblue );
    mapsFirstDataset->addAction( first_inv_twilight );



    constantSecond->addAction( second_red );
    constantSecond->addAction( second_blue );
    constantSecond->addAction( second_green );
    opacitySecond->addAction( second_decreaseOpacityGrad );
    opacitySecond->addAction( second_increaseOpacityGrad );
    mapsSecondDataset->addSeparator();
    mapsSecondDataset->addAction( second_viridis );
    mapsSecondDataset->addAction( second_inferno );
    mapsSecondDataset->addAction( second_BWcont );
    mapsSecondDataset->addAction( second_GYRcont );
    mapsSecondDataset->addAction( second_redblue );
    mapsSecondDataset->addAction( second_twilight );
    mapsSecondDataset->addSeparator();
    mapsSecondDataset->addAction( second_inv_viridis );
    mapsSecondDataset->addAction( second_inv_inferno );
    mapsSecondDataset->addAction( second_inv_BWcont );
    mapsSecondDataset->addAction( second_inv_GYRcont );
    mapsSecondDataset->addAction( second_inv_redblue );
    mapsSecondDataset->addAction( second_inv_twilight );

    //Add actions to Speed
    speedSubMenu->addAction( action7 );
    speedSubMenu->addAction( action8 );
    speedSubMenu->addAction( action9 );
    speedSubMenu->addAction( action10 );
    speedSubMenu->addAction( action11 );
    speedSubMenu->addAction( action12 );
    speedSubMenu->addAction( action13 );

    //Add actions to Animations
    animationsSubMenu->addAction( action5 );
    animationsSubMenu->addAction( action16 );
    animationsSubMenu->addAction( action14 );
    animationsSubMenu->addAction( action15 );
    animationsSubMenu->addSeparator();
    animationsSubMenu->addAction( action17 );
    animationsSubMenu->addAction( action18 );
    animationsSubMenu->addAction( action19 );
    animationsSubMenu->addAction( action20 );

    menu.addAction( &mappingState );
    menu.addAction( &resetMaps );

    menu.exec( event->screenPos() );
}
