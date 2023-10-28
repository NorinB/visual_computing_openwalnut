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

#include "WDataCreatorSphere.h"
#include "core/common/WAssert.h"
#include "core/common/WLimits.h"

WDataCreatorSphere::WDataCreatorSphere():
    WObjectNDIP< WDataSetSingleCreatorInterface >( "Spherical", "Creates a spherical volume." )
{
    // add some properties
    m_center = m_properties->addProperty( "Center", "The center point in relative coordinates, where 0.5 is the center. At this point, "
                                                    "the value in the scalar field will be zero.",
                                          WPosition( 0.5, 0.5, 0.5 ) );
    m_radius = m_properties->addProperty( "Radius", "The radius in relative coordinates, where 0.5 creates a sphere in the size of the grid.",
                                          0.5 );
    m_radius->setMin( 0.0 );

    m_lowerClamp = m_properties->addProperty( "Lower Clamp Threshold", "Defines a threshold which allows all values below this value to be set to 0."
                                              "This can be handy to create spheres which are 0 in the inside.",
                                              0.0 );
    m_lowerClamp->setMin( 0.0 );
    m_upperClamp = m_properties->addProperty( "Upper Clamp Threshold", "Defines a threshold which allows all values above this value to be set to 0."
                                              "This can be handy to create an empty field around the sphere",
                                              wlimits::MAX_DOUBLE );
    m_upperClamp->setMin( 0.0 );

    m_lowerClampValue = m_properties->addProperty( "Lower Clamp Value", "Value to use when below lower clamp threshold.", 0.0 );
    m_upperClampValue = m_properties->addProperty( "Upper Clamp Value", "Value to use when above upper clamp threshold.", 0.0 );
}

WDataCreatorSphere::~WDataCreatorSphere()
{
}

WValueSetBase::SPtr WDataCreatorSphere::operator()( WProgress::SPtr progress,
                                                    WGridRegular3D::ConstSPtr grid, unsigned char order, unsigned char dimension,
                                                    dataType /*type*/ )
{
    // this creator only supports valuesets for scalar data.
    WAssert( ( order == 0 ) && ( dimension == 1 ), "The sphere data creator only supports scalar data." );

    // currently, the type is fixed. This will come soon.
    typedef double ValueType;
    typedef WValueSet< ValueType > ValueSetType;

    // create some memory for the data
    std::shared_ptr< std::vector< ValueType > > data( new std::vector< ValueType > );
    // for scalar data we need only as much space as we have voxels
    data->resize( grid->size() );

    double originX = m_center->get().x();
    double originY = m_center->get().y();
    double originZ = m_center->get().z();

    // the formular below calculates the stuff in -1,1 interval. The radius is meant to be used in -0.5 to 0.5 -> so scale up
    double radius = 2.0 * m_radius->get();

    // clamp info
    double lowClamp = m_lowerClamp->get();
    double upClamp = m_upperClamp->get();
    double upClampValue = m_upperClampValue->get();
    double lowClampValue = m_lowerClampValue->get();

    // iterate the data and fill in some values
    double xRel = 0.0;
    double yRel = 0.0;
    double zRel = 0.0;
    for( size_t x = 0; x < grid->getNbCoordsX(); ++x )
    {
        xRel = static_cast< double >( x ) / static_cast< double >( grid->getNbCoordsX() - 1 );
        xRel -= originX;
        xRel *= 2.0;

        for( size_t y = 0; y < grid->getNbCoordsY(); ++y )
        {
            yRel = static_cast< double >( y ) / static_cast< double >( grid->getNbCoordsY() - 1 );
            yRel -= originY;
            yRel *= 2.0;

            for( size_t z = 0; z < grid->getNbCoordsZ(); ++z )
            {
                zRel = static_cast< double >( z ) / static_cast< double >( grid->getNbCoordsZ() - 1 );
                zRel -= originZ;
                zRel *= 2.0;

                ValueType val = static_cast< ValueType >( ( 1.0 / ( radius * radius ) ) *
                                                                                          ( ( xRel * xRel ) +
                                                                                            ( yRel * yRel ) +
                                                                                            ( zRel * zRel ) ) );

                // set value
                data->operator[]( grid->getVoxelNum( x, y, z ) ) = val < lowClamp ? lowClampValue : ( val > upClamp ? upClampValue : val );
            }

            // updating progress for each voxel is not needed. It is enough to update each slice
            progress->increment( grid->getNbCoordsZ() );
        }
    }

    // finally, create the value set and return it
    // We have scalar data (order = 0 ) in 3d
    return ValueSetType::SPtr( new ValueSetType( 0, 1, data ) );
}
