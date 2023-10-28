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

#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QPaintEngine>
#include <QMenu>

#include "core/common/WTransferFunction2D.h"
#include "qtgui/controlPanel/transferFunction2D/WTransferFunction2DBackground.h"
#include "qtgui/controlPanel/transferFunction2D/WTransferFunction2DScene.h"
#include "WTransferFunction2DShape.h"
#include "WTransferFunction2DShapeWidget.h"
#include "core/common/WHistogram2D.h"
#include "core/common/WLogger.h"
#include "W2DTFAnimator.h"
#include "WTransferFunction2DGUIWidget.h"




WTransferFunction2DGUIWidget::WTransferFunction2DGUIWidget( QWidget* qparent, WTransferFunction2DGuiNotificationClass* parent ):
        BaseClass( qparent ),
        parent( parent ),
        background( ),
        hist( nullptr ),
        initialized( false )
{
    //std::cout << "new widget" << std::endl;
    m_animator = new W2DTFAnimator();
    animating = false;
    // set up the scene and the parameters that define how we paint things
    setMinimumSize( xMax-xMin+20, yMax - yMin + 30 );
    this->setViewportUpdateMode( QGraphicsView::FullViewportUpdate );

    scene = new WTransferFunction2DScene( this );
    scene->setItemIndexMethod( QGraphicsScene::NoIndex );
    scene->setSceneRect( xMin, yMin, xMax, yMax );
    this->setScene( scene );

    this->setCacheMode( CacheNone );
    this->setRenderHint( QPainter::Antialiasing );

    this->setContextMenuPolicy( Qt::CustomContextMenu );

    connect( this, SIGNAL( customContextMenuRequested( const QPoint & ) ),
            this, SLOT( showContextMenu( const QPoint & ) ) );
    scale( 1, -1 );
    // insert background and histogram items
    scene->addItem( background = new WTransferFunction2DBackground( this ) );
    initialized = true;
    // initialize the histogram (aka. background)
    setMyBackground(); // trigger first paint of transfer function
}

WTransferFunction2DGUIWidget::~WTransferFunction2DGUIWidget()
{
}

void WTransferFunction2DGUIWidget::setMyBackground()
{
    if( background && hist != nullptr )
    {
        unsigned char * data = hist->getRawTexture();
        {
                size_t imageWidth = hist->getBucketsX();
                size_t imageHeight = hist->getBucketsY();

                QImage image( data, imageWidth, imageHeight, QImage::Format::Format_RGBA8888 );
                QPixmap pixmap;

        #if( QT_VERSION >= 0x040700 )
                pixmap.convertFromImage( image );
            #else
                // older versions have convertFromImage in Qt3Support
                // to avoid linking to that one, we use the slower version
                // here, which creates a copy, first.
                pixmap = QPixmap::fromImage( image );
            #endif
                background->setMyPixmap( pixmap );
        }
        delete( data );
    }
}


void WTransferFunction2DGUIWidget::drawBackground( QPainter *painter, const QRectF &rect )
{
    BaseClass::drawBackground( painter, rect );
}

void WTransferFunction2DGUIWidget::setHistogram( const std::shared_ptr< WHistogram2D >& newHistogram )
{
    hist = newHistogram;
    dataChanged();
}

void WTransferFunction2DGUIWidget::dataChanged()
{
    if( !initialized )
    {
        return;
    }

    this->updateTransferFunction();
    this->setMyBackground();
    forceRedraw();
}

void WTransferFunction2DGUIWidget::forceRedraw()
{
    if( !initialized )
    {
        return;
    }
    QRectF viewport( scene->sceneRect() );
    scene->invalidate( viewport );
    this->update();
}

namespace
{
    WColor toWColor( const QColor& q )
    {
        return WColor( q.redF(), q.greenF(), q.blueF(), q.alphaF() );
    }
}


void WTransferFunction2DGUIWidget::updateTransferFunction()
{
    WTransferFunction2D tf;
    int i = 0;
    {
        if( hist != nullptr )
        {
            tf.setHistogram( hist ); // get the data back because we need this for comparison
        }
        // Serialize the current TF into the 2D TF object in normalized space
        for( auto const &w : m_widgets )
        {
            double scalarPosX = w->mapToScene( w->boundingRect().topLeft() ).x() / xMax;
            double scalarPosY = w->mapToScene( w->boundingRect().topLeft() ).y() / yMax;
            double width = ( w->boundingRect().width() / xMax );
            double height = ( ( w->boundingRect().height() / yMax ) );
            double xAnchor = w->mapToScene( w->boundingRect().bottomRight() ).x() / xMax;
            double yAnchor = w->mapToScene( w->boundingRect().bottomRight() ).y() / yMax;
            double xMinAnchor = w->mapToScene( w->boundingRect().topLeft() ).x() / xMax;
            double yMinAnchor = w->mapToScene( w->boundingRect().topLeft() ).y() / yMax;
            if( !animating && !anchorPoints.empty() && !anchorPointsMin.empty() )
            {
                xAnchor = ( ( anchorPoints[i].x() / xMax ) );
                yAnchor = ( ( anchorPoints[i].y() / yMax ) );
                xMinAnchor = ( ( anchorPointsMin[i].x() / xMax ) );
                yMinAnchor = ( ( anchorPointsMin[i].y() / yMax ) );
            }
            if( animating )
            {
                xAnchor = ( ( anchorPoints[i].x() / xMax ) );
                yAnchor = ( ( anchorPoints[i].y() / yMax ) );
                xMinAnchor = ( ( anchorPointsMin[i].x() / xMax ) );
                yMinAnchor = ( ( anchorPointsMin[i].y() / yMax ) );
            }
            QColor col( w->getColor().red(), w->getColor().green(), w->getColor().blue(), w->getColor().alpha() );
            switch( w->getShape() )
            {
            case BOX:
                {
                    WTransferFunction2D::WidgetPoint boxPoints[4] =
                    {
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 0 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 0 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 1 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 1 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 2 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 2 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 3 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 3 ) ).y() ),
                        }
                    };
                    tf.addWidget( BOX, boxPoints, w->getMaps(), w->getMaps( false ), w->getMappingState(), xAnchor, yAnchor, xMinAnchor, yMinAnchor,
                                                    scalarPosX, scalarPosY, width, height, toWColor( col ) );
                    break;
                }
            case TRIANGLE:
                {
                    WTransferFunction2D::WidgetPoint triPoints[3] =
                    {
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 0 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 0 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 1 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 1 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 2 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 2 ) ).y() ),
                        },
                    };
                    tf.addWidget( TRIANGLE, triPoints, w->getMaps(), w->getMaps( false ), w->getMappingState(), xAnchor, yAnchor,
                                                    xMinAnchor, yMinAnchor, scalarPosX, scalarPosY, width, height, toWColor( col ) );
                    break;
                }
            case QUADRANGLE:
                {
                    WTransferFunction2D::WidgetPoint quadPoints[4] =
                    {
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 0 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 0 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 1 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 1 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 2 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 2 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 3 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 3 ) ).y() ),
                        }
                    };
                    tf.addWidget( QUADRANGLE, quadPoints, w->getMaps(), w->getMaps( false ), w->getMappingState(), xAnchor, yAnchor,
                                                xMinAnchor, yMinAnchor, scalarPosX, scalarPosY, width, height, toWColor( col ) );
                    break;
                }
            case ELLIPSIS:
                {
                    WTransferFunction2D::WidgetPoint ellipsPoints[4] =
                    {
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 0 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 0 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 1 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 1 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 2 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 2 ) ).y() ),
                        },
                        {
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 3 ) ).x() ),
                        static_cast<float>( w->mapToScene( w->getShapeObject().getPoint( 3 ) ).y() ),
                        }
                    };
                    tf.addWidget( ELLIPSIS, ellipsPoints, w->getMaps(), w->getMaps( false ), w->getMappingState(), xAnchor, yAnchor,
                                                    xMinAnchor, yMinAnchor, scalarPosX, scalarPosY, width, height, toWColor( col ) );
                    break;
                }
            default:
                break;
            }
            i++;
        }
    }
    if( parent )
    {
        parent->guiUpdate( tf );
    }
}


void WTransferFunction2DGUIWidget::insertWidget(  Shapes shape,
                                                          const QColor * color = new QColor( 55.0, 255.0, 0.0, 200.0 ) )
{
    std::vector<QPointF> points;
    points.push_back( QPointF( 0.0, 0.0 ) );
    points.push_back( QPointF( 50.0, 0.0 ) );
    points.push_back( QPointF( 50.0, 50.0 ) );
    points.push_back( QPointF( 0.0, 50.0 ) );

    switch( shape )
    {
    case BOX:
        color = new QColor( 255.0, 0.0, 0.0, 200.0 );
        break;
    case TRIANGLE:
        color = new QColor( 0.0, 255.0, 0.0, 200.0 );
        break;
    case QUADRANGLE:
        color = new QColor( 0.0, 255.0, 255.0, 200.0 );
        break;
    case ELLIPSIS:
        color = new QColor( 128.0, 255.0, 0.0, 200.0 );
        break;
    default:
        break;
    }

    WTransferFunction2DShapeWidget *newShapeWidget( new WTransferFunction2DShapeWidget( this, shape, *color, points ) );
    scene->addItem( newShapeWidget );
    m_widgets.push_back( newShapeWidget );
    this->update();
    dataChanged();
}

void WTransferFunction2DGUIWidget::updateWidget( Shapes shape,
                                                 std::vector<QPointF> points,
                                                 const QColor * const color,
                                                 [[maybe_unused]] const QPointF &pos )
{
    WTransferFunction2DShapeWidget *newShapeWidget( new WTransferFunction2DShapeWidget( this, shape, *color, points ) );
    scene->addItem( newShapeWidget );
    m_widgets.push_back( newShapeWidget );
    this->update();
    dataChanged();
}

bool WTransferFunction2DGUIWidget::isAnimating()
{
    return animating;
}

void WTransferFunction2DGUIWidget::addBoxWidget()
{
    insertWidget( BOX );
}

void WTransferFunction2DGUIWidget::addTriangleWidget()
{
    insertWidget( TRIANGLE );
}

void WTransferFunction2DGUIWidget::addQuadrangleWidget()
{
    insertWidget( QUADRANGLE );
}

void WTransferFunction2DGUIWidget::addEllipsisWidget()
{
    insertWidget( ELLIPSIS );
}

void WTransferFunction2DGUIWidget::cleanTransferFunction()
{
    m_animator->stopAnimations();
    for( size_t i = 0; i < m_widgets.size(); i++ )
    {
        m_animator->unsubscribeWidget( m_widgets[i] );
        scene->removeItem( m_widgets[i] );
        delete( m_widgets[i] );
    }
    m_widgets.clear();
    dataChanged();
}

void WTransferFunction2DGUIWidget::updateRateChanged( int newRate )
{
    m_animator->setUpdateRate( newRate );
}

void WTransferFunction2DGUIWidget::showContextMenu( const QPoint &pos )
{
    // Menu-Initalization
    QMenu contextMenu( tr( "Context menu" ), this );
    QMenu* widgetSubMenu = contextMenu.addMenu( "Add widget" );
    QMenu* updateRatesSubMenu = contextMenu.addMenu( "UpdateRate" );

    // Standard-Operations
    QAction action2( "Clear transfer function", this );

    // Widget-Actions
    QAction action1( "Box widget", this );
    QAction action3( "Triangle widget", this );
    QAction action4( "Quadrangle widget", this );
    QAction action5( "Ellipsis widget", this );

    // Animation-Controls
    QAction action6( "Play animations (▶️)", this );
    QAction action7( "Pause animations (⏸)", this );
    QAction action8( "Reset animations (⏹)", this );

    // UpdateRate-Actions
    QAction action9( " 0 ms " , this );
    QAction tenMS( " 10 ms " , this );
    QAction action10( " 50 ms " , this );
    QAction action11( " 100 ms " , this );
    QAction action12( " 200 ms " , this );
    QAction action13( " 500 ms " , this );
    QAction action14( " 1000 ms " , this );

    connect( &action1, SIGNAL( triggered() ), this, SLOT( addBoxWidget() ) );
    connect( &action3, SIGNAL( triggered() ), this, SLOT( addTriangleWidget() ) );
    connect( &action2, SIGNAL( triggered() ), this, SLOT( cleanTransferFunction() ) );
    connect( &action4, SIGNAL( triggered() ), this, SLOT( addQuadrangleWidget() ) );
    connect( &action5, SIGNAL( triggered() ), this, SLOT( addEllipsisWidget() ) );
    connect( &action6, SIGNAL( triggered() ), this, SLOT( playAnimations() ) );
    connect( &action7, SIGNAL( triggered() ), this, SLOT( pauseAnimations() ) );
    connect( &action8, SIGNAL( triggered() ), this, SLOT( stopAnimations() ) );

    connect( &action9, &QAction::triggered, this, [=]()
    {
        updateRateChanged( 0 );
    } );
    connect( &tenMS, &QAction::triggered, this, [=]()
    {
        updateRateChanged( 10 );
    } );
    connect( &action10, &QAction::triggered, this, [=]()
    {
        updateRateChanged( 50 );
    } );
    connect( &action11, &QAction::triggered, this, [=]()
    {
        updateRateChanged( 100 );
    } );
    connect( &action12, &QAction::triggered, this, [=]()
    {
        updateRateChanged( 200 );
    } );
    connect( &action13, &QAction::triggered, this, [=]()
    {
        updateRateChanged( 500 );
    } );
    connect( &action14, &QAction::triggered, this, [=]()
    {
        updateRateChanged( 1000 );
    } );

    // Add actions to submenu
    widgetSubMenu->addAction( &action1 );
    widgetSubMenu->addAction( &action3 );
    widgetSubMenu->addAction( &action4 );
    widgetSubMenu->addAction( &action5 );

    // Add management actions
    contextMenu.addSeparator();
    contextMenu.addAction( &action2 );
    contextMenu.addSeparator();

    // Add animation control actions
    contextMenu.addAction( &action6 );
    contextMenu.addAction( &action7 );
    contextMenu.addAction( &action8 );

    // Add updateRate-actions to submenu
    updateRatesSubMenu->addAction( &action9 );
    updateRatesSubMenu->addAction( &tenMS );
    updateRatesSubMenu->addAction( &action10 );
    updateRatesSubMenu->addAction( &action11 );
    updateRatesSubMenu->addAction( &action12 );
    updateRatesSubMenu->addAction( &action13 );
    updateRatesSubMenu->addAction( &action14 );

    contextMenu.exec( mapToGlobal( pos ) );
}

void WTransferFunction2DGUIWidget::removeWidget( WTransferFunction2DShapeWidget * widget )
{
    m_animator->stopAnimations();
    m_animator->unsubscribeWidget( widget );
    for( size_t i = 0; i < m_widgets.size(); i++ )
    {
        if( m_widgets[i] == widget )
        {
            m_widgets.erase( m_widgets.begin() + i );
            scene->removeItem( widget );
            delete( widget );
            this->dataChanged();
        }
    }
}

void WTransferFunction2DGUIWidget::playAnimations()
{
    animating = true;
    if( !m_animator->isPaused() )
    {
        for( auto const w : m_widgets )
        {
            anchorPoints.push_back( w->mapToScene( w->boundingRect().bottomRight() ) );
            anchorPointsMin.push_back( w->mapToScene( w->boundingRect().topLeft() ) );
        }
    }
    m_animator->playAnimationsParallel();
}

void WTransferFunction2DGUIWidget::stopAnimations()
{
    anchorPoints.clear();
    anchorPointsMin.clear();
    animating = false;
    m_animator->stopAnimations();
    for( auto const w: m_widgets )
    {
        w->toggleMappingState();
        w->toggleMappingState();
    }
}

void WTransferFunction2DGUIWidget::pauseAnimations()
{
    animating = false;
    m_animator->pauseAnimations();
}


W2DTFAnimator* WTransferFunction2DGUIWidget::getAnimator()
{
    return m_animator;
}
