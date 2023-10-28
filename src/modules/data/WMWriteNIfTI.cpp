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
#include <utility>
#include <vector>

#include <nifti1_io.h> // NOLINT: brainlint thinks this is C System Header

#include "WMWriteNIfTI.h"
#include "core/common/WAssert.h"
#include "core/common/WPathHelper.h"
#include "core/common/WStringUtils.h"
#include "core/dataHandler/WDataSetRawHARDI.h"
#include "core/dataHandler/WGridRegular3D.h"
#include "core/kernel/WKernel.h"
#include "core/kernel/WModule.h"

WMWriteNIfTI::WMWriteNIfTI() :
    WModule()
{
    // WARNING: initializing connectors inside the constructor will lead to an exception.
    // Implement WModule::initializeConnectors instead.
}

WMWriteNIfTI::~WMWriteNIfTI()
{
    // cleanup
    removeConnectors();
}

std::shared_ptr< WModule > WMWriteNIfTI::factory() const
{
    return std::shared_ptr< WModule >( new WMWriteNIfTI() );
}

const std::string WMWriteNIfTI::getName() const
{
    return "Write NIfTI";
}

const std::string WMWriteNIfTI::getDescription() const
{
    return ""; // See META file
}

void WMWriteNIfTI::moduleMain()
{
    // use the m_input "data changed" flag
    m_moduleState.setResetable( true, true );
    m_moduleState.add( m_input->getDataChangedCondition() );
    m_moduleState.add( m_saveTriggerProp->getCondition() );

    // signal ready state
    ready();

    // loop until the module container requests the module to quit
    while( !m_shutdownFlag() )
    {
        debugLog() << "Waiting for data ...";

        m_moduleState.wait();

        // acquire data from the input connector
        m_dataSet = m_input->getData();
        if( !m_dataSet )
        {
            continue;
        }
        if( m_saveTriggerProp->get( true ) == WPVBaseTypes::PV_TRIGGER_TRIGGERED )
        {
            writeToFile();
            m_saveTriggerProp->set( WPVBaseTypes::PV_TRIGGER_READY, false ); // reset button to save again
        }
    }
}

void WMWriteNIfTI::connectors()
{
    m_input = WModuleInputData< WDataSetSingle >::createAndAdd( shared_from_this(), "in", "The dataset to filter" );

    WModule::connectors();
}

void WMWriteNIfTI::properties()
{
    m_filename = m_properties->addProperty( "Filename", "Filename where to write the NIfTI file to.", WPathHelper::getAppPath() );
    m_saveTriggerProp = m_properties->addProperty( "Do save",  "Press!", WPVBaseTypes::PV_TRIGGER_READY );

    WModule::properties();
}

template< typename T > void WMWriteNIfTI::castData( void*& returnData )
{
    // cast valueset
    std::shared_ptr< WValueSetBase > valsB = ( *m_dataSet ).getValueSet();
    std::shared_ptr< WValueSet< T > > vals = std::dynamic_pointer_cast< WValueSet< T > >( ( *m_dataSet ).getValueSet() );
    WAssert( vals, "Seems that value set type is not yet supported." );
    const size_t vDim = vals->dimension();
    // cast grid
    std::shared_ptr< WGridRegular3D > grid = std::dynamic_pointer_cast< WGridRegular3D >( m_dataSet->getGrid() );
    const size_t countVoxels = grid->getNbCoordsX() * grid->getNbCoordsY() * grid->getNbCoordsZ();
    WAssert( grid, "Seems that grid is of wrong type." );

    // copy data
    T* data = new T[vals->rawSize()];
    for( size_t i = 0; i < countVoxels; ++i )
    {
        for( size_t j = 0; j < vDim; ++j )
        {
            data[( j * countVoxels ) + i] = static_cast< T > ( vals->getScalar( i * vDim + j ) );
        }
    }
    returnData = static_cast< void* > ( data );
}

void WMWriteNIfTI::writeToFile()
{
    infoLog() << "Writing Data to " << m_filename->get().string();
    nifti_image *outField = nifti_simple_init_nim();

    std::shared_ptr< WGridRegular3D > grid = std::dynamic_pointer_cast< WGridRegular3D >( m_dataSet->getGrid() );
    WAssert( grid, "Seems that grid is of wrong type." );

    size_t nbValues = ( *m_dataSet ).getValueSet()->size();

    outField->nx = grid->getNbCoordsX();
    outField->ny = grid->getNbCoordsY();
    outField->nz = grid->getNbCoordsZ();
    WAssert( grid->getNbCoordsX() * grid->getNbCoordsY() * grid->getNbCoordsZ() == nbValues,
             "Overall size incompatible with size in axis directions." );

    outField->nvox = nbValues*m_dataSet->getValueSet()->dimension();

    outField->dx = grid->getOffsetX();
    outField->dy = grid->getOffsetY();
    outField->dz = grid->getOffsetZ();

    outField->nifti_type = 1; // 1==NIFTI-1 (1 file)

    outField->freq_dim = 1;
    outField->phase_dim = 2;
    outField->slice_dim = 3;

    outField->qform_code = 1;
    outField->sform_code = 1;

    // TODO(philips): solve ticket 334
    // set time dimension to 1
    // wrong, according to nifti specs
    outField->nt = m_dataSet->getValueSet()->dimension();
    outField->dim[0] = 4;
    // right, according to nifti specs

    // wrong, according to nifti specs
    outField->ndim = 4;
    // right, according to nifti specs
    std::string description = m_dataSet->getName();
    // a description max. 80 char
    description.copy( outField->descrip, 80 );

    WMatrix< double > matrix = grid->getTransformationMatrix();
    for( size_t i = 0; i < 4; ++i )
    {
        for( size_t j = 0; j < 4; ++j )
        {
            outField->qto_xyz.m[i][j] = matrix( i, j );
            outField->sto_xyz.m[i][j] = matrix( i, j );
        }
    }

    {
        float dx, dy, dz;
        nifti_mat44_to_quatern( outField->qto_xyz, &( outField->quatern_b ),
                                &( outField->quatern_c ), &( outField->quatern_d ),
                                &( outField->qoffset_x ), &( outField->qoffset_y ),
                                &( outField->qoffset_z ),
                                &dx, &dy, &dz,
                                &( outField->qfac ) );
    }

    outField->qto_ijk = nifti_mat44_inverse( outField->qto_xyz );
    outField->sto_ijk = nifti_mat44_inverse( outField->sto_xyz );

    void* data = 0;
    switch( ( *m_dataSet ).getValueSet()->getDataType() )
    {
        case W_DT_DOUBLE:
            outField->datatype = DT_DOUBLE;
            castData< double > ( data );
            outField->nbyper = 8;
            break;
        case W_DT_FLOAT:
            outField->datatype = DT_FLOAT;
            castData< float > ( data );
            outField->nbyper = 4;
            break;
        case W_DT_UNSIGNED_CHAR:
            outField->datatype = DT_UNSIGNED_CHAR;
            castData< uint8_t > ( data );
            outField->nbyper = 1;
            break;
        case W_DT_INT8:
            outField->datatype = DT_INT8;
            castData< int8_t > ( data );
            outField->nbyper = 1;
            break;
        case W_DT_UINT16:
            outField->datatype = DT_UINT16;
            castData< uint16_t > ( data );
            outField->nbyper = 2;
            break;
        case W_DT_INT16:
            outField->datatype = DT_INT16;
            castData< int16_t > ( data );
            outField->nbyper = 2;
            break;
        case W_DT_UINT32:
            outField->datatype = DT_UINT32;
            castData< uint32_t > ( data );
            outField->nbyper = 4;
            break;
        case W_DT_SIGNED_INT:
            outField->datatype = DT_SIGNED_INT;
            castData< int32_t > ( data );
            outField->nbyper = 4;
            break;
        default:
            WAssert( false, "Data set type not yet supported." );
    }
    outField->data = data;

    std::string s = m_filename->get().string();
    if( nifti_set_filenames( outField, s.c_str(), 0, 1 ) )
    {
        throw WException( std::string( "NIfTI filename Problem" ) );
    }

    nifti_image_write( outField );

    std::shared_ptr< WDataSetRawHARDI > h = std::dynamic_pointer_cast< WDataSetRawHARDI >( m_dataSet );
    if( h )
    {
        std::fstream f( ( s + ".bvec" ).c_str(), std::ios_base::out );
        for( std::size_t i = 0; i < 3; ++i )
        {
            for( std::size_t k = 0; k < h->getNumberOfMeasurements(); ++k )
            {
                f << h->getGradient( k )[ i ] << " ";
            }
            f << std::endl;
        }
        f.close();
    }

    nifti_image_free( outField );
    infoLog() << "Writing data completed.";
}
