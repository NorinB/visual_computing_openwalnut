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

#include "core/common/WLimits.h"
#include "WEventIDLimitationPropertyHandler.h"


WEventIDLimitationPropertyHandler::WEventIDLimitationPropertyHandler( WProtonData::SPtr protonData,
                                            WPropertyGroup::SPtr properties,
                                            WEventIDLimitationPropertyHandler::CallbackPtr dataUpdate ):
    m_protonData( protonData ),
    m_properties( properties ),
    m_dataUpdate( dataUpdate )
{
}

void WEventIDLimitationPropertyHandler::createProperties()
{
    WPropertyBase::PropertyChangeNotifierType eventIDNotifier = boost::bind( &WEventIDLimitationPropertyHandler::updateMesh, this );
    WPropGroup eventIDGroup = m_properties->addPropertyGroup( "Event Id Limitation", "Adjust the range of eventIDs to be shown.", 0 );
    m_minCap = eventIDGroup->addProperty( "Minimum event id", "Filters out every event id which is lower than the set value.", 1 );
    m_maxCap = eventIDGroup->addProperty( "Maximum event id", "Filters out every event id which is higher than the set value.", 2000 );
    m_applySelection = eventIDGroup->addProperty( "Set selection", "Apply", WPVBaseTypes::PV_TRIGGER_READY, eventIDNotifier );

    updateProperty();
}

void WEventIDLimitationPropertyHandler::updateProperty()
{
    if( m_protonData->isColumnAvailable( WSingleSelectorName::getEventId() ) )
    {
        m_minCap->setHidden( false );
        m_maxCap->setHidden( false );
        m_applySelection->setHidden( false );

        determineMinMaxEventID();
    }
    else
    {
        m_minCap->setHidden( true );
        m_maxCap->setHidden( true );
        m_applySelection->setHidden( true );
    }
}

void WEventIDLimitationPropertyHandler::updateMesh()
{
    m_dataUpdate( );

    if( m_applySelection->get( true ) == WPVBaseTypes::PV_TRIGGER_TRIGGERED )
    {
        m_applySelection->set( WPVBaseTypes::PV_TRIGGER_READY, false );
    }
}

void WEventIDLimitationPropertyHandler::determineMinMaxEventID()
{
    int eventIDIndex = m_protonData->getColumnIndexBySelection( WSingleSelectorName::getEventId() );

    if( eventIDIndex < 0 )
    {
        return;
    }

    int minCap = wlimits::MAX_INT32_T;
    int maxCap = wlimits::MIN_INT32_T;
    for( auto iter = m_protonData->getCSVData()->begin(); iter != m_protonData->getCSVData()->end(); iter++ )
    {
        int calc = std::stoi( std::string( ( *iter ).at( eventIDIndex ) ) );
        if( calc < minCap )
        {
            minCap = calc;
        }
        if( calc > maxCap )
        {
            maxCap = calc;
        }
    }

    m_minCap->setMin( minCap );
    m_minCap->setMax( maxCap );
    m_maxCap->setMin( minCap );
    m_maxCap->setMax( maxCap );

    m_minCap->set( minCap );
    m_maxCap->set( maxCap );
}

WPropInt WEventIDLimitationPropertyHandler::getMinCap()
{
    return m_minCap;
}

WPropInt WEventIDLimitationPropertyHandler::getMaxCap()
{
    return m_maxCap;
}
