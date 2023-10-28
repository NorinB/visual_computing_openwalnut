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
#include <string>
#include <vector>

#include "WBatchLoader.h"
#include "WDataModuleInputFile.h"
#include "WModule.h"
#include "WModuleContainer.h"
#include "WModuleFactory.h"

WBatchLoader::WBatchLoader( std::vector< std::string > filenames, std::shared_ptr< WModuleContainer > targetContainer ):
    WThreadedRunner(),
    std::enable_shared_from_this< WBatchLoader >(),
    m_filenamesToLoad( filenames ),
    m_targetContainer( targetContainer ),
    m_suppressColormaps( false )
{
    // initialize members
}

WBatchLoader::~WBatchLoader()
{
    // cleanup
}

void WBatchLoader::run()
{
    // the module needs to be added here, as it else could be freed before the thread finishes ( remember: it is a shared_ptr).
    m_targetContainer->addPendingThread( shared_from_this() );

    // actually run
    WThreadedRunner::run();
}

void WBatchLoader::threadMain()
{
    // add a new data module for each file to load
    for( std::vector< std::string >::iterator iter = m_filenamesToLoad.begin(); iter != m_filenamesToLoad.end(); ++iter )
    {
        // This needs to be re-thought. Refer to #32.
        // TODO(ebaum): change this to create WDataModuleInput using a matching WDataModuleInputFilter
        WDataModuleInputFile::SPtr input( new WDataModuleInputFile( *iter ) );
        std::vector< WDataModule::SPtr > dataModules = WModuleFactory::getModuleFactory()->getDataModulePrototypesByInput(
            // NOTE: right now, we only support file based inputs. Will change with issue #32
            input
        );

        if( dataModules.empty() )
        {
            wlog::warn( "WBatchLoader" ) << "File type of " << *iter << " not supported. Ignoring.";
            continue;
        }

        std::shared_ptr< WModule > mod = WModuleFactory::getModuleFactory()->create(
            dataModules[0]
        );
        WDataModule::SPtr dmod = std::static_pointer_cast< WDataModule >( mod );

        // set the input
        dmod->setSuppressColormaps( m_suppressColormaps );
        dmod->setInput( input );

        m_targetContainer->add( mod );
        dmod->isReadyOrCrashed().wait();

        // add module to the list
        m_dataModules.push_back( dmod );
    }

    m_targetContainer->finishedPendingThread( shared_from_this() );
}

WBatchLoader::DataModuleList::ReadTicket WBatchLoader::getDataModuleList() const
{
    return m_dataModules.getReadTicket();
}

void WBatchLoader::setSuppressColormaps( bool suppress )
{
    m_suppressColormaps = suppress;
}

bool WBatchLoader::getSuppressColormaps() const
{
    return m_suppressColormaps;
}

