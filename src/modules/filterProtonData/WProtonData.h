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

#ifndef WPROTONDATA_H
#define WPROTONDATA_H

#include <list>
#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "WDataType.h"
#include "core/dataHandler/WDataSetCSV.h"


/**
 * Holds the CSV data.
 */
class WProtonData
{
    /**
     * Only test class may be friend
     */
     friend class WProtonDataTest;
public:
    /**
     * shared_ptr that points to itself 
     */
    typedef std::shared_ptr< WProtonData > SPtr;

    /**
     * Constructor
     *
     * \param csvHeader pointer to a column-header of the CSV-file
     * \param csvData pointer to a content of the CSV file 
     */
    explicit WProtonData( WDataSetCSV::ContentSPtr csvHeader, WDataSetCSV::ContentSPtr csvData );

    /**
     * getter
     *
     * \return pointer to a column-header of the CSV-file
     */
    WDataSetCSV::ContentSPtr getCSVHeader() const;

    /**
     * Getter
     *
     * \return pointer to a content of the CSV file 
     */
    WDataSetCSV::ContentSPtr getCSVData() const;

    /**
     * Setter
     *
     * \param csvHeader set m_csvHeader
     */
    void setCSVHeader( WDataSetCSV::ContentSPtr csvHeader );

    /**
     * Setter
     *
     * \param csvData set m_csvData
     */
    void setCSVData( WDataSetCSV::ContentSPtr csvData );

    /**
     * Setter
     *
     * \param columnName Name of column-header of the CSV-file
     * \param index position of column-header of the CSV-file
     */
    void setStateIndex( std::string columnName, int index );

    /**
     * Getter
     *
     * \param selectedName Name of selected name of single-selection
     * \return return the position current selected item
     */
    int getColumnIndexBySelection( std::string selectedName );

    /**
     * Getter
     *
     * \param columnName Name of column-header of the CSV-file
     * \return return the position of column-header of the CSV-file as int
     */
    int getColumnIndex( std::string columnName );

    /**
     * Checks whether columns are available
     * \param columnName The name of the column.
     * \return true if column is available, false if column is not available
     */
    bool isColumnAvailable( std::string columnName );

    /**
     * Get column types, stored in a string vector.
     * Positions within this vector are linked to positions in m_csvHeader
     * \return a shared pointer to m_columnTypes
     */
    std::shared_ptr< std::vector< std::string > > getColumnTypes() const;

    /**
     * Return a vector of filtered Headers
     * \param typeNames Types of filter 
     * \return Return a vector of filtered Headers
     */
    std::vector< std::string_view > getHeaderFromType( std::list< std::string > typeNames ) const;

private:
    /**
     * Stores column index of data.
     */
    WDataSetCSV::ContentSPtr m_csvHeader;

    /**
     * Stores data from obtained input file.
     */
    WDataSetCSV::ContentSPtr m_csvData;

    /**
     * Stores data as map
     */
    std::map< std::string, int > m_columnMap;

    /**
     * Stores index of the selected single-selector (ColumnPropertyHandler)
     */
    std::map< std::string, int > m_ColumnMapSelectedIndex;

    /**
     * Stores the information, which data type is stored in associated column
     */
    std::shared_ptr< std::vector< std::string > > m_columnTypes;

    /**
     * Reads CSV data and stores column types in m_columnTypes
     * \param csvData the input CSV data
     */
    void detectColumnTypesFromCsvData( WDataSetCSV::ContentSPtr csvData );

    /**
     * Determines column type due to cellValue
     * \param cellValue the value of a cell on the basis of which the column type is to be determined
     * \return either "int", "double" or "string"
     */
    std::string determineColumnTypeByString( std::string cellValue ) const;

    /**
     * Checks, if values of a column, containing double values, can be converted to integers
     * \param columnNumber the column number within m_csvHeader
     * \return true, if all double values of a column ends with ".0"; false otherwise
     */
    bool checkIfDoubleColumnCanBeInteger( int columnNumber ) const;
};

#endif  // WPROTONDATA_H
