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
#include <memory>
#include <string>

#include "WMReadRawData.h"
#include "WMReadRawData.xpm"
#include "core/common/WPathHelper.h"
#include "core/kernel/WKernel.h"

// This line is needed by the module loader to actually find your module. Do not remove. Do NOT add a ";" here.
W_LOADABLE_MODULE( WMReadRawData )

WMReadRawData::WMReadRawData():
    WModule()
{
}

WMReadRawData::~WMReadRawData()
{
    // Cleanup!
}

std::shared_ptr< WModule > WMReadRawData::factory() const
{
    return std::shared_ptr< WModule >( new WMReadRawData() );
}

const char** WMReadRawData::getXPMIcon() const
{
    return WMReadRawData_xpm; // Please put a real icon here.
}
const std::string WMReadRawData::getName() const
{
    return "Read Raw Data";
}

const std::string WMReadRawData::getDescription() const
{
    return "Read scalar data defined on uniform lattices"
        " in raw format, i.e., plain three-dimensional arrays of data.";
}

void WMReadRawData::connectors()
{
    m_output = std::shared_ptr< WModuleOutputData< WDataSetScalar > >(
            new WModuleOutputData< WDataSetScalar >( shared_from_this(), "Data", "The loaded data." ) );

    addConnector( m_output );

    WModule::connectors();
}

void WMReadRawData::properties()
{
    m_propCondition = std::shared_ptr< WCondition >( new WCondition() );
    m_dataFile = m_properties->addProperty( "File", "", WPathHelper::getAppPath(), m_propCondition );
    WPropertyHelper::PC_PATHEXISTS::addTo( m_dataFile );

    m_dataTypeSelectionsList = std::shared_ptr< WItemSelection >( new WItemSelection() );
    m_dataTypeSelectionsList->addItem( "UINT8", "" );
    m_dataTypeSelectionsList->addItem( "UINT16", "" );
    m_dataTypeSelectionsList->addItem( "UINT32", "" );
    m_dataTypeSelectionsList->addItem( "UINT64", "" );
    m_dataTypeSelectionsList->addItem( "INT8", "" );
    m_dataTypeSelectionsList->addItem( "INT16", "" );
    m_dataTypeSelectionsList->addItem( "INT32", "" );
    m_dataTypeSelectionsList->addItem( "INT64", "" );
    m_dataTypeSelectionsList->addItem( "FLOAT", "" );
    m_dataTypeSelectionsList->addItem( "DOUBLE", "" );
    m_dataTypeSelectionsList->addItem( "FLOAT128", "" );

    m_dataTypeSelection = m_properties->addProperty( "Data type",  "Data type.", m_dataTypeSelectionsList->getSelectorFirst(), m_propCondition );
    WPropertyHelper::PC_SELECTONLYONE::addTo( m_dataTypeSelection );

    m_X = m_properties->addProperty( "X", "Data sample in X direction.", 256, m_propCondition );
    m_X->setMin( 0 );
    m_X->setMax( 4096 );
    m_Y = m_properties->addProperty( "Y", "Data sample in Y direction.", 256, m_propCondition );
    m_Y->setMin( 0 );
    m_Y->setMax( 4096 );
    m_Z = m_properties->addProperty( "Z", "Data sample in Z direction.", 256, m_propCondition );
    m_Z->setMin( 0 );
    m_Z->setMax( 4096 );

    m_xScale = m_properties->addProperty( "X Scale", "Data scaling in X direction.", 1.0, m_propCondition );
    m_xScale->setMin( 0 );
    m_yScale = m_properties->addProperty( "Y Scale", "Data scaling in Y direction.", 1.0, m_propCondition );
    m_yScale->setMin( 0 );
    m_zScale = m_properties->addProperty( "Z Scale", "Data scaling in Z direction.", 1.0, m_propCondition );
    m_zScale->setMin( 0 );

    WModule::properties();
}

void WMReadRawData::requirements()
{
    // Put the code for your requirements here. See "src/modules/template/" for an extensively documented example.
}

void WMReadRawData::moduleMain()
{
    m_moduleState.add( m_propCondition );
    ready();
    while( !m_shutdownFlag() )
    {
        m_moduleState.wait();

        if( m_shutdownFlag() )
        {
            break;
        }

        debugLog() << "Loading " << m_dataFile->get().string() << ".";
        std::shared_ptr< WProgress > progress( new WProgress( "Read Raw Data", 2 ) );
        ++*progress;
        m_dataSet = readData( m_dataFile->get().string() );
        ++*progress;
        m_output->updateData( m_dataSet );
        progress->finish();
    }
}


std::shared_ptr< WDataSetScalar > WMReadRawData::readData( std::string fileName )
{
    std::string dataTypeName = m_dataTypeSelection->get().at( 0 )->getName();
    std::shared_ptr< WValueSetBase > newValueSet;
    if( dataTypeName == "UINT8" )
    {
        newValueSet =  std::shared_ptr< WValueSetBase >( new WValueSet< uint8_t >( 0, 1, readDataTyped< uint8_t >( fileName ), W_DT_UINT8 ) );
    }
    else if( dataTypeName == "UINT16" )
    {
        newValueSet =  std::shared_ptr< WValueSetBase >( new WValueSet< uint16_t >( 0, 1, readDataTyped< uint16_t >( fileName ), W_DT_UINT16 ) );
    }
    else if( dataTypeName == "UINT32" )
    {
        newValueSet =  std::shared_ptr< WValueSetBase >( new WValueSet< uint32_t >( 0, 1, readDataTyped< uint32_t >( fileName ), W_DT_UINT32 ) );
    }
    else if( dataTypeName == "UINT64" )
    {
        newValueSet =  std::shared_ptr< WValueSetBase >( new WValueSet< uint64_t >( 0, 1, readDataTyped< uint64_t >( fileName ), W_DT_UINT64 ) );
    }
    else if( dataTypeName == "INT8" )
    {
        newValueSet =  std::shared_ptr< WValueSetBase >( new WValueSet< int8_t >( 0, 1, readDataTyped< int8_t >( fileName ), W_DT_INT8 ) );
    }
    else if( dataTypeName == "INT16" )
    {
        newValueSet =  std::shared_ptr< WValueSetBase >( new WValueSet< int16_t >( 0, 1, readDataTyped< int16_t >( fileName ), W_DT_INT16 ) );
    }
    else if( dataTypeName == "INT32" )
    {
        newValueSet =  std::shared_ptr< WValueSetBase >( new WValueSet< int32_t >( 0, 1, readDataTyped< int32_t >( fileName ), W_DT_SIGNED_INT ) );
    }
    else if( dataTypeName == "INT64" )
    {
        newValueSet =  std::shared_ptr< WValueSetBase >( new WValueSet< int64_t >( 0, 1, readDataTyped< int64_t >( fileName ), W_DT_INT64 ) );
    }
    else if( dataTypeName == "FLOAT" )
    {
        newValueSet =  std::shared_ptr< WValueSetBase >( new WValueSet< float >( 0, 1, readDataTyped< float >( fileName ), W_DT_FLOAT ) );
    }
    else if( dataTypeName == "DOUBLE" )
    {
        newValueSet =  std::shared_ptr< WValueSetBase >( new WValueSet< double >( 0, 1, readDataTyped< double >( fileName ), W_DT_DOUBLE ) );
    }
    else if( dataTypeName == "FLOAT128" )
    {
        newValueSet =
            std::shared_ptr< WValueSetBase >( new WValueSet< long double >( 0, 1, readDataTyped< long double >( fileName ), W_DT_FLOAT128 ) );
    }
    else
    {
        throw WException( "Not supported data type while reading raw data." );
    }

    std::shared_ptr< WGridRegular3D > newGrid;
    size_t numX = m_X->get();
    size_t numY = m_Y->get();
    size_t numZ = m_Z->get();
    newGrid = std::shared_ptr< WGridRegular3D >( new WGridRegular3D( numX, numY, numZ, m_xScale->get(), m_yScale->get(), m_zScale->get() ) );

    std::shared_ptr< WDataSetScalar > newDataSet;
    newDataSet = std::shared_ptr< WDataSetScalar >( new WDataSetScalar( newValueSet, newGrid ) );

    return newDataSet;
}
