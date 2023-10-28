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

#include "WGEZoomTrackballManipulator.h"
#include "WGraphicsEngine.h"

WGEZoomTrackballManipulator::WGEZoomTrackballManipulator():
    TrackballManipulator( 0x02 ),
    m_zoom( 1.0 ),
    m_allowThrow( false ),
    m_paintMode( 0 )
{
    setTrackballSize( .3 ); // changes the effect of a mouse move for rotation
}

void WGEZoomTrackballManipulator::setByMatrix( const osg::Matrixd& matrix )
{
    m_zoom = 1.0 / matrix.getScale()[0];

    // The zoom needs to be undone before forwarding the matrix.
    TrackballManipulator::setByMatrix( osg::Matrixd::inverse( osg::Matrixd::scale( 1.0 / m_zoom, 1.0 / m_zoom, 1.0 / m_zoom ) ) * matrix );
}

osg::Matrixd WGEZoomTrackballManipulator::getMatrix() const
{
    return osg::Matrixd::scale( 1.0 / m_zoom, 1.0 / m_zoom, 1.0 / m_zoom ) * TrackballManipulator::getMatrix();
}

osg::Matrixd WGEZoomTrackballManipulator::getMatrixWithoutZoom() const
{
    return TrackballManipulator::getMatrix();
}

osg::Matrixd WGEZoomTrackballManipulator::getInverseMatrix() const
{
    return TrackballManipulator::getInverseMatrix() * osg::Matrixd::scale( m_zoom, m_zoom, m_zoom );
}

void WGEZoomTrackballManipulator::home( double /* currentTime */ )
{
    m_zoom = 1.0;
    TrackballManipulator::home( 0 /* currentTime */ );
}

bool WGEZoomTrackballManipulator::zoom( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us )
{
    double zoomDelta = 0.0;

    if( ea.getKey() && ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN )
    {
        if( ea.getKey() == osgGA::GUIEventAdapter::KEY_Minus )
        {
            zoomDelta = -0.05;
        }
        if( ea.getKey() == osgGA::GUIEventAdapter::KEY_Plus )
        {
            zoomDelta = 0.05;
        }
        if( zoomDelta != 0.0 )
        {
            m_zoom *= 1.0 + zoomDelta;
            us.requestRedraw();
        }
    }
    else
    {
        if( ea.getHandled() )
        {
            return true;
        }

        switch( ea.getScrollingMotion() )
        {
            case osgGA::GUIEventAdapter::SCROLL_UP:
                zoomDelta = 0.05;
                break;
            case osgGA::GUIEventAdapter::SCROLL_DOWN:
                zoomDelta = -0.05;
                break;
            case osgGA::GUIEventAdapter::SCROLL_2D:
                zoomDelta = 0.05 / 120.0 * ea.getScrollingDeltaY();
                break;
                // case osgGA::GUIEventAdapter::SCROLL_LEFT:
                // case osgGA::GUIEventAdapter::SCROLL_RIGHT:
                // case osgGA::GUIEventAdapter::SCROLL_NONE:
            default:
                // do nothing
                zoomDelta = 0.0;
                break;
        }
    }

    if( zoomDelta != 0.0 )
    {
        m_zoom *= 1.0 + zoomDelta;
        us.requestRedraw();
    }

    us.requestContinuousUpdate( false );
    return true;
}

bool WGEZoomTrackballManipulator::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us )
{
    _thrown &= m_allowThrow; // By default we do not want the auto-rotation thingy.

    if( WGraphicsEngine::getGraphicsEngine()->getScene()->isHomePositionRequested() )
    {
        // We set the scene to the manipulator home position if the scene
        // requests to do so. See WGEScene for more details.
        home( 0 );
        return true;
    }
    else if( ea.getEventType() == osgGA::GUIEventAdapter::SCROLL
             || ea.getKey() == osgGA::GUIEventAdapter::KEY_Minus
             ||  ea.getKey() == osgGA::GUIEventAdapter::KEY_Plus )
    {
        return zoom( ea, us );
    }
    // NOTE: we need to ignore the right mouse-button drag! This manipulates the underlying Trackball Manipulator while, at the same time, is
    // used for moving ROIS! Zooming is done using Scroll Wheel or +/- keys.
    else if( ( ea.getEventType() == osgGA::GUIEventAdapter::DRAG ) || ( ea.getEventType() == osgGA::GUIEventAdapter::PUSH ) )
    {
        if( ea.getButtonMask() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON )
        {
            return true;
        }
        else if(  ( ea.getButtonMask() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON ) && ( m_paintMode == 1 ) )
        {
            return true;
        }
        else
        {
            return TrackballManipulator::handle( ea, us );
        }
    }
    else
    {
        return TrackballManipulator::handle( ea, us );
    }
}

void WGEZoomTrackballManipulator::setPaintMode( int mode )
{
    m_paintMode = mode;
}

void WGEZoomTrackballManipulator::setThrow( bool allowThrow )
{
    m_allowThrow = allowThrow;
}

bool WGEZoomTrackballManipulator::getThrow() const
{
    return m_allowThrow;
}

void WGEZoomTrackballManipulator::computeHomePosition( const osg::Camera*, bool useBoundingBox )
{
    if( getNode() )
    {
        osg::BoundingSphere boundingSphere;

        if( useBoundingBox )
        {
            WGEZoomTrackballNodeVisitor cbVisitor;
            getNode()->accept( cbVisitor );
            osg::BoundingBox& bb = cbVisitor.getBoundingBox();

            if( bb.valid() )
            {
                boundingSphere.expandBy( bb );
            }
            else
            {
                boundingSphere = getNode()->getBound();
            }
        }
        else
        {
            boundingSphere = getNode()->getBound();
        }

        m_radius = osg::maximum( ( double ) boundingSphere.radius(), 1e-6 );

        // The more far away the number from 0 is, the stronger is the pan
        setHomePosition( boundingSphere.center() + osg::Vec3d( 0.0, -m_radius, 0.0 ),
                         boundingSphere.center(),
                         osg::Vec3d( 0.0, 0.0, 1.0 ),
                         _autoComputeHomePosition );
    }
}

void WGEZoomTrackballManipulator::fitToScreen( const osg::Camera* camera )
{
    if( !camera )
    {
        return;
    }

    computeHomePosition( camera, true );

    double radiusFac[] = {
         1,  1,  1,
        -1,  1,  1,
         1, -1,  1,
        -1, -1,  1,
         1,  1, -1,
        -1,  1, -1,
         1, -1, -1,
        -1, -1, -1
    };
    osg::Vec3 center = _homeCenter;
    osg::Matrix transf = camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
    double fac = INFINITY;
    for( int i = 0; i < 8; i++ )
    {
        osg::Vec3d vec = osg::Vec3( center.x() + m_radius * radiusFac[ i * 3 ],
                                    center.y() + m_radius * radiusFac[ i * 3 + 1 ],
                                    center.z() + m_radius * radiusFac[ i * 3 + 2 ] );
        osg::Vec3d screenCoords = vec * transf;

        double facX = abs( camera->getViewport()->width() / screenCoords.x() );
        double facY = abs( camera->getViewport()->height() / screenCoords.y() );

        fac = fmin( fac, facX );
        fac = fmin( fac, facY );
    }

    m_zoom = fac;
    setCenter( center );
}

bool WGEZoomTrackballManipulator::performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy )
{
    // scale panning based on zoom
    float scale = -0.5 * ( _distance / m_zoom ) * getThrowScale( eventTimeDelta );
    panModel( dx * scale, dy * scale );
    return true;
}

