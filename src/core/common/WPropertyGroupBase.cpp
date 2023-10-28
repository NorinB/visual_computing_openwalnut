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

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/tokenizer.hpp>

#include "WLogger.h"
#include "WPropertyGroupBase.h"
#include "WPropertyHelper.h"
#include "WStringUtils.h"
#include "exceptions/WPropertyNotUnique.h"
#include "exceptions/WPropertyUnknown.h"

const std::string WPropertyGroupBase::separator = "/";

WPropertyGroupBase::WPropertyGroupBase( std::string name, std::string description ):
    WPropertyBase( name, description ),
    m_properties(),
    m_autoHideEmpty( true )
{
    // this groups update condition also fires upon group modification -> add WSharedObject condition
    m_updateCondition->add( m_properties.getChangeCondition() );
}

WPropertyGroupBase::~WPropertyGroupBase()
{
}

WPropertyGroupBase::WPropertyGroupBase( const WPropertyGroupBase& from ):
    WPropertyBase( from ),
    m_properties()
{
    // copy the properties inside

    // lock, unlocked if l looses focus
    PropertySharedContainerType::ReadTicket l = from.m_properties.getReadTicket();

    // we need to make a deep copy here.
    for( PropertyConstIterator iter = l->get().begin(); iter != l->get().end(); ++iter )
    {
        // clone them to keep dynamic type
        addArbitraryProperty( ( *iter )->clone() );
    }

    // unlock explicitly
    l.reset();

    // this groups update condition also fires upon group modification -> add WSharedObject condition
    m_updateCondition->add( m_properties.getChangeCondition() );
}

bool WPropertyGroupBase::propNamePredicate( std::shared_ptr< WPropertyBase > prop1, std::shared_ptr< WPropertyBase > prop2 ) const
{
    return ( prop1->getName() == prop2->getName() );
}

std::shared_ptr< WPropertyBase > WPropertyGroupBase::findProperty( const WPropertyGroupBase* const props, std::string name ) const
{
    std::shared_ptr< WPropertyBase > result = std::shared_ptr< WPropertyBase >();

    // lock, unlocked if l looses focus
    PropertySharedContainerType::ReadTicket l = props->m_properties.getReadTicket();

    // iterate over the items
    for( PropertyContainerType::const_iterator it = l->get().begin(); it != l->get().end(); ++it )
    {
        if( ( *it )->getName() == name )
        {
            result = ( *it );
            break;
        }
    }

    // done. Unlocked after l looses focus.
    return result;
}

std::shared_ptr< WPropertyBase > WPropertyGroupBase::findProperty( std::string name ) const
{
    std::shared_ptr< WPropertyBase > result = std::shared_ptr< WPropertyBase >();

    // tokenize the name -> contains any paths?
    typedef boost::tokenizer<boost::char_separator< char > > tokenizer;
    boost::char_separator< char > sep( WPropertyGroupBase::separator.c_str() );   // separate by /
    tokenizer tok( name, sep );

    // iterate along the path
    const WPropertyGroupBase* curProps = this;       // the group currently in while traversing the path
    for( tokenizer::iterator it = tok.begin(); it != tok.end(); ++it )
    {
        // was the last token not a group?
        if( result && !WPVBaseTypes::isPropertyGroup( result->getType() ) )
        {
            // no it wasn't. This means that one token inside the path is no group, but it needs to be one
            return std::shared_ptr< WPropertyBase >();
        }

        // get the properties along the path
        result = findProperty( curProps, string_utils::toString( *it ) );
        if( !result )
        {
            // not found? Return NULL.
            return std::shared_ptr< WPropertyBase >();
        }
        else if( result && WPVBaseTypes::isPropertyGroup( result->getType() ) )
        {
            // it is a group. Go down
            curProps = result->toPropGroupBase().get();
        }
    }

    return result;
}

void WPropertyGroupBase::visitAsString( WPropertyGroupBase::PropertyStringVisitor visitor, std::string pathPrefix ) const
{
    // read access
    PropertySharedContainerType::ReadTicket r = getReadTicket();

    for( PropertyConstIterator it = r->get().begin(); it != r->get().end(); ++it )
    {
        // path: handle some special cases:
        std::string propName = pathPrefix + WPropertyGroupBase::separator + ( *it )->getName();

        // 1: user added a separator
        if( boost::algorithm::ends_with( pathPrefix, WPropertyGroupBase::separator ) )
        {
            propName = pathPrefix + ( *it )->getName();
        }
        // 2: avoid separator if prefix is empty
        if( pathPrefix.empty() )
        {
            propName = ( *it )->getName();
        }

        // is it a group type?
        WPropertyGroupBase::SPtr g = ( *it )->toPropGroupBase();
        if( g )
        {
            // recurse down
            g->visitAsString( visitor, propName );
        }
        else
        {
            // it is a leaf, call visitor
            std::string value = ( *it )->getAsString();
            visitor( propName, value );
        }
    }
}

bool WPropertyGroupBase::existsProperty( std::string name )
{
    return ( findProperty( name ) != std::shared_ptr< WPropertyBase >() );
}

std::shared_ptr< WPropertyBase > WPropertyGroupBase::getProperty( std::string name )
{
    std::shared_ptr< WPropertyBase > p = findProperty( name );
    if( p == std::shared_ptr< WPropertyBase >() )
    {
        throw WPropertyUnknown( std::string( "Property \"" + name + "\" can't be found." ) );
    }

    return p;
}

void WPropertyGroupBase::addArbitraryProperty( WPropertyBase::SPtr prop )
{
    // lock, unlocked if l looses focus
    PropertySharedContainerType::WriteTicket l = m_properties.getWriteTicket();

    // NOTE: WPropertyBase already prohibits invalid property names -> no check needed here

    // check uniqueness:
    if( std::count_if( l->get().begin(), l->get().end(),
            boost::bind( boost::mem_fn( &WPropertyGroupBase::propNamePredicate ), this, prop, boost::placeholders::_1 ) ) )
    {
        // unlock explicitly
        l.reset();

        // oh oh, this property name is not unique in this group
        if( !getName().empty() )
        {
            throw WPropertyNotUnique( std::string( "Property \"" + prop->getName() + "\" is not unique in this group (\"" + getName() + "\")." ) );
        }
        else
        {
            throw WPropertyNotUnique( std::string( "Property \"" + prop->getName() + "\" is not unique in this group (unnamed root)." ) );
        }
    }

    // PV_PURPOSE_INFORMATION groups do not allow PV_PURPOSE_PARAMETER properties but vice versa.
    if( getPurpose() == PV_PURPOSE_INFORMATION )
    {
        prop->setPurpose( PV_PURPOSE_INFORMATION );
    }
    // INFORMATION properties are allowed inside PARAMETER groups -> do not set the properties purpose.

    l->get().push_back( prop );

    // add the child's update condition to the list
    m_updateCondition->add( prop->getUpdateCondition() );
}

WPropertyGroupBase::PropertySharedContainerType::ReadTicket WPropertyGroupBase::getProperties() const
{
    return m_properties.getReadTicket();
}

WPropertyGroupBase::PropertySharedContainerType::ReadTicket WPropertyGroupBase::getReadTicket() const
{
    return m_properties.getReadTicket();
}

bool WPropertyGroupBase::autoHideEmpty() const
{
    return m_autoHideEmpty;
}

void WPropertyGroupBase::setAutoHideEmpty( bool autoHide )
{
    m_autoHideEmpty = autoHide;
}

