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

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

#include <boost/variant.hpp>

#include "WMVectorNormalize.h"
#include "core/common/WAssert.h"
#include "core/common/WProgress.h"
#include "core/common/WStringUtils.h"
#include "core/common/WTypeTraits.h"
#include "core/common/exceptions/WTypeMismatch.h"
#include "core/dataHandler/WDataHandler.h"
#include "core/dataHandler/WDataHandlerEnums.h"
#include "core/dataHandler/WGridRegular3D.h"
#include "core/dataHandler/exceptions/WDHValueSetMismatch.h"
#include "core/kernel/WKernel.h"

// This line is needed by the module loader to actually find your module.
W_LOADABLE_MODULE( WMVectorNormalize )

WMVectorNormalize::WMVectorNormalize() :
    WModule()
{
    // initialize
}

WMVectorNormalize::~WMVectorNormalize()
{
    // cleanup
    removeConnectors();
}

std::shared_ptr< WModule > WMVectorNormalize::factory() const
{
    return std::shared_ptr< WModule >( new WMVectorNormalize() );
}

const std::string WMVectorNormalize::getName() const
{
    return "Vector Normalize";
}

const std::string WMVectorNormalize::getDescription() const
{
    return "Normalize a vector field.";
}

void WMVectorNormalize::connectors()
{
    m_inputA = WModuleInputData< WDataSetVector >::createAndAdd( shared_from_this(), "input", "Input vectors." );

    m_output = WModuleOutputData< WDataSetVector >::createAndAdd( shared_from_this(), "normalized", "Normalized input." );

    // call WModules initialization
    WModule::connectors();
}

void WMVectorNormalize::properties()
{
    m_propCondition = std::shared_ptr< WCondition >( new WCondition() );

    m_zeroTol = m_properties->addProperty( "Zero Tolerance", "Vector lengths smaller than this are assumed as being 0.", 0.000001, m_propCondition );
    m_zeroTol->setMin( 0.0 );
    m_zeroTol->setMax( 1.0 );

    WModule::properties();
}

WMVectorNormalize::VisitorVSetA::VisitorVSetA( double zeroTol ):
    boost::static_visitor< result_type >(),
    m_zeroTol( zeroTol )
{
}

/**
 * Called by boost::varying during static visiting.
 *
 * \tparam T the real integral type of the first value set.
 * \param vsetA the first valueset currently visited.
 *
 * \return the result from the operation
 */
template < typename T >
boost::static_visitor< std::shared_ptr< WValueSetBase > >::result_type WMVectorNormalize::VisitorVSetA::operator()(
    const WValueSet< T >* const& vsetA ) const             // NOLINT
{
    // get some info
    std::vector< T > data;
    data.resize( vsetA->rawSize() );

    // apply op to each value
    // iterate field
    for( size_t i = 0; i < vsetA->size(); ++i )
    {
        // to avoid cascading numeric errors due to T being a low resolution type, we use doubles during calculation
        double x = vsetA->getScalar( ( i * 3 ) + 0 );
        double y = vsetA->getScalar( ( i * 3 ) + 1 );
        double z = vsetA->getScalar( ( i * 3 ) + 2 );

        double len = sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
        if( len < m_zeroTol )
        {
            data[ ( i * 3 ) + 0 ] = 0;
            data[ ( i * 3 ) + 1 ] = 0;
            data[ ( i * 3 ) + 2 ] = 0;

            continue;
        }

        data[ ( i * 3 ) + 0 ] = static_cast< T >( x / len );
        data[ ( i * 3 ) + 1 ] = static_cast< T >( y / len );
        data[ ( i * 3 ) + 2 ] = static_cast< T >( z / len );
    }

    // create result value set
    return std::shared_ptr< WValueSet< T > >( new WValueSet< T >( 1,
                                                                    3,
                                                                    std::shared_ptr< std::vector< T > >(
                                                                        new std::vector< T >( data ) ),
                                                                    DataType< T >::type ) );
}

void WMVectorNormalize::moduleMain()
{
    // let the main loop awake if the data changes or the properties changed.
    m_moduleState.setResetable( true, true );
    m_moduleState.add( m_inputA->getDataChangedCondition() );
    m_moduleState.add( m_propCondition );

    // signal ready state
    ready();

    // loop until the module container requests the module to quit
    while( !m_shutdownFlag() )
    {
        // Now, the moduleState variable comes into play. The module can wait for the condition, which gets fired whenever the input receives data
        // or an property changes. The main loop now waits until something happens.
        debugLog() << "Waiting ...";
        m_moduleState.wait();

        // woke up since the module is requested to finish
        if( m_shutdownFlag() )
        {
            break;
        }

        // has the data changed?
        if( m_zeroTol->changed() || m_inputA->handledUpdate() )
        {
            std::shared_ptr< WDataSetVector > dataSetA = m_inputA->getData();

            // valid data?
            if( dataSetA )
            {
                std::shared_ptr< WValueSetBase > valueSetA = dataSetA->getValueSet();

                // use a custom progress combiner
                std::shared_ptr< WProgress > prog = std::shared_ptr< WProgress >(
                    new WProgress( "Applying operator on data" ) );
                m_progress->addSubProgress( prog );

                // apply the operation to each voxel
                debugLog() << "Processing ...";
                std::shared_ptr< WValueSetBase > newValueSet = valueSetA->applyFunction( VisitorVSetA( m_zeroTol->get( true ) ) );

                // Create the new dataset and export it
                m_output->updateData( std::shared_ptr<WDataSetVector>( new WDataSetVector( newValueSet, m_inputA->getData()->getGrid() ) ) );

                // done
                prog->finish();
                m_progress->removeSubProgress( prog );
            }
            else
            {
                debugLog() << "Resetting output.";
                m_output->reset();
            }
        }
    }
}

