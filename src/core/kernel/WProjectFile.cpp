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
#include <fstream>
#include <iterator>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include <boost/regex.hpp>

#include "../common/WStringUtils.h"
#include "../common/exceptions/WFileNotFound.h"
#include "../common/exceptions/WFileOpenFailed.h"
#include "../graphicsEngine/WGEProjectFileIO.h"
#include "WKernel.h"
#include "WModule.h"
#include "WProjectFile.h"
#include "WRoiProjectFileIO.h"
#include "combiner/WModuleProjectFileCombiner.h"

WProjectFile::ParserList WProjectFile::m_additionalParsers;

WProjectFile::WProjectFile( boost::filesystem::path project ):
    WThreadedRunner(),
    std::enable_shared_from_this< WProjectFile >(),
    m_project( project )
{
    // initialize members
    std::shared_ptr< WProjectFileIO > p1( new WModuleProjectFileCombiner() );
    std::shared_ptr< WProjectFileIO > p2( new WRoiProjectFileIO() );
    std::shared_ptr< WProjectFileIO > p3( new WGEProjectFileIO() );

    // The module graph parser
    m_moduleIO = std::dynamic_pointer_cast< WModuleProjectFileCombiner >( p1->clone( this ) );
    m_parsers.push_back( m_moduleIO );
    m_writers.push_back( m_moduleIO );

    // The ROI parser
    m_parsers.push_back( p2->clone( this ) );
    m_writers.push_back( p2->clone( this ) );

    // The Camera parser
    m_parsers.push_back( p3->clone( this ) );
    m_writers.push_back( p3->clone( this ) );

    // add the current list of additional parsers
    ParserList::ReadTicket r = m_additionalParsers.getReadTicket();

    // Grab all items and add to my own list of parsers
    for( ParserList::ConstIterator it = r->get().begin(); it != r->get().end(); ++it )
    {
        if( ( *it )->getApplyOrder() == WProjectFileIO::POST_MODULES )
        {
            m_parsers.push_back( ( *it )->clone( this ) );
        }
        else
        {
            m_parsers.push_front( ( *it )->clone( this ) );
        }

        // always add savers behind the module saver, to allow the module saver build the id map
        m_writers.push_back( ( *it )->clone( this )  );
    }

    // ticket unlocked automatically upon its destruction
}

WProjectFile::WProjectFile( boost::filesystem::path project, ProjectLoadCallback doneCallback ):
    WThreadedRunner(),
    std::enable_shared_from_this< WProjectFile >(),
    m_project( project ),
    m_signalLoadDoneConnection( m_signalLoadDone.connect( doneCallback ) )
{
    // initialize members
    std::shared_ptr< WProjectFileIO > p1( new WModuleProjectFileCombiner() );
    std::shared_ptr< WProjectFileIO > p2( new WRoiProjectFileIO() );
    std::shared_ptr< WProjectFileIO > p3( new WGEProjectFileIO() );

    // The module graph parser
    m_moduleIO = std::dynamic_pointer_cast< WModuleProjectFileCombiner >( p1->clone( this ) );
    m_parsers.push_back( m_moduleIO );
    m_writers.push_back( m_moduleIO );

    // The ROI parser
    m_parsers.push_back( p2->clone( this ) );
    m_writers.push_back( p2->clone( this ) );

    // The Camera parser
    m_parsers.push_back( p3->clone( this ) );
    m_writers.push_back( p3->clone( this ) );

    // add the current list of additional parsers
    ParserList::ReadTicket r = m_additionalParsers.getReadTicket();

    // Grab all items and add to my own list of parsers
    for( ParserList::ConstIterator it = r->get().begin(); it != r->get().end(); ++it )
    {
        if( ( *it )->getApplyOrder() == WProjectFileIO::POST_MODULES )
        {
            m_parsers.push_back( ( *it )->clone( this ) );
        }
        else
        {
            m_parsers.push_front( ( *it )->clone( this ) );
        }

        // always add savers behind the module saver, to allow the module saver build the id map
        m_writers.push_back( ( *it )->clone( this )  );
    }

    // ticket unlocked automatically upon its destruction
}

WProjectFile::~WProjectFile()
{
    // cleanup
    m_parsers.clear();
    m_writers.clear();
    m_signalLoadDoneConnection.disconnect();
}

std::shared_ptr< WProjectFileIO > WProjectFile::getCameraWriter()
{
    return std::shared_ptr< WProjectFileIO >( new WGEProjectFileIO() );
}

std::shared_ptr< WProjectFileIO > WProjectFile::getModuleWriter()
{
    return std::shared_ptr< WProjectFileIO >( new WModuleProjectFileCombiner() );
}

std::shared_ptr< WProjectFileIO > WProjectFile::getROIWriter()
{
    return std::shared_ptr< WProjectFileIO >( new WRoiProjectFileIO() );
}

void WProjectFile::load()
{
    // the instance needs to be added here, as it else could be freed before the thread finishes ( remember: it is a shared_ptr ).
    WKernel::getRunningKernel()->getRootContainer()->addPendingThread( shared_from_this() );

    // actually run
    run();
}

void WProjectFile::save( const std::vector< std::shared_ptr< WProjectFileIO > >& writer )
{
    std::list< std::shared_ptr< WProjectFileIO > > l( writer.begin(), writer.end() );
    save( l );
}

void WProjectFile::save( const std::list< std::shared_ptr< WProjectFileIO > >& writer )
{
    wlog::info( "Project File" ) << "Saving project file \"" << m_project.string() << "\".";

    // open the file for write
    std::ofstream output( m_project.string().c_str() );
    if( !output.is_open() )
    {
        throw WFileOpenFailed( std::string( "The project file \"" ) + m_project.string() +
                               std::string( "\" could not be opened for write access." ) );
    }

    // allow each parser to handle save request
    for( std::list< std::shared_ptr< WProjectFileIO > >::const_iterator iter = writer.begin(); iter != writer.end(); ++iter )
    {
        ( *iter )->save( output );
        output << std::endl;
    }

    output.close();
}

void WProjectFile::save()
{
    save( m_writers );
}

void WProjectFile::threadMain()
{
    // Parse the file
    wlog::info( "Project File" ) << "Loading project file \"" << m_project.string() << "\".";

    // store some errors and warnings
    std::vector< std::string > errors;
    std::vector< std::string > warnings;

    // read the file
    std::ifstream input( m_project.string().c_str() );
    if( !input.is_open() )
    {
        errors.push_back( std::string( "The project file \"" ) + m_project.string() + std::string( "\" does not exist." ) );

        // give some feedback
        m_signalLoadDone( m_project, errors, warnings );
        m_signalLoadDoneConnection.disconnect();

        // also throw an exception
        throw WFileNotFound( *errors.begin() );
    }

    // the comment
    static const boost::regex commentRe( "^ *//.*$" );

    // read it line by line
    std::string line;       // the current line
    int i = 0;              // line counter
    bool match = false;     // true of a parser successfully parsed the line
    boost::smatch matches;  // the list of matches

    while( std::getline( input, line ) )
    {
        ++i;    // line number
        match = false;

        // allow each parser to handle the line.
        for( std::list< std::shared_ptr< WProjectFileIO > >::const_iterator iter = m_parsers.begin(); iter != m_parsers.end(); ++iter )
        {
            try
            {
                if( ( *iter )->parse( line, i ) )
                {
                    match = true;
                    // the first parser matching this line -> next line
                    break;
                }
            }
            catch( const std::exception& e )
            {
                errors.push_back( "Parse error on line " + string_utils::toString( i ) + ": " + e.what() );
                wlog::error( "Project Loader" ) << errors.back();
            }
        }

        // did someone match this line? Or is it empty or a comment?
        if( !match && !line.empty() && !boost::regex_match( line, matches, commentRe ) )
        {
            // no it is something else -> warning! Not a critical error.
            wlog::warn( "Project Loader" ) << "Line " << i << ": Malformed. Skipping.";
        }
    }

    input.close();

    // finally, let every one know that we have finished
    for( std::list< std::shared_ptr< WProjectFileIO > >::const_iterator iter = m_parsers.begin(); iter != m_parsers.end(); ++iter )
    {
        try
        {
            ( *iter )->done();
            // append errors and warnings
            std::copy( ( *iter )->getErrors().begin(), ( *iter )->getErrors().end(), std::back_inserter( errors ) );
            std::copy( ( *iter )->getWarnings().begin(), ( *iter )->getWarnings().end(), std::back_inserter( warnings ) );
        }
        catch( const std::exception& e )
        {
            errors.push_back( "Exception while applying settings: " + std::string( e.what() ) );
            wlog::error( "Project Loader" ) << errors.back();
        }
    }

    // give some feedback
    m_signalLoadDone( m_project, errors, warnings );
    m_signalLoadDoneConnection.disconnect();

    // remove from thread list
    WKernel::getRunningKernel()->getRootContainer()->finishedPendingThread( shared_from_this() );
}

void WProjectFile::onThreadException( const WException& e )
{
    // let WThreadedRunner do the remaining tasks.
    handleDeadlyException( e, "Project Loader" );

    // remove from thread list. Please note: this NEEDS to be done after handleDeadlyException - if done before, the thread pointer might be
    // deleted already.
    WKernel::getRunningKernel()->getRootContainer()->finishedPendingThread( shared_from_this() );
}

void WProjectFile::registerParser( WProjectFileIO::SPtr parser )
{
    ParserList::WriteTicket w = m_additionalParsers.getWriteTicket();

    // find item if still inside
    ParserList::Iterator it = std::find( w->get().begin(), w->get().end(), parser );
    // item not inside? Add!
    if( it == w->get().end() )
    {
        // add
        w->get().push_back( parser );
    }
    // ticket unlocked automatically upon its destruction
}

void WProjectFile::deregisterParser( WProjectFileIO::SPtr parser )
{
    m_additionalParsers.remove( parser );
}

std::shared_ptr< WModule > WProjectFile::mapToModule( unsigned int id ) const
{
    return m_moduleIO->mapToModule( id );
}

unsigned int WProjectFile::mapFromModule(  std::shared_ptr< WModule > module ) const
{
    return m_moduleIO->mapFromModule( module );
}

