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
#include <set>
#include <string>
#include <vector>

#include <boost/regex.hpp>

#include "../common/WIOTools.h"
#include "../common/WPathHelper.h"
#include "../common/WSharedLib.h"
#include "WModuleLoader.h"

WModuleLoader::WModuleLoader( )
{
    // initialize members
}

WModuleLoader::~WModuleLoader()
{
    // cleanup all the handles
    m_libs.clear();
}

void WModuleLoader::load( WSharedAssociativeContainer< std::set< std::shared_ptr< WModule > > >::WriteTicket ticket,
                          boost::filesystem::path dir, unsigned int level )
{
    for( boost::filesystem::directory_iterator i = boost::filesystem::directory_iterator( dir );
         i != boost::filesystem::directory_iterator(); ++i )
    {
        // all modules need to begin with this
        std::string stem = i->path().stem().string();

        // we want to strip the search directory from the path
        std::string relPath = i->path().string();
        relPath.erase( 0, dir.string().length() + 1 ); // NOTE: +1 because we want to remove the "/" too

        // is it a lib? Use a regular expression to check this
        // NOTE:: the double \\ is needed to escape the escape char (to interpret the "dot" as dot and not as "any char".
        #ifdef __WIN32__
            static const boost::regex CheckLibMMP( "^(lib)?(.*)\\" + WSharedLib::getSystemSuffix() +"$" );
        #elif __APPLE__
            static const boost::regex CheckLibMMP( "^(lib)?(.*)\\.[0-9]+\\.[0-9]+\\.[0-9]+\\" + WSharedLib::getSystemSuffix() + "$" );
        #else
            static const boost::regex CheckLibMMP( "^(lib)?(.*)\\" + WSharedLib::getSystemSuffix() + "\\.[0-9]+\\.[0-9]+\\.[0-9]+$" );
        #endif
        // this will contain the filename afterwards
        boost::smatch matches;
        std::string fn = i->path().filename().string();
        bool matchLibName = boost::regex_match( fn, matches, CheckLibMMP );
        std::string libBaseName = matchLibName ? std::string( matches[2] ) : "";

        if( !boost::filesystem::is_directory( *i ) &&
            matchLibName &&
            ( stem.compare( 0, getModulePrefix().length(), getModulePrefix() ) == 0 )
          )
        {
            try
            {
                // load lib
                std::shared_ptr< WSharedLib > l( new WSharedLib( i->path() ) );

                bool isLoadableModule = false;
                bool isLoadableArbitrary = false;

                // be nice. Do not fail if the module symbol does not exist
                if( l->existsFunction( W_LOADABLE_MODULE_SYMBOL ) )
                {
                    // get instantiation function
                    W_LOADABLE_MODULE_SIGNATURE f;
                    l->fetchFunction< W_LOADABLE_MODULE_SIGNATURE >( W_LOADABLE_MODULE_SYMBOL, f );

                    isLoadableModule = true;

                    // get the first prototype
                    WModuleList m;
                    f( m );

                    // could the prototype be created?
                    if( m.empty() )
                    {
                        continue;
                    }
                    else
                    {
                        // yes, add it to the list of prototypes
                        for( WModuleList::const_iterator iter = m.begin(); iter != m.end(); ++iter )
                        {
                            // which lib?
                            ( *iter )->setLibPath( i->path() );
                            // we use the library name (excluding extension and optional lib prefix) as package name
                            ( *iter )->setPackageName( libBaseName );
                            // resource path
                            ( *iter )->setLocalPath( WPathHelper::getModuleResourcePath( i->path().parent_path(), ( *iter )->getPackageName() ) );

                            // add module
                            ticket->get().insert( *iter );

                            // we need to keep a reference to the lib
                            m_libs.push_back( l );
                        }

                        wlog::debug( "Module Loader" ) << "Loaded " << m.size() << " modules from " << relPath;
                    }
                }

                // do the same for the arbitrary register functionality
                // get instantiation function
                if( l->existsFunction( W_LOADABLE_REGISTERARBITRARY_SYMBOL ) )
                {
                    isLoadableArbitrary = true;

                    // store this temporarily. This is called later, after OW was completely initialized
                    // put together the right path and call function
                    m_arbitraryRegisterLibs.push_back(
                        PostponedLoad( l, WPathHelper::getModuleResourcePath( i->path().parent_path(), libBaseName ) )
                    );
                }
                // lib gets closed if l looses focus

                if( !isLoadableModule && !isLoadableArbitrary )
                {
                    wlog::warn( "Module Loader" ) << "Library does neither contain a module nor another extension.";
                }
            }
            catch( const WException& e )
            {
                WLogger::getLogger()->addLogMessage( "Load failed for module \"" + relPath + "\". " + e.what() + ". Ignoring.",
                                                     "Module Loader", LL_ERROR );
            }
        }
        else if( ( level <= 10 ) &&  // this sould be enough to tranverse the typical structure build/release/lib/openwalnut/MODULENAME (5 levels)
                 boost::filesystem::is_directory( *i ) )     // this only traverses down one level
        {
            // if it a dir -> traverse down
            load( ticket, *i, level + 1 );
        }
    }
}

void WModuleLoader::load( WSharedAssociativeContainer< std::set< std::shared_ptr< WModule > > >::WriteTicket ticket )
{
    std::vector< boost::filesystem::path > allPaths = WPathHelper::getAllModulePaths();

    // go through each of the paths
    for( std::vector< boost::filesystem::path >::const_iterator path = allPaths.begin(); path != allPaths.end(); ++path )
    {
        WLogger::getLogger()->addLogMessage( "Searching modules in \"" + ( *path ).string() + "\".", "Module Loader", LL_INFO );

        // does the directory exist?
        if( !boost::filesystem::is_directory( *path ) || !boost::filesystem::exists( *path ) )
        {
            WLogger::getLogger()->addLogMessage( "Searching modules in \"" + ( *path ).string() +
                                                 "\" failed. It is not a directory or does not exist." +
                                                 " Ignoring.", "Module Loader", LL_WARNING );

            continue;
        }

        // directly search the path for libOWmodule_ files
        load( ticket, *path );
    }
}

void WModuleLoader::initializeExtensions()
{
    typedef std::vector< PostponedLoad > Vec;
    for( Vec::const_iterator iter = m_arbitraryRegisterLibs.begin(); iter != m_arbitraryRegisterLibs.end(); ++iter )
    {
        wlog::debug( "WModuleLoader" ) << "Initializing extensions of \"" << ( *iter ).m_lib->getLibraryName() << "\"";
        W_LOADABLE_REGISTERARBITRARY_SIGNATURE arbitraryRegister;
        ( *iter ).m_lib->fetchFunction< W_LOADABLE_REGISTERARBITRARY_SIGNATURE >( W_LOADABLE_REGISTERARBITRARY_SYMBOL, arbitraryRegister );
        arbitraryRegister( ( *iter ).m_path );
    }
}

std::string WModuleLoader::getModulePrefix()
{
    // all module file names need to have this prefix:
    return WSharedLib::getSystemPrefix();
}

