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

#include <list>
#include <memory>
#include <string>

#include "WPickHandler.h"
#include "WPickHandler3D.h"
#include "WROI.h"

WROI::WROI():
    osg::Geode()
{
    properties();
}

WROI::~WROI()
{
}

void WROI::properties()
{
    m_properties = std::shared_ptr< WProperties >( new WProperties( "Properties", "This ROI's properties" ) );

    m_name = m_properties->addProperty( "Name", "The name of this ROI.", std::string( "ROI" ) );
    m_active = m_properties->addProperty( "Active", "Enable or disable the ROI.", true, boost::bind( &WROI::propertyChanged, this ) );
    m_show = m_properties->addProperty( "Show", "Toggles visibility of the ROI but does not disable it.", true,
                                        boost::bind( &WROI::propertyChanged, this ) );
    m_not = m_properties->addProperty( "Not", "Negates the effect of this ROI.", false, boost::bind( &WROI::propertyChanged, this ) );
    m_dirty = m_properties->addProperty( "Dirty", "", true ); // boost::bind( &WROI::propertyChanged, this ) );
    m_dirty->setHidden( true );
}

WPropBool WROI::invertProperty()
{
    return m_not;
}

WPropBool WROI::showProperty()
{
    return m_show;
}

WPropString WROI::nameProperty()
{
    return m_name;
}

WPropBool WROI::activeProperty()
{
    return m_active;
}

void WROI::propertyChanged()
{
    if( m_show->changed() )
    {
        if( m_show->get( true ) )
        {
            unhide();
        }
        else
        {
            hide();
        }
    }

    setDirty();
}

std::shared_ptr<WProperties> WROI::getProperties()
{
    return m_properties;
}

void WROI::setNot( bool isNot )
{
    m_not->set( isNot );
    setDirty();
}

bool WROI::isNot()
{
    return m_not->get();
}

bool WROI::active()
{
    return m_active->get();
}

void WROI::setActive( bool active )
{
    m_active->set( active );
    setDirty();
}

void WROI::setDirty()
{
    m_dirty->set( true );
    signalRoiChange();
}

bool WROI::dirty()
{
    return m_dirty->get();
}

void WROI::hide()
{
    setNodeMask( 0x0 );
}

void WROI::unhide()
{
    setNodeMask( 0xFFFFFFFF );
}

void WROI::signalRoiChange()
{
    for( std::list< std::shared_ptr< boost::function< void() > > >::iterator iter = m_changeNotifiers.begin();
                iter != m_changeNotifiers.end(); ++iter )
    {
        ( **iter )();
    }
}

void WROI::addROIChangeNotifier( std::shared_ptr< boost::function< void() > > notifier )
{
    std::unique_lock< std::shared_mutex > lock;
    lock = std::unique_lock< std::shared_mutex >( m_associatedNotifiersLock );
    m_changeNotifiers.push_back( notifier );
    lock.unlock();
}

void WROI::removeROIChangeNotifier( std::shared_ptr< boost::function< void() > > notifier )
{
    std::unique_lock< std::shared_mutex > lock;
    lock = std::unique_lock< std::shared_mutex >( m_associatedNotifiersLock );
    std::list<  std::shared_ptr< boost::function< void() > > >::iterator it;
    it = std::find( m_changeNotifiers.begin(), m_changeNotifiers.end(), notifier );
    if( it != m_changeNotifiers.end() )
    {
        m_changeNotifiers.erase( it );
    }
    lock.unlock();
}
