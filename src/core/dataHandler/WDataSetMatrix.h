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

#ifndef WDATASETMATRIX_H
#define WDATASETMATRIX_H

#include <string>

#include "WDataSetSingle.h"


/**
 * Represents dataset with a matrix at every point.
 */
class WDataSetMatrix : public WDataSetSingle
{
public:
    /**
     * Creates a new matrix dataset out of a value set and a grid.
     *
     * \param newValueSet Valueset having vectors of number of entries of the matrix.
     * \param newGrid The grid for the dataset
     * \param nbRows Number of rows of stored matrices
     * \param nbColumns Number of columns of stored matrices
     */
    WDataSetMatrix( std::shared_ptr< WValueSetBase > newValueSet, std::shared_ptr< WGrid > newGrid, size_t nbRows, size_t nbColumns );

    /**
     * Constructs a new set of matrices. The constructed instance is not usable but needed for prototype mechanism.
     */
    WDataSetMatrix();

    /**
     * Destructs this dataset.
     */
    ~WDataSetMatrix();

    /**
     * Creates a copy (clone) of this instance but allows one to change the valueset. Unlike copy construction, this is a very useful function if you
     * want to keep the dynamic type of your dataset even if you just have a WDataSetSingle.
     *
     * \param newValueSet the new valueset.
     *
     * \return the clone
     */
    virtual WDataSetSingle::SPtr clone( std::shared_ptr< WValueSetBase > newValueSet ) const;

    /**
     * Creates a copy (clone) of this instance but allows one to change the grid. Unlike copy construction, this is a very useful function if you
     * want to keep the dynamic type of your dataset even if you just have a WDataSetSingle.
     *
     * \param newGrid the new grid.
     *
     * \return the clone
     */
    virtual WDataSetSingle::SPtr clone( std::shared_ptr< WGrid > newGrid ) const;

    /**
     * Creates a copy (clone) of this instance. Unlike copy construction, this is a very useful function if you
     * want to keep the dynamic type of your dataset even if you just have a WDataSetSingle.
     *
     * \return the clone
     */
    virtual WDataSetSingle::SPtr clone() const;

    /**
     * Retrieves the i'th matrix.
     *
     * \warning Here is dynamical allocation used inside, this may be a problem when used with multithreading.
     *
     * \param index The position of the matrix to retrieve
     *
     * \return The new constructed matrix.
     */
    WMatrix< double > getMatrixDouble( size_t index ) const;

    /**
     * Gets the name of this prototype.
     *
     * \return the name.
     */
    virtual const std::string getName() const;

    /**
     * Gets the description for this prototype.
     *
     * \return the description
     */
    virtual const std::string getDescription() const;

    /**
     * Returns a prototype instantiated with the true type of the deriving class.
     *
     * \return the prototype.
     */
    static std::shared_ptr< WPrototyped > getPrototype();


protected:
    /**
     * The prototype as singleton.
     */
    static std::shared_ptr< WPrototyped > m_prototype;

private:
    size_t rows; //!< Number of rows of stored matrices
    size_t columns; //!< Number of columns of stored matrices
};

#endif  // WDATASETMATRIX_H
