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
#include <vector>


#include "../common/math/linearAlgebra/WPosition.h"
#include "WTractAdapter.h"

WTractAdapter::WTractAdapter( std::shared_ptr< const std::vector< float > > pointComponents, size_t startIndex, size_t numPoints )
    : m_pointComponents( pointComponents ),
      m_numPoints( numPoints ),
      m_startIndex( startIndex )
{
}

WPosition WTractAdapter::operator[]( size_t index ) const
{
#ifdef DEBUG
    assert( m_pointComponents && "Invalid point component array inside of WTractAdapter." );
    return WPosition( m_pointComponents->at( m_startIndex + index * 3 ),
                             m_pointComponents->at( m_startIndex + index * 3 + 1 ),
                             m_pointComponents->at( m_startIndex + index * 3 + 2 ) );
#else
    return WPosition( ( *m_pointComponents )[ m_startIndex + index * 3],
                             ( *m_pointComponents )[ m_startIndex + index * 3 + 1],
                             ( *m_pointComponents )[ m_startIndex + index * 3 + 2] );
#endif
}
