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
#include <memory>
#include <string>
#include <vector>

#include "../common/WLogger.h"
#include "../common/WStringUtils.h"
#include "WDataHandler.h"
#include "WSubject.h"
#include "exceptions/WDHNoSuchSubject.h"

// instance as singleton
std::shared_ptr< WDataHandler > WDataHandler::m_instance = std::shared_ptr< WDataHandler >();

WDataHandler::WDataHandler():
    m_subjects()
{
    WLogger::getLogger()->addLogMessage( "Initializing Data Handler", "Data Handler", LL_INFO );
    addSubject( std::shared_ptr< WSubject >( new WSubject( WPersonalInformation::createDummyInformation() ) ) );
}

WDataHandler::~WDataHandler()
{
}

void WDataHandler::addSubject( std::shared_ptr< WSubject > subject )
{
    WLogger::getLogger()->addLogMessage( "Adding subject with ID \"" +
                                         string_utils::toString( subject->getPersonalInformation().getSubjectID() ) + "\" and Name \""
                                         + subject->getName() + "\".",
                                         "Data Handler", LL_DEBUG );

    // simply add the new subject
    m_subjects.push_back( subject );
}

void WDataHandler::removeSubject( std::shared_ptr< WSubject > subject )
{
    SubjectSharedContainerType::WriteTicket l = m_subjects.getWriteTicket();

    WLogger::getLogger()->addLogMessage( "Removing subject with ID \"" +
                                         string_utils::toString( subject->getPersonalInformation().getSubjectID() ) + "\" and Name \""
                                         + subject->getName() + "\".",
                                         "Data Handler", LL_DEBUG );

    // iterate and find, remove
    for( SubjectContainerType::iterator iter = l->get().begin(); iter != l->get().end();
            ++iter )
    {
        if( ( *iter ) ==  subject )
        {
            l->get().erase( iter );
            break;
        }
    }
}

void WDataHandler::clear()
{
    SubjectSharedContainerType::WriteTicket l = m_subjects.getWriteTicket();

    WLogger::getLogger()->addLogMessage( "Removing all subjects.", "Data Handler", LL_INFO );

    for( SubjectContainerType::const_iterator iter = l->get().begin(); iter != l->get().end();
            ++iter )
    {
        WLogger::getLogger()->addLogMessage( "Removing subject \"" +
                string_utils::toString( ( *iter )->getPersonalInformation().getSubjectID() ) + "\".",
                "Data Handler", LL_DEBUG );

        ( *iter )->clear();
    }

    l->get().clear();
}

WDataHandler::SubjectSharedContainerType::ReadTicket WDataHandler::getSubjects() const
{
    return m_subjects.getReadTicket();
}

std::shared_ptr< WSubject > WDataHandler::getSubjectByID( size_t subjectID )
{
    SubjectSharedContainerType::ReadTicket l = m_subjects.getReadTicket();

    // search it
    std::shared_ptr< WSubject > result;
    try
    {
        if( subjectID < l->get().size() )
        {
            result = l->get().at( subjectID );
        }
        else
        {
            result = std::shared_ptr< WSubject >();
        }
    }
    catch( const std::out_of_range& e )
    {
        throw WDHNoSuchSubject();
    }

    return result;
}

std::shared_ptr< WDataHandler > WDataHandler::getDataHandler()
{
    if( !m_instance )
    {
        m_instance = std::shared_ptr< WDataHandler >( new WDataHandler() );
    }

    return m_instance;
}

std::shared_ptr< WSubject > WDataHandler::getDefaultSubject()
{
    return getDataHandler()->getSubjectByID( WSubject::SUBJECT_UNKNOWN );
}

