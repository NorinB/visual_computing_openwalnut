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

#include <boost/filesystem.hpp>

#include "WProperties.h"
#include "WPropertyBase.h"
#include "WPropertyGroupBase.h"
#include "WPropertyVariable.h"
#include "WTransferFunction.h"
#include "WTransferFunction2D.h"
#include "exceptions/WPropertyNameMalformed.h"

WPropertyBase::WPropertyBase( std::string name, std::string description ):
    std::enable_shared_from_this< WPropertyBase >(),
    m_name( name ),
    m_description( description ),
    m_hidden( false ),
    m_purpose( PV_PURPOSE_PARAMETER ),
    signal_PropertyChange(),
    m_updateCondition( new WConditionSet() )
{
    // check name validity
    if( ( m_name.find( std::string( "/" ) ) != std::string::npos ) || m_name.empty() )
    {
        throw WPropertyNameMalformed( std::string( "Property name \"" + name +
                                      "\" is malformed. Do not use slashes (\"/\") or empty strings in property names." ) );
    }
}

WPropertyBase::WPropertyBase( const WPropertyBase& from ):
    std::enable_shared_from_this< WPropertyBase >(),
    m_name( from.m_name ),
    m_description( from.m_description ),
    m_hidden( from.m_hidden ),
    m_type( from.m_type ),
    m_purpose( from.m_purpose ),
    signal_PropertyChange(),                    // create a new and empty signal
    m_updateCondition( new WConditionSet() )    // create a new condition set. Do not copy it.
{
}

WPropertyBase::~WPropertyBase()
{
    // cleanup
}

std::string WPropertyBase::getName() const
{
    return m_name;
}

std::string WPropertyBase::getDescription() const
{
    return m_description;
}

PROPERTY_TYPE WPropertyBase::getType() const
{
    return m_type;
}

PROPERTY_PURPOSE WPropertyBase::getPurpose() const
{
    return m_purpose;
}

void WPropertyBase::setPurpose( PROPERTY_PURPOSE purpose )
{
    m_purpose = purpose;
}

void WPropertyBase::updateType()
{
    m_type = PV_UNKNOWN;
}

bool WPropertyBase::isHidden() const
{
    return m_hidden;
}

void WPropertyBase::setHidden( bool hidden )
{
    if( m_hidden != hidden )
    {
        m_hidden = hidden;
        m_updateCondition->notify();
    }
}

WPropInt WPropertyBase::toPropInt()
{
    return std::dynamic_pointer_cast< WPVInt >( shared_from_this() );
}

WPropDouble WPropertyBase::toPropDouble()
{
    return std::dynamic_pointer_cast< WPVDouble >( shared_from_this() );
}

WPropBool WPropertyBase::toPropBool()
{
    return std::dynamic_pointer_cast< WPVBool >( shared_from_this() );
}

WPropString WPropertyBase::toPropString()
{
    return std::dynamic_pointer_cast< WPVString >( shared_from_this() );
}

WPropFilename WPropertyBase::toPropFilename()
{
    return std::dynamic_pointer_cast< WPVFilename >( shared_from_this() );
}

WPropSelection WPropertyBase::toPropSelection()
{
    return std::dynamic_pointer_cast< WPVSelection >( shared_from_this() );
}

WPropColor WPropertyBase::toPropColor()
{
    return std::dynamic_pointer_cast< WPVColor >( shared_from_this() );
}

WPropPosition WPropertyBase::toPropPosition()
{
    return std::dynamic_pointer_cast< WPVPosition >( shared_from_this() );
}

WPropGroup WPropertyBase::toPropGroup()
{
    return std::dynamic_pointer_cast< WPVGroup >( shared_from_this() );
}

WPropertyGroupBase::SPtr WPropertyBase::toPropGroupBase()
{
    return std::dynamic_pointer_cast< WPropertyGroupBase >( shared_from_this() );
}

WPropMatrix4X4 WPropertyBase::toPropMatrix4X4()
{
    return std::dynamic_pointer_cast< WPVMatrix4X4 >( shared_from_this() );
}

WPropTrigger WPropertyBase::toPropTrigger()
{
    return std::dynamic_pointer_cast< WPVTrigger >( shared_from_this() );
}

WPropTransferFunction WPropertyBase::toPropTransferFunction()
{
    return std::dynamic_pointer_cast< WPVTransferFunction >( shared_from_this() );
}

WPropTransferFunction2D WPropertyBase::toPropTransferFunction2D()
{
    return std::dynamic_pointer_cast< WPVTransferFunction2D >( shared_from_this() );
}

std::shared_ptr< WCondition > WPropertyBase::getUpdateCondition() const
{
    return m_updateCondition;
}

WPropInterval WPropertyBase::toPropInterval()
{
    return std::dynamic_pointer_cast< WPVInterval >( shared_from_this() );
}

