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

#include "WDataSetMatrix.h"

// prototype instance as singleton
std::shared_ptr< WPrototyped > WDataSetMatrix::m_prototype = std::shared_ptr< WPrototyped >();


WDataSetMatrix::WDataSetMatrix()
    : WDataSetSingle()
{
    // default constructor used by the prototype mechanism
}

WDataSetMatrix::WDataSetMatrix( std::shared_ptr< WValueSetBase > newValueSet, std::shared_ptr< WGrid > newGrid, size_t nbRows, size_t nbColumns )
    : WDataSetSingle( newValueSet, newGrid )
{
    WAssert( newValueSet, "No value set given." );
    WAssert( newGrid, "No grid given." );
    WAssert( newValueSet->size() == newGrid->size(), "Number of values unequal number of positions in grid." );
    WAssert( newValueSet->order() == 1, "The value set does not contain vectors." );
    rows = nbRows;
    columns = nbColumns;
}

WDataSetMatrix::~WDataSetMatrix()
{
}

WDataSetSingle::SPtr WDataSetMatrix::clone( std::shared_ptr< WValueSetBase > newValueSet ) const
{
    return WDataSetSingle::SPtr( new WDataSetMatrix( newValueSet, getGrid(), rows, columns ) );
}

WDataSetSingle::SPtr WDataSetMatrix::clone( std::shared_ptr< WGrid > newGrid ) const
{
    return WDataSetSingle::SPtr( new WDataSetMatrix( getValueSet(), newGrid, rows, columns ) );
}

WDataSetSingle::SPtr WDataSetMatrix::clone() const
{
    return WDataSetSingle::SPtr( new WDataSetMatrix( getValueSet(), getGrid(), rows, columns ) );
}

WMatrix< double > WDataSetMatrix::getMatrixDouble( size_t index ) const
{
    std::shared_ptr< WValueSet< double > > values = std::dynamic_pointer_cast< WValueSet< double > >( m_valueSet );
    WAssert( values, "The value set of a WDataSetMatrix must be a WValueSet< double >, nothing else!" );
    int d = rows * columns;
    WMatrix< double > m( rows, columns );
    if( ( index + 1 ) * d > values->rawSize() )
    {
        wlog::debug( "Size exceeds Array. Array Size: " + std::to_string( values->rawSize() ) );
        wlog::debug( "Wanted: " + std::to_string( ( index + 1 ) * d ) );
        wlog::debug( "For index " + std::to_string( index ) );
    }
    WValueSet< double >::SubArray sa = values->getSubArray( index * d, d );
    for( int i = 0; i < d; i++ )
    {
        m[i] = sa[i];
    }
    return m;
}


const std::string WDataSetMatrix::getName() const
{
    return "WDataSetMatrix";
}

const std::string WDataSetMatrix::getDescription() const
{
    return "Contains matrices.";
}

std::shared_ptr< WPrototyped > WDataSetMatrix::getPrototype()
{
    if( !m_prototype )
    {
        m_prototype = std::shared_ptr< WPrototyped >( new WDataSetMatrix() );
    }

    return m_prototype;
}
