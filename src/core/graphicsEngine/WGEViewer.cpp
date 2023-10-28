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

#include <osg/Camera>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/UFOManipulator>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>

#include "WGE2DManipulator.h"
#include "WGEGroupNode.h"
#include "WGENoOpManipulator.h"
#include "WGEViewer.h"
#include "WGEZoomTrackballManipulator.h"
#include "WGraphicsEngine.h"
#include "WMouseLocationHandler.h"
#include "WPickHandler.h"
#include "WPickHandler3D.h"
#include "core/common/WConditionOneShot.h"
#include "core/common/WLogger.h"
#include "core/common/WThreadedRunner.h"
#include "exceptions/WGEInitFailed.h"

WGEViewer::WGEViewer( std::string name, osg::ref_ptr<osg::Referenced> wdata, int x, int y, int width, int height,
                      WGECamera::ProjectionMode projectionMode ):
    WGEGraphicsWindow( wdata, x, y, width, height ),
    std::enable_shared_from_this< WGEViewer >(),
    m_name( name ),
    m_scene( new WGEGroupNode ),
    m_rendered( WBoolFlag::SPtr( new WBoolFlag( new WConditionOneShot(), false ) ) ),
    m_screenCapture( new WGEScreenCapture() ),
    m_inAnimationMode( false ),
    m_effectHorizon( new WGEViewerEffectHorizon() ),
    m_effectVignette( new WGEViewerEffectVignette() ),
    m_effectImageOverlay( new WGEViewerEffectImageOverlay() ),
    m_paused( false )
{
    try
    {
        m_View = osg::ref_ptr<osgViewer::Viewer>( new osgViewer::Viewer );

        osg::ref_ptr< WGECamera > cam( new WGECamera( width, height, projectionMode ) );
        m_View->setCamera( cam );
        m_queryCallback = new QueryCallback( cam, m_rendered );
        m_View->getCamera()->setInitialDrawCallback( m_queryCallback );
        m_View->getCamera()->setFinalDrawCallback( m_screenCapture );

        m_View->getCamera()->setGraphicsContext( m_GraphicsWindow.get() );

        m_View->getCamera()->getGraphicsContext()->getState()->resetVertexAttributeAlias( false, 8 );
        m_View->getCamera()->getGraphicsContext()->getState()->setUseModelViewAndProjectionUniforms( true );
        m_View->getCamera()->getGraphicsContext()->getState()->setUseVertexAttributeAliasing( true );
        m_View->getCamera()->getGraphicsContext()->getState()->setCheckForGLErrors( osg::State::CheckForGLErrors::ONCE_PER_ATTRIBUTE );

        m_View->getCamera()->getOrCreateStateSet()->addUniform( new osg::Uniform( "ow_lightsource", osg::Vec4( 0.0, 0.0, 1.0, 1.0 ) ) );

        m_mouseLocationHandler = new WMouseLocationHandler( name );
        m_View->addEventHandler( m_mouseLocationHandler );

        switch( projectionMode )
        {
            case( WGECamera::ORTHOGRAPHIC ):
                m_pickHandler = new WPickHandler( name );
                m_pickHandler3D = new WPickHandler3D();
                m_View->addEventHandler( m_pickHandler );
                if( name != std::string( "Main View" ) )
                    break;
                /* FALLTHRU */
            case( WGECamera::PERSPECTIVE ):
                // camera manipulator
                m_View->setCameraManipulator( new WGEZoomTrackballManipulator() );

                m_View->setLightingMode( osg::View::HEADLIGHT ); // this is the default anyway

                break;
            case( WGECamera::TWO_D ):
                // no manipulators nor gui handlers
                break;
            case( WGECamera::TWO_D_UNIT ):
                // use no-op handler by default
                m_View->setCameraManipulator( new WGENoOpManipulator() );
                break;
            default:
                throw WGEInitFailed( std::string( "Unknown projection mode" ) );
        }

        // add the stats handler
        osgViewer::StatsHandler* statsHandler = new osgViewer::StatsHandler();
        statsHandler->setKeyEventTogglesOnScreenStats( 'F' );
        m_View->addEventHandler( statsHandler );

        // Properties of the view. Collects props of the effects and similar
        m_properties = std::shared_ptr< WProperties >( new WProperties( "Viewer Properties", "The view's properties" ) );
        m_bgColor = m_properties->addProperty( "Background Color", "Default background color if not overwritten by a camera effect.",
                                               defaultColor::WHITE,
                                               boost::bind( &WGEViewer::updateBgColor, this ) );
        m_throwing = m_properties->addProperty( "Throwing", "If checked, you can grab the scene and throw it. It will keep the rotation impulse.",
                                                false,
                                                boost::bind( &WGEViewer::updateThrowing, this ) );

        WPropGroup effects = m_properties->addPropertyGroup( "Camera Effects", "Several effects that to not depend on any scene content." );
        effects->addProperty( m_effectHorizon->getProperties() );
        effects->addProperty( m_effectVignette->getProperties() );
        effects->addProperty( m_effectImageOverlay->getProperties() );

        // scene node
        m_View->setSceneData( m_scene );
        // add effects to it:
        m_scene->insert( m_effectVignette );
        m_scene->insert( m_effectImageOverlay );
        m_scene->insert( m_effectHorizon );

        // apply the above default
        updateThrowing();
        updateBgColor();
    }
    catch( ... )
    {
        throw WGEInitFailed( std::string( "Initialization of WGEViewer failed" ) );
    }
}

WGEViewer::~WGEViewer()
{
    // cleanup
    close();
}

osg::ref_ptr<osgViewer::Viewer> WGEViewer::getView()
{
    return m_View;
}

void WGEViewer::setCameraManipulator( osg::ref_ptr<osgGA::MatrixManipulator> manipulator )
{
    if( !m_inAnimationMode )
    {
        m_View->setCameraManipulator( manipulator );
    }
}

osg::ref_ptr<osgGA::MatrixManipulator> WGEViewer::getCameraManipulator()
{
    return m_View->getCameraManipulator();
}

void WGEViewer::setCamera( osg::ref_ptr<WGECamera> camera )
{
    m_View->setCamera( camera );
    // redraw request?? No since it redraws permanently and uses the new settings
}

osg::ref_ptr<WGECamera> WGEViewer::getCamera()
{
    return dynamic_cast< WGECamera* >( m_View->getCamera() );
}

void WGEViewer::setScene( osg::ref_ptr< WGEGroupNode > node )
{
    m_sceneMainNode = node;

    m_effectImageOverlay->setReferenceViewer( shared_from_this() );

    m_scene->clear();
    m_scene->insert( m_sceneMainNode );
    // add effects to scene node. We cleared it earlier.
    m_scene->insert( m_effectVignette );
    m_scene->insert( m_effectImageOverlay );
    m_scene->insert( m_effectHorizon );
}

osg::ref_ptr< WGEGroupNode > WGEViewer::getScene()
{
    return m_sceneMainNode;
}

void WGEViewer::updateThrowing()
{
    WGEZoomTrackballManipulator* manipulator = dynamic_cast< WGEZoomTrackballManipulator* >( getCameraManipulator().get() );
    if( manipulator )
    {
        manipulator->setThrow( m_throwing->get() );
    }
}

void WGEViewer::updateBgColor()
{
    m_View->getCamera()->setClearColor( m_bgColor->get() );
}

void WGEViewer::setBgColor( const WColor& bgColor )
{
    m_bgColor->set( bgColor );
}

WColor WGEViewer::getBgColor() const
{
    return m_bgColor->get();
}

void WGEViewer::paint()
{
    m_View->frame();
}

void WGEViewer::resize( int width, int height )
{
    m_View->getEventQueue()->windowResize( 0, 0, width, height );

    WGEGraphicsWindow::resize( width, height );

    // also update the camera
    m_View->getCamera()->setViewport( 0, 0, width, height );
    WGECamera* camera = dynamic_cast< WGECamera* >( m_View->getCamera() );
    if( camera )
    {
        camera->resize();
    }
}

void WGEViewer::close()
{
    // delete/unset all the objects we sponsored a "shared_from_this" pointer to ensure the viewer gets deleted after close
    m_effectImageOverlay->setReferenceViewer( WGEViewer::SPtr() );

    // forward close event
    WGEGraphicsWindow::close();
}

std::string WGEViewer::getName() const
{
    return m_name;
}

osg::ref_ptr< WPickHandler > WGEViewer::getPickHandler()
{
    return m_pickHandler;
}

osg::ref_ptr< WPickHandler3D > WGEViewer::getPickHandler3D()
{
    return m_pickHandler3D;
}

osg::ref_ptr< WMouseLocationHandler > WGEViewer::getMouseLocationHandler()
{
    return m_mouseLocationHandler;
}

void WGEViewer::reset()
{
    m_View->home();
}

WGEScreenCapture::RefPtr WGEViewer::getScreenCapture() const
{
    return m_screenCapture;
}

std::string WGEViewer::getOpenGLVendor() const
{
    return m_queryCallback->getVendor();
}

WBoolFlag::SPtr WGEViewer::isFrameRendered() const
{
    return m_rendered;
}

WGEViewer::QueryCallback::QueryCallback( osg::ref_ptr<WGECamera> camera, WBoolFlag::SPtr run ):
    m_vendor( "" ),
    m_run( run ),
    m_camera( camera )
{
    // init
}

WGEViewer::QueryCallback::~QueryCallback()
{
    // cleanup
}

void WGEViewer::QueryCallback::operator()( osg::RenderInfo& /* renderInfo */ ) const
{
    const GLubyte* vendor = glGetString( GL_VENDOR );
    m_vendor = reinterpret_cast< const char* >( vendor );

    // job done. De-register.
    m_camera->setInitialDrawCallback( NULL );
    m_run->set( true );
}

std::string WGEViewer::QueryCallback::getVendor() const
{
    return m_vendor;
}

WGEAnimationManipulator::RefPtr WGEViewer::animationMode( bool on )
{
    if( m_inAnimationMode && !on ) // turn off mode
    {
        m_inAnimationMode = false;

        // restore old manipulator
        m_View->setCameraManipulator( m_animationModeManipulatorBackup );
        return NULL;
    }
    else if( !m_inAnimationMode && on ) // turn on
    {
        m_inAnimationMode = true;

        // backup
        m_animationModeManipulatorBackup = getCameraManipulator();

        // create animation manipulator
        WGEAnimationManipulator::RefPtr anim = new WGEAnimationManipulator();
        m_View->setCameraManipulator( anim );
        return anim;
    }
    else if( m_inAnimationMode ) // already on
    {
        return dynamic_cast< WGEAnimationManipulator* >( getCameraManipulator().get() );
    }

    // else: do nothing
    return NULL;
}

bool WGEViewer::isAnimationMode() const
{
    return m_inAnimationMode;
}

WGEViewerEffectHorizon::SPtr WGEViewer::getBackground()
{
    return m_effectHorizon;
}

WGEViewerEffectImageOverlay::SPtr WGEViewer::getImageOverlay()
{
    return m_effectImageOverlay;
}

WGEViewerEffectVignette::SPtr WGEViewer::getVignette()
{
    return m_effectVignette;
}

WGEViewerEffectHorizon::ConstSPtr WGEViewer::getBackground() const
{
    return m_effectHorizon;
}

WGEViewerEffectImageOverlay::ConstSPtr WGEViewer::getImageOverlay() const
{
    return m_effectImageOverlay;
}

WGEViewerEffectVignette::ConstSPtr WGEViewer::getVignette() const
{
    return m_effectVignette;
}

WProperties::SPtr WGEViewer::getProperties() const
{
    return m_properties;
}

void WGEViewer::setEffectsActiveDefault( bool activeByDefault )
{
    getBackground()->setEnabledByDefault( activeByDefault );
    getImageOverlay()->setEnabledByDefault( activeByDefault );
    getVignette()->setEnabledByDefault( activeByDefault );
}

void WGEViewer::setPaused( bool pause )
{
    m_paused = pause;
}

bool WGEViewer::getPaused() const
{
    return m_paused;
}

void WGEViewer::handleVisibilityChange( bool visible )
{
    getView()->getScene()->getSceneData()->setNodeMask( visible * 0xFFFFFFFF );
}

void WGEViewer::requestContinuousUpdate( bool continuous )
{
    getView()->requestContinuousUpdate( continuous );
}
