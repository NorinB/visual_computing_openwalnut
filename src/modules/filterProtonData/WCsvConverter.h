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

#ifndef WCSVCONVERTER_H
#define WCSVCONVERTER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include "WConverterIndexes.h"
#include "WConverterVectors.h"
#include "WPropertyStatus.h"
#include "WProtonData.h"
#include "WSingleSelectorName.h"
#include "core/common/WLogger.h"
#include "core/common/WTransferFunction.h"
#include "core/dataHandler/WDataSetFibers.h"
#include "core/dataHandler/WDataSetPoints.h"
#include "core/dataHandler/WGrid.h"
#include "core/dataHandler/WGridRegular3D.h"
#include "core/dataHandler/WValueSet.h"
#include "core/dataHandler/WValueSetBase.h"


/**
 * Converts the csv data to points and fibers.
 */
class WCsvConverter
{
    /**
     * only test classes may be friend
     */
     friend class WCsvConverterTest;
public:
    /**
     * Initializes the vectors, indices and transfer function color bar
     * Calls setOutputFromCSV.
     * \param protonData The proton data to use.
     * \param propertyStatus The status of the properties.
     * \param colorBar Reference to the transfer function color bar module
     */
    WCsvConverter( WProtonData::SPtr protonData, std::shared_ptr< WPropertyStatus > propertyStatus, WModule::SPtr colorBar );

    /**
     * represents a std::shared_ptr to a vector containing a vector of floats.
     */
    typedef std::shared_ptr< std::vector< float > > SPFloatVector;

    /**
     * represents a std::shared_ptr to a vector containing a vector of size_t.
     */
    typedef std::shared_ptr< std::vector< size_t > > SPSizeVector;

    /**
     * Getter
     *
     * \return shared_ptr of generated fibers from the CSV file 
     */
    std::shared_ptr< WDataSetFibers > getFibers();

    /**
     * Getter
     *
     * \return shared_ptr of generated Points from the CSV file 
     */
    std::shared_ptr< WDataSetPoints > getPoints();

    /**
     * Getter
     * \return shared_ptr of generated transfer function
     */
    std::shared_ptr< WDataSetSingle > getTransferFunction();

    /**
     * Getter
     * \return shared_ptr of generated selected event ID
     */
    std::shared_ptr< WDataSetPoints > getPointsAndData();

private:
    /**
     * Stores information form csv content. Content object containing data
     */
    WProtonData::SPtr m_protonData;

    /**
     * Stores reference to the given transfer function color bar module
     */
    WModule::SPtr m_colorBar;

    /**
     * Stores information for the fiber display
     */
    std::shared_ptr< WDataSetFibers > m_fibers;

    /**
     * Stores information for the point renderer
     */
    std::shared_ptr< WDataSetPoints > m_points;

    /**
     * Stores information for the point Conncetor
     */
    std::shared_ptr< WDataSetPoints > m_pointsAndData;

    /**
     * Stores the currently mapped transfer function
     */
    std::shared_ptr< WDataSetSingle > m_transferFunction;

    /**
     * Stores points for point and fiber renderer
     */
    WConverterVectors::SPtr m_vectors;

    /**
     * Stores indexes for fiber renderer
     */
    WConverterIndexes::SPtr m_indexes;

    /**
     * includes all property groups 
     */
    WPropertyStatus::SPtr m_propertyStatus;

    /**
     * Computes gradient vector from transfer function specified in visualization properties.
     * \return shared_ptr of mapped gradim_plainColorent from transfer function in RGBA format
     */
    std::shared_ptr< std::vector<unsigned char> > sampleTransferFunction();

    /**
     * Normalize energy deposition values to use as RGB values
     * \param edeps vector containing energy deposition values
     * \param colorArray vector containing colors per vertex
     * \param maxEdep maximum energy deposition
     * \param minEdep minimum energy deposition
     */
    void normalizeEdeps( SPFloatVector edeps, SPFloatVector colorArray,  float maxEdep, float minEdep );


    /**
     * checks whether the requirements are fulfilled.
     * \param dataRow the row to check.
     * \return true The row can be displayed.
     * \return false The row can not be displayed.
     */
    bool checkConditionToPass( WDataSetCSV::Content::iterator dataRow );

    /**
     * Create vertex for point/fiber renderer
     *
     * \param dataRow each row of the csv file (content of row)
     */
    void addVertex( WDataSetCSV::Content::iterator dataRow );

    /**
     * Create color for point/Fiber renderer
     *
     * \param plainColor The color to create
     */
    void addColor( WColor plainColor );

    /**
     * Create edep and sizes for point/fiber renderer
     *
     * \param dataRow each row of the csv file (content of row)
     * \param maxEdep a pointer to the current maximum of the edep
     * \param minEdep a pointer to the current minimum of the edep
     */
    void addEdepAndSize( WDataSetCSV::Content::iterator dataRow, float* maxEdep, float* minEdep );

    /**
     * Create eventID for Fiber renderer
     *
     * \param dataRow each row of the csv file (content of row)
     */
    void addEventID( WDataSetCSV::Content::iterator dataRow );

    /**
     * calculate the property of WDataSetFiber (index, length, verticesReverse)
     */
    void calculateFibers();

    /**
     * Create the fibers for fiber renderer
     */
    void createOutputFibers();

    /**
     * Create the points for points renderer
     */
    void createOutputPoints();

    /**
     * Create the points and selected data for Point Connector
     */
    void createOutputPointsAndData();

    /**
     * Create outputs, so it can be displayed by the fiber display and the point renderer.
     */
    void setOutputFromCSV( );

    /**
     * Creates output for transfer function
     * \param data shared_ptr of mapped gradient from transfer function in RGBA format
     */
    void setTransferFunction( std::shared_ptr< std::vector<unsigned char> > data );

    /**
     * the cast value from string to float
     * \return returns the cast value from string to float
     */
    bool checkIfOutputIsNull();

    /**
     * Computes the cluster size
     * \param edep energy deposition
     * \return float cluster size
     */
    float getClusterSize( float edep );

    /**
     * checks whether the string is a number (double)  
     * \param str The string to cast
     * \return return the casted double value
     */
    float stringToDouble( std::string_view str );

    /**
     * checks whether the string is a number (int)
     * \param str The string to cast
     * \return return the casted int value
     */
    int stringToInt( std::string_view str );
};

#endif  // WCSVCONVERTER_H
