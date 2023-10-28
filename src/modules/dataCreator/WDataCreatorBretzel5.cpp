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

#include "WDataCreatorBretzel5.h"
#include "core/common/WAssert.h"

WDataCreatorBretzel5::WDataCreatorBretzel5():
    WObjectNDIP< WDataSetSingleCreatorInterface >( "Bretzel5", "Creates a volume with some nice shape." )
{
    const double initScale = 2.34375; // Appears to be the original scale of 300 divided by this module's resolution of 128
    m_scale = m_properties->addProperty( "Scale", "Scale the value domain.", initScale );
    m_scale->setMin( 0.0 );
    m_scale->setMax( 10 );
}

WDataCreatorBretzel5::~WDataCreatorBretzel5()
{
}

WValueSetBase::SPtr WDataCreatorBretzel5::operator()( WProgress::SPtr progress,
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

    // iterate the data and fill in some values
    double xRel = 0.0;
    double yRel = 0.0;
    double zRel = 0.0;
    double scale = m_scale->get();
    for( size_t x = 0; x < grid->getNbCoordsX(); ++x )
    {
        xRel = static_cast< double >( x ) / static_cast< double >( grid->getNbCoordsX() - 1 );
        xRel -= 0.5;
        xRel *= scale * 2.0;

        for( size_t y = 0; y < grid->getNbCoordsY(); ++y )
        {
            yRel = static_cast< double >( y ) / static_cast< double >( grid->getNbCoordsY() - 1 );
            yRel -= 0.5;
            yRel *= scale * 2.0;

            for( size_t z = 0; z < grid->getNbCoordsZ(); ++z )
            {
                zRel = static_cast< double >( z ) / static_cast< double >( grid->getNbCoordsZ() - 1 );
                zRel -= 0.5;
                zRel *= scale * 2.0;

                double x2 = xRel * xRel;
                double y2 = yRel * yRel;
                double z2 = zRel * zRel;
                double s = ( x2 + 0.25 * y2 - 1.0 ) * ( 0.25 * x2 + y2 - 1.0 );
                data->operator[]( grid->getVoxelNum( x, y, z ) ) = static_cast< ValueType >( s * s + z2 - 0.1 );
            }

            // updating progress for each voxel is not needed. It is enough to update each slice
            progress->increment( grid->getNbCoordsZ() );
        }
    }

    // finally, create the value set and return it
    // We have scalar data (order = 0 ) in 3d
    return ValueSetType::SPtr( new ValueSetType( 0, 1, data ) );
}
