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

#include <fstream>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>


#include "WReaderNIfTI.h"
#include "core/common/WIOTools.h"
#include "core/common/WLogger.h"
#include "core/dataHandler/WDataHandlerEnums.h"
#include "core/dataHandler/WDataSet.h"
#include "core/dataHandler/WDataSetDTI.h"
#include "core/dataHandler/WDataSetRawHARDI.h"
#include "core/dataHandler/WDataSetScalar.h"
#include "core/dataHandler/WDataSetSegmentation.h"
#include "core/dataHandler/WDataSetSingle.h"
#include "core/dataHandler/WDataSetSphericalHarmonics.h"
#include "core/dataHandler/WDataSetTimeSeries.h"
#include "core/dataHandler/WDataSetVector.h"
#include "core/dataHandler/WGrid.h"
#include "core/dataHandler/WGridRegular3D.h"
#include "core/dataHandler/WSubject.h"
#include "core/dataHandler/WValueSet.h"
#include "core/dataHandler/WValueSetBase.h"

WReaderNIfTI::WReaderNIfTI( std::string fileName )
    : WReader( fileName ),
      m_sform( 4, 4 ),
      m_qform( 4, 4 )
{
}

template< typename T >  std::shared_ptr< std::vector< T > > WReaderNIfTI::copyArray( const T* dataArray, const size_t countVoxels,
        const size_t vDim )
{
    std::shared_ptr< std::vector< T > > data( new std::vector< T >( countVoxels * vDim ) );
    for( unsigned int i = 0; i < countVoxels; ++i )
    {
        for( unsigned int j = 0; j < vDim; ++j )
        {
            (*data)[i * vDim + j] = dataArray[( j * countVoxels ) + i];
        }
    }
    return data;
}


WMatrix< double > WReaderNIfTI::convertMatrix( const mat44& in )
{
    WMatrix< double > out( 4, 4 );

    bool isZero = true;
    for( size_t i = 0; i < 4; ++i )
    {
        for( size_t j = 0; j < 4; ++j )
        {
            out( i, j ) = in.m[i][j];
            isZero = isZero && out( i, j ) == 0.0;
        }
    }

    if( isZero )
    {
        out.makeIdentity();
    }
    return out;
}

WReaderNIfTI::GradVec WReaderNIfTI::readGradientsIfAvailable( unsigned int vDim )
{
    std::string gradientFileName = m_fname;
    std::string suffix = getSuffix( m_fname );

    if( suffix == ".gz" )
    {
        WAssert( gradientFileName.length() > 3, "" );
        gradientFileName.resize( gradientFileName.length() - 3 );
        suffix = getSuffix( gradientFileName );
    }
    WAssert( suffix == ".nii", "Input file is not a nifti file." );

    WAssert( gradientFileName.length() > 4, "" );
    gradientFileName.resize( gradientFileName.length() - 4 );
    gradientFileName += ".bvec";

    GradVec result; // incase of error return NULL_ptr

    // check if the file exists
    std::ifstream i( gradientFileName.c_str() );
    if( i.bad() || !i.is_open() )
    {
        if( i.is_open() )
        {
            i.close();
        }
        wlog::debug( "WReaderNIfTI" ) << "Could not find gradient file expected at: \"" << gradientFileName << "\", skipping this.";
    }
    else
    {
        wlog::debug( "WReaderNIfTI" ) << "Found b-vectors file: " << gradientFileName << " will try reading...";
        result = GradVec( new std::vector< WVector3d >( vDim ) );

        // the file should contain the x-coordinates in line 0, y-coordinates in line 1,
        // z-coordinates in line 2
        for( unsigned int j = 0; j < 3; ++j )
        {
            for( unsigned int k = 0; k < vDim; ++k )
            {
                i >> result->operator[] ( k )[ j ];
            }
        }
        bool success = !i.eof();
        i.close();
        if( !success )
        {
            wlog::error( "WReaderNIfTI" ) << "Error while reading gradient file: did not contain enough gradients: " << result->size();
            return GradVec(); // return Null_ptr
        }
        else
        {
            wlog::debug( "WReaderNIfTI" ) << "Successfully loaded " << result->size() << " gradients";
        }
    }
    return result;
}

WReaderNIfTI::BValues WReaderNIfTI::readBValuesIfAvailable( unsigned int vDim )
{
    std::string bvaluesFileName = m_fname;
    std::string suffix = getSuffix( m_fname );

    if( suffix == ".gz" )
    {
        WAssert( bvaluesFileName.length() > 3, "" );
        bvaluesFileName.resize( bvaluesFileName.length() - 3 );
        suffix = getSuffix( bvaluesFileName );
    }
    WAssert( suffix == ".nii", "Input file is not a nifti file." );

    WAssert( bvaluesFileName.length() > 4, "" );
    bvaluesFileName.resize( bvaluesFileName.length() - 4 );
    bvaluesFileName += ".bval";

    BValues result; // return NULL_ptr in case of error

    // check if the file exists
    std::ifstream i( bvaluesFileName.c_str() );
    if( i.bad() || !i.is_open() )
    {
        if( i.is_open() )
        {
            i.close();
        }
        wlog::debug( "WReaderNIfTI" ) << "Could not find b-values file expected at: \"" << bvaluesFileName << "\", skipping this.";
    }
    else
    {
        //read b-values
        char value[ 8 ];
        // there should be 3 * vDim values in the file
        result = BValues( new std::vector< float >( vDim * 3, 0 ) );
        size_t numValues = 0;
        while( i.good() && !i.eof() )
        {
            i.getline( value, 8 );
            float fVal;
            std::istringstream( value ) >> fVal;
            ( *result )[ numValues ] = fVal;
            if( numValues > vDim * 3 )
            {
                wlog::error( "WReaderNIfTI" ) << "Too many b-Values: " << numValues << " but expected: " << vDim * 3;
                return BValues(); // return Null_ptr
            }
            numValues++;
        }

        i.close();

        wlog::debug( "WReaderNIfTI" ) << "Found b-values file and loaded " << result->size() << " values.";
    }
    return result;
}

std::shared_ptr< WDataSet > WReaderNIfTI::load( DataSetType dataSetType )
{
    std::shared_ptr< nifti_image > filedata( nifti_image_read( m_fname.c_str(), 1 ), &nifti_image_free );

    WAssert( filedata, "Error during file access to NIfTI file. This probably means that the file is corrupted." );

    WAssert( filedata->ndim >= 3,
             "The NIfTI file contains data that has less than the three spatial dimension. OpenWalnut is not able to handle this." );

    int columns = filedata->dim[1];
    int rows = filedata->dim[2];
    int frames = filedata->dim[3];

    std::shared_ptr< WValueSetBase > newValueSet;
    std::shared_ptr< WGrid > newGrid;

    unsigned int vDim;
    if( filedata->ndim >= 4 )
    {
        vDim = filedata->dim[4];
    }
    else
    {
        vDim = 1;
    }

    unsigned int order = ( ( vDim == 1 ) ? 0 : 1 );  // TODO(all): Does recognize vectors and scalars only so far.
    unsigned int countVoxels = columns * rows * frames;

    // don't rearrange if this is a time series
    if( filedata->dim[ 5 ] <= 1 )
    {
        switch( filedata->datatype )
        {
            case DT_UINT8:
            {
                std::shared_ptr< std::vector< uint8_t > > data = copyArray( reinterpret_cast< uint8_t* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< uint8_t >( order, vDim, data, W_DT_UINT8 ) );
                break;
            }
            case DT_INT8:
            {
                std::shared_ptr< std::vector< int8_t > > data = copyArray( reinterpret_cast< int8_t* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< int8_t >( order, vDim, data, W_DT_INT8 ) );
                break;
            }
            case DT_INT16:
            {
                std::shared_ptr< std::vector< int16_t > > data = copyArray( reinterpret_cast< int16_t* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< int16_t >( order, vDim, data, W_DT_INT16 ) );
                break;
            }
            case DT_UINT16:
            {
                std::shared_ptr< std::vector< uint16_t > > data
                    = copyArray( reinterpret_cast< uint16_t* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< uint16_t >( order, vDim, data, W_DT_UINT16 ) );
                break;
            }
            case DT_SIGNED_INT:
            {
                std::shared_ptr< std::vector< int32_t > > data = copyArray( reinterpret_cast< int32_t* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< int32_t >( order, vDim, data, W_DT_SIGNED_INT ) );
                break;
            }
            case DT_UINT32:
            {
                std::shared_ptr< std::vector< uint32_t > > data
                    = copyArray( reinterpret_cast< uint32_t* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< uint32_t >( order, vDim, data, W_DT_UINT32 ) );
                break;
            }
            case DT_INT64:
            {
                std::shared_ptr< std::vector< int64_t > > data = copyArray( reinterpret_cast< int64_t* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< int64_t >( order, vDim, data, W_DT_INT64 ) );
                break;
            }
            case DT_UINT64:
            {
                std::shared_ptr< std::vector< uint64_t > > data =
                    copyArray( reinterpret_cast< uint64_t* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< uint64_t >( order, vDim, data, W_DT_UINT64 ) );
                break;
            }
            case DT_FLOAT:
            {
                std::shared_ptr< std::vector< float > > data = copyArray( reinterpret_cast< float* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< float >( order, vDim, data, W_DT_FLOAT ) );
                break;
            }
            case DT_DOUBLE:
            {
                std::shared_ptr< std::vector< double > > data = copyArray( reinterpret_cast< double* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< double >( order, vDim, data, W_DT_DOUBLE ) );
                break;
            }
            case DT_FLOAT128:
            {
                std::shared_ptr< std::vector< long double > > data =
                    copyArray( reinterpret_cast< long double* >( filedata->data ), countVoxels, vDim );
                newValueSet = std::shared_ptr< WValueSetBase >( new WValueSet< long double >( order, vDim, data, W_DT_FLOAT128 ) );
                break;
            }
            default:
                wlog::error( "WReaderNIfTI" ) << "unknown data type " << filedata->datatype << std::endl;
                newValueSet = std::shared_ptr< WValueSetBase >();
        }
    }

    m_sform = convertMatrix( filedata->sto_xyz );
    m_qform = convertMatrix( filedata->qto_xyz );
    newGrid = std::shared_ptr< WGridRegular3D >(
                        new WGridRegular3D( columns, rows, frames, WGridTransformOrtho( getStandardTransform() ) ) );

    std::shared_ptr< WDataSet > newDataSet;
    // known description
    std::string description( filedata->descrip );
    if( !description.compare( "WDataSetSegmentation" ) )
    {
        wlog::debug( "WReaderNIfTI" ) << "Load as segmentation" << std::endl;
        newDataSet = std::shared_ptr< WDataSet >( new WDataSetSegmentation( newValueSet, newGrid ) );
    }
    else if( description.compare( "WDataSetSphericalHarmonics" ) == 0 || dataSetType == W_DATASET_SPHERICALHARMONICS )
    {
        wlog::debug( "WReaderNIfTI" ) << "Load as spherical harmonics" << std::endl;
        newDataSet = std::shared_ptr< WDataSet >( new WDataSetSphericalHarmonics( newValueSet, newGrid ) );
    }
    // 4th dimension is the time
    // note that in the nifti standard, dim[ 4 ] is the temporal dimension
    // we use dim[ 5 ] here
    else if( filedata->dim[ 5 ] > 1 )
    {
        WAssert( filedata->dim[ 4 ] == 1, "Only scalar datasets are supported for time series so far." );
        wlog::debug( "WReaderNIfTI" ) << "Load as WDataSetTimeSeries";
        std::size_t numTimeSlices = filedata->dim[ 5 ];
        float tw = filedata->pixdim[ 5 ];
        WAssert( tw != 0.0f, "" );

        std::vector< std::shared_ptr< WDataSetScalar const > > ds;
        std::vector< float > times;
        float t = 0.0f;
        for( std::size_t k = 0; k < numTimeSlices; ++k )
        {
            times.push_back( t );
            t += tw;
            std::shared_ptr< WValueSetBase > vs;
            switch( filedata->datatype )
            {
                case DT_UINT8:
                {
                    uint8_t* ptr = reinterpret_cast< uint8_t* >( filedata->data );
                    std::shared_ptr< std::vector< uint8_t > > values =
                        std::shared_ptr< std::vector< uint8_t > >(
                            new std::vector< uint8_t >( ptr + k * countVoxels, ptr + ( k + 1 ) * countVoxels ) );
                    vs = std::shared_ptr< WValueSetBase >( new WValueSet< uint8_t >( 0, 1, values, W_DT_UINT8 ) );
                }
                break;
                case DT_INT8:
                {
                    int8_t* ptr = reinterpret_cast< int8_t* >( filedata->data );
                    std::shared_ptr< std::vector< int8_t > > values =
                        std::shared_ptr< std::vector< int8_t > >(
                            new std::vector< int8_t >( ptr + k * countVoxels, ptr + ( k + 1 ) * countVoxels ) );
                    vs = std::shared_ptr< WValueSetBase >( new WValueSet< int8_t >( 0, 1, values, W_DT_INT8 ) );
                }
                break;
                case DT_UINT16:
                {
                    uint16_t* ptr = reinterpret_cast< uint16_t* >( filedata->data );
                    std::shared_ptr< std::vector< uint16_t > >values =
                        std::shared_ptr< std::vector< uint16_t > >(
                            new std::vector< uint16_t >( ptr + k * countVoxels, ptr + ( k + 1 ) * countVoxels ) );
                    vs = std::shared_ptr< WValueSetBase >( new WValueSet< uint16_t >( 0, 1, values, W_DT_UINT16 ) );
                }
                break;
                case DT_INT16:
                {
                    int16_t* ptr = reinterpret_cast< int16_t* >( filedata->data );
                    std::shared_ptr< std::vector< int16_t > > values =
                        std::shared_ptr< std::vector< int16_t > >(
                            new std::vector< int16_t >( ptr + k * countVoxels, ptr + ( k + 1 ) * countVoxels ) );
                    vs = std::shared_ptr< WValueSetBase >( new WValueSet< int16_t >( 0, 1, values, W_DT_INT16 ) );
                }
                break;
                case DT_UINT32:
                {
                    uint32_t* ptr = reinterpret_cast< uint32_t* >( filedata->data );
                    std::shared_ptr< std::vector< uint32_t > > values =
                        std::shared_ptr< std::vector< uint32_t > >(
                            new std::vector< uint32_t >( ptr + k * countVoxels, ptr + ( k + 1 ) * countVoxels ) );
                    vs = std::shared_ptr< WValueSetBase >( new WValueSet< uint32_t >( 0, 1, values, W_DT_UINT32 ) );
                }
                break;
                case DT_SIGNED_INT:
                {
                    int32_t* ptr = reinterpret_cast< int32_t* >( filedata->data );
                    std::shared_ptr< std::vector< int32_t > > values =
                        std::shared_ptr< std::vector< int32_t > >(
                            new std::vector< int32_t >( ptr + k * countVoxels, ptr + ( k + 1 ) * countVoxels ) );
                    vs = std::shared_ptr< WValueSetBase >( new WValueSet< int32_t >( 0, 1, values, W_DT_SIGNED_INT ) );
                }
                break;
                case DT_UINT64:
                {
                    uint64_t* ptr = reinterpret_cast< uint64_t* >( filedata->data );
                    std::shared_ptr< std::vector< uint64_t > > values =
                        std::shared_ptr< std::vector< uint64_t > >(
                            new std::vector< uint64_t >( ptr + k * countVoxels, ptr + ( k + 1 ) * countVoxels ) );
                    vs = std::shared_ptr< WValueSetBase >( new WValueSet< uint64_t >( 0, 1, values, W_DT_UINT64 ) );
                }
                break;
                case DT_INT64:
                {
                    int64_t* ptr = reinterpret_cast< int64_t* >( filedata->data );
                    std::shared_ptr< std::vector< int64_t > > values =
                        std::shared_ptr< std::vector< int64_t > >(
                            new std::vector< int64_t >( ptr + k * countVoxels, ptr + ( k + 1 ) * countVoxels ) );
                    vs = std::shared_ptr< WValueSetBase >( new WValueSet< int64_t >( 0, 1, values, W_DT_INT64 ) );
                }
                break;
                case DT_FLOAT:
                {
                    float* ptr = reinterpret_cast< float* >( filedata->data );
                    std::shared_ptr< std::vector< float > > values =
                        std::shared_ptr< std::vector< float > >(
                            new std::vector< float >( ptr + k * countVoxels, ptr + ( k + 1 ) * countVoxels ) );
                    vs = std::shared_ptr< WValueSetBase >( new WValueSet< float >( 0, 1, values, W_DT_FLOAT ) );
                }
                break;
                case DT_DOUBLE:
                {
                    double* ptr = reinterpret_cast< double* >( filedata->data );
                    std::shared_ptr< std::vector< double > > values =
                        std::shared_ptr< std::vector< double > >(
                            new std::vector< double >( ptr + k * countVoxels, ptr + ( k + 1 ) * countVoxels ) );
                    vs = std::shared_ptr< WValueSetBase >( new WValueSet< double >( 0, 1, values, W_DT_DOUBLE ) );
                }
                break;
                default:
                    throw WException( std::string( "Unsupported datatype in WReaderNIfTI" ) );
                    break;
            }
            ds.push_back( std::shared_ptr< WDataSetScalar >( new WDataSetScalar( vs, newGrid ) ) );
        }
        newDataSet = std::shared_ptr< WDataSet >( new WDataSetTimeSeries( ds, times ) );
    }
    // unknown description
    else
    {
        if( vDim == 3 )
        {
            wlog::debug( "WReaderNIfTI" ) << "Load as WDataSetVector";
            newDataSet = std::shared_ptr< WDataSet >( new WDataSetVector( newValueSet, newGrid ) );
        }
        else if( vDim == 1 )
        {
            wlog::debug( "WReaderNIfTI" ) << "Load as WDataSetScalar";
            newDataSet = std::shared_ptr< WDataSet >( new WDataSetScalar( newValueSet, newGrid ) );
        }
        else if( vDim > 20 && filedata->dim[ 5 ] <= 1 ) // hardi data, order 1
        {
            wlog::debug( "WReaderNIfTI" ) << "Load as WDataSetRawHARDI";

            GradVec newGradients = readGradientsIfAvailable( vDim );
            BValues newBValues = readBValuesIfAvailable( vDim );

            if( !newGradients )
            {
                // cannot find the appropriate gradient vectors and/or bvalues, build a dataSetSingle instead of hardi
                newDataSet = std::shared_ptr< WDataSet >( new WDataSetSingle( newValueSet, newGrid ) );
                wlog::debug( "WReaderNIfTI" ) << "No gradients given. See above for expected filename. Loading as WDataSetSingle instead.";
            }
            else
            {
                if( !newBValues )
                {
                    newDataSet = std::shared_ptr< WDataSet >( new WDataSetRawHARDI( newValueSet, newGrid, newGradients ) );
                }
                else
                {
                    newDataSet = std::shared_ptr< WDataSet >( new WDataSetRawHARDI( newValueSet, newGrid, newGradients, newBValues ) );
                }
            }

            if( newBValues && newGradients && ( newBValues->size() > 1 && newBValues->size() != newGradients->size() * 3 ) )
            {
                wlog::warn( "WReaderNIfTI" ) << "Be careful: there are " << newBValues->size() / 3 << " b-values but only "
                    << newGradients->size() << " gradients.";
            }
        }
        else if( filedata->intent_code == NIFTI_INTENT_SYMMATRIX )
        {
            wlog::debug( "WReaderNIfTI" ) << "Load as WDataSetDTI";
            newDataSet = std::shared_ptr< WDataSetDTI >( new WDataSetDTI( newValueSet, newGrid ) );
        }
        else
        {
            wlog::debug( "WReaderNIfTI" ) << "Load as WDataSetSingle";
            newDataSet = std::shared_ptr< WDataSet >( new WDataSetSingle( newValueSet, newGrid ) );
        }
    }
    newDataSet->setFilename( m_fname );

    return newDataSet;
}

WMatrix< double > WReaderNIfTI::getStandardTransform() const
{
    return WMatrix< double >( 4, 4 ).makeIdentity();
}

WMatrix< double > WReaderNIfTI::getSFormTransform() const
{
    return m_sform;
}

WMatrix< double > WReaderNIfTI::getQFormTransform() const
{
    return m_qform;
}
