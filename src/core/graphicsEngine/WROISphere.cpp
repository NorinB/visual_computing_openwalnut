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

#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include <osg/ShapeDrawable>

#include "WGEUtils.h"
#include "WGraphicsEngine.h"
#include "WROISphere.h"
#include "callbacks/WGEFunctorCallback.h"

size_t WROISphere::maxSphereId = 0;


WROISphere::WROISphere( WPosition position, float radius ) :
    WROI(),
    sphereId( maxSphereId++ ),
    m_position( position ),
    m_originalPosition( position ),
    m_radius( radius ),
    m_pickNormal( WVector3d() ),
    m_oldPixelPosition( WVector2d::zero() ),
    m_color( osg::Vec4( 0.f, 1.f, 1.f, 0.4f ) ),
    m_notColor( osg::Vec4( 1.0f, 0.0f, 0.0f, 0.4f ) ),
    m_lockPoint( WVector3d( 0.0, 0.0, 0.0 ) ),
    m_lockVector( WVector3d( 1.0, 1.0, 1.0 ) ),
    m_lockOnVector( false ),
    m_lockX( false ),
    m_lockY( false ),
    m_lockZ( false )
{
    std::shared_ptr< WGraphicsEngine > ge = WGraphicsEngine::getGraphicsEngine();
    assert( ge );
    std::shared_ptr< WGEViewer > viewer = ge->getViewerByName( "Main View" );
    assert( viewer );
    m_viewer = viewer;
    m_pickHandler = m_viewer->getPickHandler();
    m_pickHandler3D = m_viewer->getPickHandler3D();
    m_pickHandler->getPickSignal()->connect( boost::bind( &WROISphere::registerRedrawRequest, this, boost::placeholders::_1 ) );
    m_pickHandler3D->getPickSignal()->connect( boost::bind( &WROISphere::registerRedrawRequest3D, this, boost::placeholders::_1 ) );

    redrawSphere();
    //**********************************************************
    m_dirty->set( true );

    setUserData( this );

    setUpdateCallback( new WGEFunctorCallback< osg::Node >( boost::bind( &WROISphere::updateGFX, this ) ) );
}

void WROISphere::redrawSphere()
{
    removeDrawables( 0 );

    osg::ShapeDrawable* shape = new osg::ShapeDrawable( new osg::Sphere( osg::Vec3( m_position[0], m_position[1], m_position[2] ), m_radius ) );
    shape->setColor( m_color );

    std::stringstream ss;
    ss << "ROISphere" << sphereId;

    setName( ss.str() );
    shape->setName( ss.str() );

    addDrawable( shape );
}

WROISphere::~WROISphere()
{
//    std::cout << "destructor called" << std::endl;
//    std::cout << "ref count geode: " << m_geode->referenceCount() << std::endl;
//
//    WGraphicsEngine::getGraphicsEngine()->getScene()->remove( m_geode );
}

WPosition WROISphere::getPosition() const
{
    return m_position;
}

osg::Quat WROISphere::getRotation() const
{
    return m_rotation;
}

void WROISphere::setPosition( WPosition position )
{
    m_position = position;
    m_lockPoint = position;
    m_originalPosition = position;
    m_dirty->set( true );
}

void WROISphere::setRotation( osg::Quat rotation )
{
    m_rotation = rotation;
    m_dirty->set( true );
}

void WROISphere::setPosition( float x, float y, float z )
{
    m_position = WPosition( x, y, z );
    m_lockPoint = WPosition( x, y, z );
    m_originalPosition = WPosition( x, y, z );
    m_dirty->set( true );
}


void WROISphere::setX( float x )
{
    m_position.x() = x;
    m_originalPosition = m_position;
    m_dirty->set( true );
}

void WROISphere::setY( float y )
{
    m_position.y() = y;
    m_originalPosition = m_position;
    m_dirty->set( true );
}

void WROISphere::setZ( float z )
{
    m_position.z() = z;
    m_originalPosition = m_position;
    m_dirty->set( true );
}


void WROISphere::registerRedrawRequest( WPickInfo pickInfo )
{
    m_pickInfo = pickInfo;
}

void WROISphere::registerRedrawRequest3D( std::pair< WPickInfo3D, WPickInfo3D > pickInfo )
{
    m_pickInfo3D = pickInfo;
}

bool WROISphere::handlePick()
{
    std::stringstream ss;
    ss << "ROISphere" << sphereId << "";

    bool mouseMove = false;

    if( m_pickInfo.getName() == ss.str() )
    {
        WVector2d newPixelPos( m_pickInfo.getPickPixel() );
        if( m_isPicked )
        {
            osg::Vec3 in( newPixelPos.x(), newPixelPos.y(), 0.0 );
            osg::Vec3 world = wge::unprojectFromScreen( in, m_viewer->getCamera() );

            WPosition newPixelWorldPos( world[0], world[1], world[2] );
            WPosition oldPixelWorldPos;
            if( m_oldPixelPosition.x() == 0 && m_oldPixelPosition.y() == 0 )
            {
                oldPixelWorldPos = newPixelWorldPos;
            }
            else
            {
                osg::Vec3 in( m_oldPixelPosition.x(), m_oldPixelPosition.y(), 0.0 );
                osg::Vec3 world = wge::unprojectFromScreen( in, m_viewer->getCamera() );
                oldPixelWorldPos = WPosition( world[0], world[1], world[2] );
            }

            WVector3d moveVec = newPixelWorldPos - oldPixelWorldPos;

            // move sphere
            if( m_pickInfo.getModifierKey() == WPickInfo::NONE )
            {
                moveSphere( moveVec );
                mouseMove = true;
            }
        }

        m_oldPixelPosition = newPixelPos;
        m_dirty->set( true );
        m_isPicked = true;
    }
    if( m_isPicked && m_pickInfo.getName() == WPickHandler::unpickString )
    {
        // Perform all actions necessary for finishing a pick
        m_pickNormal = WVector3d();
        m_isPicked = false;
    }

    return mouseMove;
}

bool WROISphere::handlePick3D()
{
    std::stringstream ss;
    ss << "ROISphere" << sphereId << "";

    bool mouseMove = false;

    if( m_pickInfo3D.first.getName() == ss.str() )
    {
        if( m_isPicked3D )
        {
            osg::Matrixd sceneMatrix = getWorldMatrices().back();
            osg::Vec3 pos( m_position );
            osg::Vec3 moveVec( pos );
            moveVec = moveVec * sceneMatrix;

            moveVec += ( m_pickInfo3D.first.getPosition() - m_oldPickInfo3D.first.getPosition() );

            osg::Quat rotDiff = m_oldPickInfo3D.first.getRotation().inverse() * m_pickInfo3D.first.getRotation();
            osg::Matrixd rotMatrix = osg::Matrixd::translate( -m_pickInfo3D.first.getPosition() ) * osg::Matrixd::rotate( rotDiff ) *
                                     osg::Matrixd::translate( m_pickInfo3D.first.getPosition() );

            moveVec = moveVec * rotMatrix;
            moveVec = moveVec * osg::Matrixd::inverse( sceneMatrix );
            moveVec = moveVec - pos;

            moveSphere( moveVec );
            mouseMove = true;

            m_rotation *= rotDiff;
        }

        m_dirty->set( true );
        m_isPicked3D = true;
    }
    if( m_isPicked3D && m_pickInfo3D.first.getName() == WPickHandler::unpickString )
    {
        // Perform all actions necessary for finishing a pick
        m_pickNormal = WVector3d();
        m_isPicked3D = false;
    }

    return mouseMove;
}

void WROISphere::updateGFX()
{
    bool roiChanged = handlePick();
    if( m_pickInfo3D.first.getButtons() & WPickInfo3D::TRIGGER )
    {
        roiChanged = handlePick3D();
    }
    m_oldPickInfo3D = m_pickInfo3D;

    if( m_dirty->get() )
    {
        redrawSphere();
        m_dirty->set( false );
    }

    if( roiChanged )
    {
        signalRoiChange();
    }
}

void WROISphere::moveSphere( WVector3d offset )
{
    m_position += offset;

    if( m_lockX )
    {
        m_position[0] = m_lockPoint[0];
    }

    if( m_lockY )
    {
        m_position[1] = m_lockPoint[1];
    }

    if( m_lockZ )
    {
        m_position[2] = m_lockPoint[2];
    }

    if( m_lockOnVector )
    {
        float k = ( ( m_lockPoint[0] * m_lockVector[0] ) - ( m_position.x() * m_lockVector[0] ) +
                    ( m_lockPoint[1] * m_lockVector[1] ) - ( m_position.y() * m_lockVector[1] ) +
                    ( m_lockPoint[2] * m_lockVector[2] ) - ( m_position.z() * m_lockVector[2] ) ) /
                    ( m_lockVector[0] * m_lockVector[0] + m_lockVector[1] * m_lockVector[1] + m_lockVector[2] * m_lockVector[2] ) * -1.0;
        m_position = m_lockPoint + ( m_lockVector * k );
    }
}

void WROISphere::setLockX( bool value )
{
    m_lockX = value;
    m_lockPoint = m_position;
}

void WROISphere::setLockY( bool value )
{
    m_lockY = value;
    m_lockPoint = m_position;
}

void WROISphere::setLockZ( bool value )
{
    m_lockZ = value;
    m_lockPoint = m_position;
}


void WROISphere::setColor( osg::Vec4 color )
{
    m_color = color;
    redrawSphere();
}

void WROISphere::setNotColor( osg::Vec4 color )
{
    m_notColor = color;
}

void  WROISphere::setLockVector( WVector3d vector )
{
    m_lockVector = vector;
    m_lockPoint = m_position;
}

void  WROISphere::setLockOnVector( bool value )
{
    m_lockOnVector = value;
}
