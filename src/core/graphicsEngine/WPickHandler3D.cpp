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

#include <string>
#include <utility>

#include "WPickHandler3D.h"

const std::string WPickHandler3D::unpickString = "unpick";

WPickHandler3D::WPickHandler3D() :
    m_hitResultLeft( WPickInfo3D() ),
    m_hitResultRight( WPickInfo3D() ),
    m_startPickLeft( WPickInfo3D() ),
    m_startPickRight( WPickInfo3D() )
{
}

void WPickHandler3D::unpickLeft()
{
    if( m_hitResultLeft != WPickInfo3D() )
    {
        m_hitResultLeft = WPickInfo3D( WPickHandler3D::unpickString );
        m_startPickLeft = WPickInfo3D();
    }
    m_pickSignal( std::make_pair( getHitResultLeft(), getHitResultRight() ) );
}

void WPickHandler3D::unpickRight()
{
    if( m_hitResultRight != WPickInfo3D() )
    {
        m_hitResultRight = WPickInfo3D( WPickHandler3D::unpickString );
        m_startPickRight = WPickInfo3D();
    }
    m_pickSignal( std::make_pair( getHitResultLeft(), getHitResultRight() ) );
}

std::string extractSuitableName( osgUtil::RayIntersector::Intersections::iterator hitr )
{
    if( !hitr->nodePath.empty() && !( hitr->nodePath.back()->getName().empty() ) )
    {
        return hitr->nodePath.back()->getName();
    }
    else if( hitr->drawable.valid() )
    {
        return  hitr->drawable->className();
    }
    assert( 0 && "This should not happen. Tell \"wiebel\" if it does." );
    return ""; // This line will not be reached.
}

WPickInfo3D createPickInfo( osg::Camera* camera, WPickInfo3D startPick, osg::Vec3 position, osg::Quat rotation, int buttons )
{
    osg::Vec3 dir = rotation * osg::Vec3( 0.0, 1.0, 0.0 );
    osg::Vec3 pos = position;

    if( buttons == WPickInfo3D::NONE )
    {
        return WPickInfo3D( "nothing", position, rotation, buttons );
    }

    osgUtil::RayIntersector::Intersections intersections;

    osg::ref_ptr< osgUtil::RayIntersector > picker = new osgUtil::RayIntersector( pos, dir );
    osgUtil::IntersectionVisitor iv( picker.get() );

    camera->accept( iv );

    bool intersectionsExist = picker->containsIntersections();
    WPickInfo3D pickInfo;

    WPickInfo3D fullPathpickInfo;
    bool startPickIsStillInList = false;
    osgUtil::RayIntersector::Intersections::iterator hitr;

    if( intersectionsExist )
    {
        intersections = picker->getIntersections();

        hitr = intersections.begin();
        while( hitr != intersections.end() )
        {
            std::string nodeName = extractSuitableName( hitr );
            fullPathpickInfo.appendToPickPath( nodeName );
            ++hitr;
        }

        assert( intersections.size() );
        hitr = intersections.begin();

        while( hitr != intersections.end() )
        {
            std::string nodeName = extractSuitableName( hitr );
            WAssert( nodeName.size() > 2, "Geode name too short for picking." );

            // now we skip everything that starts with an underscores or vr
            if( nodeName[0] == '_' || ( nodeName[0] == 'v' && nodeName[1] == 'r' ) )
            {
                ++hitr;
            }
            else
            {
                break;
            }
        }

        if( hitr == intersections.end() )
        {
            if( startPick.empty() )
            {
                return WPickInfo3D( "nothing", position, rotation, buttons );
            }
        }

        if( !startPick.empty() && startPick.getName() != WPickHandler3D::unpickString )
        {
            while( ( hitr != intersections.end() ) && !startPickIsStillInList )
            {
                WPickInfo3D pickInfoTmp( extractSuitableName( hitr ) );
                startPickIsStillInList |= ( pickInfoTmp.getName() == startPick.getName() );

                if( !startPickIsStillInList )
                {
                    ++hitr;
                }
            }
        }
    }
    else
    {
        if( startPick.empty() )
        {
            return WPickInfo3D( "nothing", position, rotation, buttons );
        }
    }

    if( startPickIsStillInList || ( intersectionsExist && ( startPick.getName() == WPickHandler3D::unpickString || startPick.empty() ) ) )
    {
        WPosition pickPos;
        pickPos[0] = hitr->getWorldIntersectPoint()[0];
        pickPos[1] = hitr->getWorldIntersectPoint()[1];
        pickPos[2] = hitr->getWorldIntersectPoint()[2];

        WVector3d pickNormal;
        const osgUtil::RayIntersector::Intersection::IndexList& vil = hitr->indexList;
        osg::ref_ptr< osg::Geometry > geo = dynamic_cast< osg::Geometry* >( hitr->drawable.get() );
        if( geo )
        {
            float* normals = ( float* ) geo->getNormalArray()->getDataPointer();
            int vertexIdx = vil[0];
            pickNormal[0] = normals[vertexIdx * 3];
            pickNormal[1] = normals[vertexIdx * 3 + 1];
            pickNormal[2] = normals[vertexIdx * 3 + 2];
        }

        pickInfo = WPickInfo3D( extractSuitableName( hitr ), position, rotation, buttons, pickPos, pickNormal );
    }

    if( !startPickIsStillInList && !startPick.empty() && startPick.getName() != WPickHandler3D::unpickString )
    {
        pickInfo = WPickInfo3D( startPick.getName(), position, rotation, buttons,
                              startPick.getPickPosition(), startPick.getPickNormal(), startPick.getPickPath() );
    }

    pickInfo.setPickPath( fullPathpickInfo.getPickPath() );

    return pickInfo;
}

WPickInfo3D WPickHandler3D::getHitResultLeft()
{
    return m_hitResultLeft;
}

WPickInfo3D WPickHandler3D::getHitResultRight()
{
    return m_hitResultRight;
}

boost::signals2::signal< void( std::pair< WPickInfo3D, WPickInfo3D > ) >* WPickHandler3D::getPickSignal()
{
    return &m_pickSignal;
}

void WPickHandler3D::pick( osg::Camera* camera,
                           osg::Vec3 leftPosition,
                           osg::Vec3 rightPosition,
                           osg::Quat leftRotation,
                           osg::Quat rightRotation,
                           int leftButtons,
                           int rightButtons )
{
    WPickInfo3D oldLeft = m_hitResultLeft;
    WPickInfo3D oldRight = m_hitResultRight;

    m_hitResultLeft = createPickInfo( camera, m_startPickLeft, leftPosition, leftRotation, leftButtons );
    if( m_startPickLeft.empty() )
    {
        m_startPickLeft = m_hitResultLeft;
    }

    m_hitResultRight = createPickInfo( camera, m_startPickRight, rightPosition, rightRotation, rightButtons );
    if( m_startPickRight.empty() )
    {
        m_startPickRight = m_hitResultRight;
    }


    if( oldLeft.getButtons() != WPickInfo3D::NONE && leftButtons == WPickInfo3D::NONE )
    {
        unpickLeft();
    }

    if( oldRight.getButtons() != WPickInfo3D::NONE && rightButtons == WPickInfo3D::NONE )
    {
        unpickRight();
    }

    m_pickSignal( std::make_pair( getHitResultLeft(), getHitResultRight() ) );
}
