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
#include <memory>
#include <string>

#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QKeyEvent>
#include <QPixmap>

#include "WMainWindow.h"
#include "WQtGLScreenCapture.h"
#include "WQtGLWidget.h"
#include "WQtGui.h"
#include "WSettingAction.h"
#include "core/common/WColor.h"
#include "core/common/WConditionOneShot.h"
#include "core/common/WFlag.h"
#include "core/common/WLogger.h"
#include "core/graphicsEngine/WGE2DManipulator.h"
#include "core/graphicsEngine/WGEAdvancedManipulator.h"
#include "core/graphicsEngine/WGENoOpManipulator.h"
#include "core/graphicsEngine/WGEViewer.h"
#include "core/graphicsEngine/WGEZoomTrackballManipulator.h"
#include "core/graphicsEngine/WGraphicsEngine.h"
#include "core/kernel/WKernel.h"
#include "events/WEventTypes.h"
#include "events/WRenderedFrameEvent.h"

#ifdef OW_QT_GLWIDGET
WQtGLWidget::WQtGLWidget( std::string nameOfViewer, QWidget* parent, WGECamera::ProjectionMode projectionMode, const QWidget* /* shareWidget */ ):
    QOpenGLWidget( parent ),
#else
WQtGLWidget::WQtGLWidget( std::string nameOfViewer, QWidget* parent, WGECamera::ProjectionMode projectionMode, const QWidget* shareWidget ):
    QGLWidget( getDefaultFormat(), parent, dynamic_cast< const QGLWidget* >( shareWidget ) ),
#endif
    m_nameOfViewer( nameOfViewer ),
    m_firstPaint( true ),
    m_firstFrame( true )
{
#ifdef OW_QT_GLWIDGET
    setFormat( getDefaultFormat() );
#endif
    m_initialProjectionMode = projectionMode;

    setSizePolicy( QSizePolicy( QSizePolicy::QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding ) );

    // This causes QOpenGLWidget to freeze so only use with qt5 and below
#ifndef OW_QT_GLWIDGET
    setAttribute( Qt::WA_PaintOnScreen );
    setAttribute( Qt::WA_NoSystemBackground );
#endif

    setFocusPolicy( Qt::ClickFocus );
    setMouseTracking( true );

    // initialize OpenGL context and OpenSceneGraph
    osg::ref_ptr<osg::Referenced> wdata; // NULL pointer since not used on Mac

    // create viewer
    m_Viewer = WKernel::getRunningKernel()->getGraphicsEngine()->createViewer(
        m_nameOfViewer, wdata, x(), y(), width(), height(), m_initialProjectionMode );

#ifdef OW_QT_GLWIDGET
    connect( &m_Timer, SIGNAL( timeout() ), this, SLOT( update() ) );
#else
    connect( &m_Timer, SIGNAL( timeout() ), this, SLOT( updateGL() ) );
#endif
    m_Timer.start( 0 );

    m_Viewer->isFrameRendered()->getCondition()->subscribeSignal( boost::bind( &WQtGLWidget::notifyFirstRenderedFrame, this ) );

    m_cameraResetAction = new QAction( WQtGui::getIconManager()->getIcon( "view" ), "Reset", this );
    connect( m_cameraResetAction, SIGNAL(  triggered( bool ) ), this, SLOT( reset() ) );
    m_cameraResetAction->setToolTip( "Reset view" );

    // a separate menu for some presets
    m_cameraPresetMenu = new QMenu( "Camera Presets" );
    m_cameraPresetResetMenu = new QMenu( "Camera Presets" );
    m_cameraPresetResetMenu->addAction( m_cameraResetAction );

    // NOTE: the shortcuts for these view presets should be chosen carefully. Most keysequences have another meaning in the most applications
    // so the user may get confused. It is also not a good idea to take letters as they might be used by OpenSceneGraph widget ( like "S" for
    // statistics ).
    // By additionally adding the action to the main window, we ensure the action can be triggered even if the menu bar is hidden.
#ifdef OW_QT6_MODIFIER_ADD
    QAction* tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "sagittal icon" ), "Left", this,
                                                        SLOT( setPresetViewLeft() ),
                                                        QKeySequence( Qt::CTRL | Qt::SHIFT | Qt::Key_L ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "sagittal icon" ), "Right", this,
                                               SLOT( setPresetViewRight() ),
                                               QKeySequence( Qt::CTRL | Qt::SHIFT | Qt::Key_R ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "axial icon" ), "Superior", this,
                                               SLOT( setPresetViewSuperior() ),
                                               QKeySequence( Qt::CTRL | Qt::SHIFT | Qt::Key_S ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "axial icon" ), "Inferior", this,
                                               SLOT( setPresetViewInferior() ),
                                               QKeySequence( Qt::CTRL | Qt::SHIFT | Qt::Key_I ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "coronal icon" ), "Anterior", this,
                                               SLOT( setPresetViewAnterior() ),
                                               QKeySequence( Qt::CTRL | Qt::SHIFT | Qt::Key_A ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "coronal icon" ), "Posterior", this,
                                               SLOT( setPresetViewPosterior() ),
                                               QKeySequence( Qt::CTRL | Qt::SHIFT | Qt::Key_P ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );

    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "center icon" ), "Fit screen", this,
                                               SLOT( setFitScreenPosition() ),
                                               QKeySequence( Qt::CTRL | Qt::SHIFT | Qt::Key_F ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
#else
    QAction* tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "sagittal icon" ), "Left", this,
                                                        SLOT( setPresetViewLeft() ),
                                                        QKeySequence( Qt::CTRL + Qt::SHIFT + Qt::Key_L ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "sagittal icon" ), "Right", this,
                                               SLOT( setPresetViewRight() ),
                                               QKeySequence( Qt::CTRL + Qt::SHIFT + Qt::Key_R ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "axial icon" ), "Superior", this,
                                               SLOT( setPresetViewSuperior() ),
                                               QKeySequence( Qt::CTRL + Qt::SHIFT + Qt::Key_S ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "axial icon" ), "Inferior", this,
                                               SLOT( setPresetViewInferior() ),
                                               QKeySequence( Qt::CTRL + Qt::SHIFT + Qt::Key_I ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "coronal icon" ), "Anterior", this,
                                               SLOT( setPresetViewAnterior() ),
                                               QKeySequence( Qt::CTRL + Qt::SHIFT + Qt::Key_A ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "coronal icon" ), "Posterior", this,
                                               SLOT( setPresetViewPosterior() ),
                                               QKeySequence( Qt::CTRL + Qt::SHIFT + Qt::Key_P ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );

    tmpAction = m_cameraPresetMenu->addAction( WQtGui::getIconManager()->getIcon( "center icon" ), "Fit screen", this,
                                               SLOT( setFitScreenPosition() ),
                                               QKeySequence( Qt::CTRL + Qt::SHIFT + Qt::Key_F ) );
    tmpAction->setIconVisibleInMenu( true );
    m_cameraPresetResetMenu->addAction( tmpAction );
#endif
}

WQtGLWidget::~WQtGLWidget()
{
    wlog::debug( "WQtGLWidget" ) << "OpenGL widget for viewer \"" << m_nameOfViewer << "\" removed.";
    // nothing
    cleanUp();
}

void WQtGLWidget::cleanUp()
{
    if( m_Viewer )
    {
        m_Viewer->setClosed( true );
        WKernel::getRunningKernel()->getGraphicsEngine()->closeViewer( m_Viewer );
        m_Viewer = std::shared_ptr<WGEViewer>();
    }
}

void WQtGLWidget::closeEvent( QCloseEvent* event )
{
    event->accept();
    WQtGLWidgetParent::closeEvent( event );
}

void WQtGLWidget::setCameraManipulator( WQtGLWidget::CameraManipulators manipulator )
{
    if( !m_Viewer )
    {
        return;
    }

    m_CurrentManipulator = manipulator;
    switch( manipulator )
    {
        case TWO_D:
            WLogger::getLogger()->addLogMessage( "Switched to camera manipulator \"WGE2D\".",
                                                 "WQtGLWidget(" + m_Viewer->getName() + ")",
                                                 LL_DEBUG );

            m_Viewer->setCameraManipulator( new( WGE2DManipulator ) );
            break;
        case NO_OP:
            WLogger::getLogger()->addLogMessage( "Switched to camera manipulator \"WGENoOp\".",
                                                 "WQtGLWidget(" + m_Viewer->getName() + ")",
                                                 LL_DEBUG );

            m_Viewer->setCameraManipulator( new( WGENoOpManipulator ) );
            break;
        case ADVANCED:
            WLogger::getLogger()->addLogMessage( "Switched to camera manipulator \"ADVANCED\".",
                                                 "WQtGLWidget(" + m_Viewer->getName() + ")",
                                                 LL_DEBUG );

            m_Viewer->setCameraManipulator( new( WGEAdvancedManipulator ) );
            break;
        case TRACKBALL:
        default:
            WLogger::getLogger()->addLogMessage( "Switched to OSG manipulator \"WGEZoomTrackball\".",
                                                 "WQtGLWidget(" + m_Viewer->getName() + ")",
                                                 LL_DEBUG );

            m_Viewer->setCameraManipulator( new( WGEZoomTrackballManipulator ) );
            break;
    }
}

WQtGLWidget::CameraManipulators WQtGLWidget::getCameraManipulators()
{
    return m_CurrentManipulator;
}

std::shared_ptr< WGEViewer > WQtGLWidget::getViewer() const
{
    return m_Viewer;
}

void WQtGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
}

void WQtGLWidget::paintEvent( QPaintEvent* event )
{
    if( m_firstPaint )
    {
        // it is important to let the GE know that there now is an completely initialized widget -> allowing GE startup to complete
        // This is needed as on some machines, the OSG crashes if the GL widget is not fully initialized.
        m_firstPaint = false;
        WKernel::getRunningKernel()->getGraphicsEngine()->finalizeStartup();
    }
    WQtGLWidgetParent::paintEvent( event );
}

void WQtGLWidget::paintGL()
{
    if( m_Viewer )
    {
        if( m_firstFrame )
        {
            #ifdef OW_QT_GLWIDGET
                m_Viewer->getView()->getCamera()->getGraphicsContext()->setDefaultFboId( defaultFramebufferObject() );
            #endif
            m_firstFrame = false;
        }

        if( !m_Viewer->getPaused() )
        {
            m_Viewer->paint();
        }
    }
}

void WQtGLWidget::resizeGL( int width, int height )
{
    if( m_Viewer )
    {
        m_Viewer->resize( width, height );
    }
    WQtGLWidgetParent::resizeGL( width, height );
}

int WQtGLWidget::translateButton( QMouseEvent* event )
{
    switch( event->button() )
    {
        case( Qt::LeftButton ):
            return 1;
        case( Qt::MiddleButton ):
            return 2;
        case( Qt::RightButton ):
            return 3;
        default:
            return 0;
    }
}

void WQtGLWidget::keyPressEvent( QKeyEvent* event )
{
    if( !m_Viewer )
    {
        return;
    }

    // we ignore auto-repeated keys independent of the window manager settings
    if( event->isAutoRepeat() )
    {
        return;
    }
    if( event->text() != "" )
    {
        m_Viewer->keyEvent( WGEViewer::KEYPRESS, event->key() );
    }
    else
    {
        switch( event->modifiers() )
        {
            case Qt::ShiftModifier :
                m_Viewer->keyEvent( WGEViewer::KEYPRESS, osgGA::GUIEventAdapter::KEY_Shift_L );
                break;
            case Qt::ControlModifier :
                m_Viewer->keyEvent( WGEViewer::KEYPRESS, osgGA::GUIEventAdapter::KEY_Control_L );
                break;
            default :
                break;
        }
    }
}

void WQtGLWidget::keyReleaseEvent( QKeyEvent* event )
{
    if( !m_Viewer )
    {
        return;
    }

    // we ignore auto-repeated keys independent of the window manager settings
    if( event->isAutoRepeat() )
    {
        return;
    }
    switch( event->key() )
    {
        case Qt::Key_Period:
            WGraphicsEngine::getGraphicsEngine()->requestShaderReload();
            break;
        case Qt::Key_1:
            setCameraManipulator( TRACKBALL );
            break;
        case Qt::Key_2:
            setCameraManipulator( TWO_D );
            break;
        case Qt::Key_3:
            setCameraManipulator( ADVANCED );
            break;
    }

    switch( event->modifiers() )
    {
        case Qt::ShiftModifier :
            m_Viewer->keyEvent( WGEViewer::KEYRELEASE, osgGA::GUIEventAdapter::KEY_Shift_L );
            break;
        case Qt::ControlModifier :
            m_Viewer->keyEvent( WGEViewer::KEYRELEASE, osgGA::GUIEventAdapter::KEY_Control_L );
            break;
    }

    m_Viewer->keyEvent( WGEViewer::KEYRELEASE, event->key() );
}


void WQtGLWidget::mousePressEvent( QMouseEvent* event )
{
    if( m_Viewer )
    {
        m_Viewer->mouseEvent( WGEViewer::MOUSEPRESS, event->x(), event->y(), translateButton( event ) );
    }
}

void WQtGLWidget::mouseDoubleClickEvent( QMouseEvent* event )
{
    if( m_Viewer )
    {
        m_Viewer->mouseEvent( WGEViewer::MOUSEDOUBLECLICK, event->x(), event->y(), translateButton( event ) );
    }
}

void WQtGLWidget::mouseReleaseEvent( QMouseEvent* event )
{
    if( m_Viewer )
    {
        m_Viewer->mouseEvent( WGEViewer::MOUSERELEASE, event->x(), event->y(), translateButton( event ) );
    }
}

void WQtGLWidget::mouseMoveEvent( QMouseEvent* event )
{
    if( m_Viewer )
    {
        m_Viewer->mouseEvent( WGEViewer::MOUSEMOVE, event->x(), event->y(), 0 );
    }
}

void WQtGLWidget::wheelEvent( QWheelEvent* event )
{
    if( m_Viewer )
    {
        int x, y;
        x = event->angleDelta().x();
        y = event->angleDelta().y();

        m_Viewer->mouseEvent( WGEViewer::MOUSESCROLL, x, y, 0 );
    }
}

bool WQtGLWidget::event( QEvent* event )
{
    if( event->type() == WQT_RENDERED_FRAME_EVENT )
    {
        emit renderedFirstFrame();
        return true;
    }

    return WQtGLWidgetParent::event( event );
}

void WQtGLWidget::reset()
{
    if( m_Viewer )
    {
        m_Viewer->reset();
    }
}

const QGLFormat WQtGLWidget::getDefaultFormat()
{
    QGLFormat format;
    format.setSwapInterval( 0 );    // according to Qt Doc, this should enable VSync. But it doesn't.
    return format;
}

void WQtGLWidget::notifyFirstRenderedFrame()
{
    QCoreApplication::postEvent( this, new WRenderedFrameEvent() );
}

void WQtGLWidget::setPresetViewLeft()
{
    if( m_Viewer )
    {
        osg::ref_ptr<osgGA::TrackballManipulator>  cm = osg::dynamic_pointer_cast<osgGA::TrackballManipulator>( m_Viewer->getCameraManipulator() );
        osg::Quat q( 0.5, -0.5, -0.5, 0.5 );
        // is it a trackball manipulator?
        if( cm )
        {
            cm->setRotation( q );
        }
        else
        {
            wlog::warn( "WQtGLWidget(" + m_Viewer->getName() + ")" ) << "GL Widget does not use a TrackballManipulator. Preset cannot be used.";
        }
    }
}

void WQtGLWidget::setPresetViewRight()
{
    if( m_Viewer )
    {
        osg::ref_ptr<osgGA::TrackballManipulator>  cm = osg::dynamic_pointer_cast<osgGA::TrackballManipulator>( m_Viewer->getCameraManipulator() );
        osg::Quat q( -0.5, -0.5, -0.5, -0.5 );
        // is it a trackball manipulator?
        if( cm )
        {
            cm->setRotation( q );
        }
        else
        {
            wlog::warn( "WQtGLWidget(" + m_Viewer->getName() + ")" ) << "GL Widget does not use a TrackballManipulator. Preset cannot be used.";
        }
    }
}

void WQtGLWidget::setPresetViewSuperior()
{
    if( m_Viewer )
    {
        osg::ref_ptr<osgGA::TrackballManipulator>  cm = osg::dynamic_pointer_cast<osgGA::TrackballManipulator>( m_Viewer->getCameraManipulator() );
        osg::Quat q( 0., 0., 0., 1 );
        // is it a trackball manipulator?
        if( cm )
        {
            cm->setRotation( q );
        }
        else
        {
            wlog::warn( "WQtGLWidget(" + m_Viewer->getName() + ")" ) << "GL Widget does not use a TrackballManipulator. Preset cannot be used.";
        }
    }
}

void WQtGLWidget::setPresetViewInferior()
{
    if( m_Viewer )
    {
        osg::ref_ptr<osgGA::TrackballManipulator>  cm = osg::dynamic_pointer_cast<osgGA::TrackballManipulator>( m_Viewer->getCameraManipulator() );
        osg::Quat q( 0., -1., 0., 0. );
        // is it a trackball manipulator?
        if( cm )
        {
            cm->setRotation( q );
        }
        else
        {
            wlog::warn( "WQtGLWidget(" + m_Viewer->getName() + ")" ) << "GL Widget does not use a TrackballManipulator. Preset cannot be used.";
        }
    }
}

void WQtGLWidget::setPresetViewAnterior()
{
    if( m_Viewer )
    {
        osg::ref_ptr<osgGA::TrackballManipulator>  cm = osg::dynamic_pointer_cast<osgGA::TrackballManipulator>( m_Viewer->getCameraManipulator() );
        osg::Quat q( 0., -0.707107, -0.707107, 0. );
        // is it a trackball manipulator?
        if( cm )
        {
            cm->setRotation( q );
        }
        else
        {
            wlog::warn( "WQtGLWidget(" + m_Viewer->getName() + ")" ) << "GL Widget does not use a TrackballManipulator. Preset cannot be used.";
        }
    }
}

void WQtGLWidget::setPresetViewPosterior()
{
    if( m_Viewer )
    {
        osg::ref_ptr<osgGA::TrackballManipulator>  cm = osg::dynamic_pointer_cast<osgGA::TrackballManipulator>( m_Viewer->getCameraManipulator() );
        osg::Quat q( 0.707107, 0., 0., 0.707107 );
        // is it a trackball manipulator?
        if( cm )
        {
            cm->setRotation( q );
        }
        else
        {
            wlog::warn( "WQtGLWidget(" + m_Viewer->getName() + ")" ) << "GL Widget does not use a TrackballManipulator. Preset cannot be used.";
        }
    }
}

void WQtGLWidget::setFitScreenPosition()
{
    if( m_Viewer )
    {
        osg::ref_ptr<WGEZoomTrackballManipulator> cm = osg::dynamic_pointer_cast<WGEZoomTrackballManipulator>( m_Viewer->getCameraManipulator() );
        if( cm )
        {
            osg::Vec3d eye, center, up;
            cm->getHomePosition( eye, center, up );

            cm->setCenter( center );
            cm->fitToScreen( WKernel::getRunningKernel()->getGraphicsEngine()->getViewer()->getCamera() );
        }
        else
        {
            wlog::warn( "WQtGLWidget(" + m_Viewer->getName() + ")" ) << "GL Widget does not use a TrackballManipulator. Preset cannot be used.";
        }
    }
}

QMenu* WQtGLWidget::getCameraPresetsMenu()
{
    return m_cameraPresetMenu;
}

QMenu* WQtGLWidget::getCameraPresetsAndResetMenu()
{
    return m_cameraPresetResetMenu;
}

QAction* WQtGLWidget::getCameraResetAction()
{
    return m_cameraResetAction;
}

void WQtGLWidget::setPaused( bool pause )
{
    getViewer()->setPaused( pause );
}

bool WQtGLWidget::getPaused() const
{
    return getViewer()->getPaused();
}
