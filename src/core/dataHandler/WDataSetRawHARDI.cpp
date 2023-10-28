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

#include "../common/WAssert.h"
#include "WDataSetRawHARDI.h"
#include "WDataSetSingle.h"

// prototype instance as singleton
std::shared_ptr< WPrototyped > WDataSetRawHARDI::m_prototype = std::shared_ptr< WPrototyped >();

void WDataSetRawHARDI::init( std::shared_ptr< WValueSetBase > newValueSet,
               std::shared_ptr< WGrid > newGrid,
               std::shared_ptr< std::vector< WVector3d > > newGradients )
{
    WAssert( newValueSet, "No value set given." );
    WAssert( newGrid, "No grid given." );
    WAssert( newGradients, "No gradients given." );
    WAssert( newValueSet->size() == newGrid->size(), "Number of voxel entries unequal number of positions in grid." );
    WAssert( newValueSet->order() != newGradients->size(), "Number of gradients unequal number of entries in value set." );
    buildGradientIndexes();
}

WDataSetRawHARDI::WDataSetRawHARDI( std::shared_ptr< WValueSetBase > newValueSet,
                                    std::shared_ptr< WGrid > newGrid,
                                    std::shared_ptr< std::vector< WVector3d > > newGradients,
                                    double diffusionBValue )
    : WDataSetSingle( newValueSet, newGrid ), m_gradients( newGradients ), m_diffusionBValues( new std::vector< float >( 1, diffusionBValue ) )
{
    init( newValueSet, newGrid, newGradients );
}

WDataSetRawHARDI::WDataSetRawHARDI( std::shared_ptr< WValueSetBase > newValueSet,
                                    std::shared_ptr< WGrid > newGrid,
                                    std::shared_ptr< std::vector< WVector3d > > newGradients,
                                    std::shared_ptr< std::vector< float > > diffusionBValues )
    : WDataSetSingle( newValueSet, newGrid ), m_gradients( newGradients ), m_diffusionBValues( diffusionBValues )
{
    WAssert( diffusionBValues, "No b-values given." );
    init( newValueSet, newGrid, newGradients );
}

void WDataSetRawHARDI::buildGradientIndexes()
{
    std::vector< size_t > validIndices;
    for( size_t i = 0; i < m_gradients->size(); ++i )
    {
        const WVector3d& grad = ( *m_gradients )[ i ];
        if( ( grad[ 0 ] != 0.0 ) || ( grad[ 1 ] != 0.0 ) || ( grad[ 2 ] != 0.0 ) )
        {
            m_nonZeroGradientIndexes.push_back( i );
        }
        else
        {
            m_zeroGradientIndexes.push_back( i );
        }
    }
}

WDataSetRawHARDI::WDataSetRawHARDI()
    : WDataSetSingle()
{
}

WDataSetRawHARDI::~WDataSetRawHARDI()
{
}

WDataSetSingle::SPtr WDataSetRawHARDI::clone( std::shared_ptr< WValueSetBase > newValueSet, std::shared_ptr< WGrid > newGrid ) const
{
    return WDataSetSingle::SPtr( new WDataSetRawHARDI( newValueSet, newGrid, m_gradients, getDiffusionBValues() ) );
}

WDataSetSingle::SPtr WDataSetRawHARDI::clone( std::shared_ptr< WValueSetBase > newValueSet ) const
{
    return WDataSetSingle::SPtr( new WDataSetRawHARDI( newValueSet, getGrid(), m_gradients, getDiffusionBValues() ) );
}

WDataSetSingle::SPtr WDataSetRawHARDI::clone( std::shared_ptr< WGrid > newGrid ) const
{
    return WDataSetSingle::SPtr( new WDataSetRawHARDI( getValueSet(), newGrid, m_gradients, getDiffusionBValues() ) );
}

WDataSetSingle::SPtr WDataSetRawHARDI::clone() const
{
    return WDataSetSingle::SPtr( new WDataSetRawHARDI( getValueSet(), getGrid(), m_gradients, getDiffusionBValues() ) );
}

std::shared_ptr< WPrototyped > WDataSetRawHARDI::getPrototype()
{
    if( !m_prototype )
    {
        m_prototype = std::shared_ptr< WPrototyped >( new WDataSetRawHARDI() );
    }

    return m_prototype;
}

const WVector3d& WDataSetRawHARDI::getGradient( size_t index ) const
{
#ifdef DEBUG
  return m_gradients->at( index );
#else
  return (*m_gradients)[ index ];
#endif
}

std::shared_ptr< std::vector< WVector3d > > WDataSetRawHARDI::getOrientations() const
{
    return m_gradients;
}

double WDataSetRawHARDI::getDiffusionBValue() const
{
  WAssert( ( *m_diffusionBValues ).size() == 1, "There is more then one diffusion b-value!" );
  return ( *m_diffusionBValues )[ 0 ];
}

std::shared_ptr< std::vector< float > > WDataSetRawHARDI::getDiffusionBValues() const
{
  return m_diffusionBValues;
}

std::size_t WDataSetRawHARDI::getNumberOfMeasurements() const
{
  return m_gradients->size();
}

const std::string WDataSetRawHARDI::getName() const
{
    return "WDataSetRawHARDI";
}

const std::string WDataSetRawHARDI::getDescription() const
{
    return "Contains HARDI measurements.";
}
