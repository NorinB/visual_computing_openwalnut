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

#include "WDataCreatorTwoBlobs.h"
#include "core/common/WAssert.h"

WDataCreatorTwoBlobs::WDataCreatorTwoBlobs():
    WObjectNDIP< WDataSetSingleCreatorInterface >( "Two Blobs", "Creates a volume containing two blobs." )
{
    m_center = m_properties->addProperty( "Center",
                                          "The center point between the two blobs.",
                                          WPosition( 64.0, 64.0, 64.0 ) ); //Initial value according to the module's typical size of 128
    m_radius = m_properties->addProperty( "Scale",
                                          "Scaling the shape of the volume to for the size of the grid.",
                                          32.0 ); //Initial value according to the module's typical size of 128
    m_radius->setMin( 0.0 );
}

WDataCreatorTwoBlobs::~WDataCreatorTwoBlobs()
{
}

WValueSetBase::SPtr WDataCreatorTwoBlobs::operator()( WProgress::SPtr progress,
                                                      WGridRegular3D::ConstSPtr grid, unsigned char order, unsigned char dimension,
                                                      dataType /*type*/ )
{
    // this creator only supports valuesets for scalar data.
    WAssert( ( order == 0 ) && ( dimension == 1 ), "The data creator only supports scalar data." );

    // currently, the type is fixed. This will come soon.
    typedef double ValueType;
    typedef WValueSet< ValueType > ValueSetType;

    // create some memory for the data
    std::shared_ptr< std::vector< ValueType > > data( new std::vector< ValueType > );
    // for scalar data we need only as much space as we have voxels
    data->resize( grid->size() );

    const WVector3d p = ( WVector3d( -1, 0, 0 ) ) * m_radius->get();
    const WVector3d q = ( WVector3d(  1, 0, 0 ) ) * m_radius->get();

    // iterate the data
    for( size_t x = 0; x < grid->getNbCoordsX(); ++x )
    {
        for( size_t y = 0; y < grid->getNbCoordsY(); ++y )
        {
            for( size_t z = 0; z < grid->getNbCoordsZ(); ++z )
            {
                const WVector3d s = ( grid->getPosition( x, y, z ) - m_center->get() );
                data->operator[]( grid->getVoxelNum( x, y, z ) ) = static_cast< ValueType >( distance( p, s ) * distance( q, s ) );
            }

            // updating progress for each voxel is not needed. It is enough to update each slice
            progress->increment( grid->getNbCoordsZ() );
        }
    }

    // finally, create the value set and return it
    // We have scalar data (order = 0 ) in 3d
    return ValueSetType::SPtr( new ValueSetType( 0, 1, data ) );
}
