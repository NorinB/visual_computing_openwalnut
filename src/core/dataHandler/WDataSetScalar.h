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

#ifndef WDATASETSCALAR_H
#define WDATASETSCALAR_H

#include <map>
#include <memory>
#include <string>

#include <boost/thread.hpp>

#include "WDataSetSingle.h"
#include "datastructures/WValueSetHistogram.h"


/**
 * This data set type contains scalars as values.
 * \ingroup dataHandler
 */
class WDataSetScalar : public WDataSetSingle // NOLINT
{
public:
    /**
     * shared_ptr abbreviation
     */
    typedef std::shared_ptr< WDataSetScalar > SPtr;

    /**
     * const shared_ptr abbreviation
     */
    typedef std::shared_ptr< const WDataSetScalar > ConstSPtr;

    /**
     * Constructs an instance out of an appropriate value set and a grid.
     * Computes the maximum an minimum values stored as member variables.
     *
     * \param newValueSet the scalar value set to use
     * \param newGrid the grid which maps world space to the value set
     */
    WDataSetScalar( std::shared_ptr< WValueSetBase > newValueSet,
                    std::shared_ptr< WGrid > newGrid );

    /**
     * Construct an empty and unusable instance. This is needed for the prototype mechanism.
     */
    WDataSetScalar();

    /**
     * Destroys this DataSet instance
     */
    virtual ~WDataSetScalar();

    /**
     * Creates a copy (clone) of this instance but allows one to change the valueset. Unlike copy construction, this is a very useful function if you
     * want to keep the dynamic type of your dataset.
     *
     * \param newValueSet the new valueset.
     * \param newGrid the new grid.
     *
     * \return the clone
     */
    virtual WDataSetSingle::SPtr clone( std::shared_ptr< WValueSetBase > newValueSet, std::shared_ptr< WGrid > newGrid ) const;

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
     * Returns the largest of the scalars stored in the data set
     *
     * \return maximum value in dataset
     */
    double getMax() const;

    /**
     * Returns the smallest of the scalars stored in the data set
     *
     * \return minimum value in dataset
     */
    double getMin() const;

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
     * Returns the histogram of this dataset's valueset. If it does not exist yet, it will be created and cached. It does NOT make use of the
     * WValueSetHistogram down scaling feature even though the number of buckets might be lower than the default as the down scaling might
     * introduce errors. To use down-scaling, grab the default histogram and call WValueSetHistogram( getHistogram(), buckets ) manually.
     *
     * \param buckets the number of buckets inside the histogram.
     *
     * \return the histogram.
     */
    std::shared_ptr< const WValueSetHistogram > getHistogram( size_t buckets = 1000 );

    /**
     * Interpolate the value for the valueset at the given position.
     * If interpolation fails, the success parameter will be false
     * and the value returned zero.
     *
     * \param pos The position for which we would like to get a value.
     * \param success indicates whether the interpolation was successful
     *
     * \return Scalar value for that given position
     */
    double interpolate( const WPosition& pos, bool* success ) const;

    /**
     * Get the value stored at a certain grid position of the data set
     * \param x index in x direction
     * \param y index in y direction
     * \param z index in z direction
     *
     * \return the value at the grid position with the given index tuple.
     */
    template< typename T > T getValueAt( int x, int y, int z ) const;

    /**
     * Get the value stored at a certain grid position of the data set
     * \param x index in x direction
     * \param y index in y direction
     * \param z index in z direction
     *
     * \return the double the grid position with the given index tuple.
     */
    double getValueAt( int x, int y, int z ) const;

    /**
     * Get the value stored at a certain grid position of the data set
     * \param id
     *
     * \return the double the grid position with the given tuple.
     */
    double getValueAt( size_t id ) const;

    /**
     * Returns a prototype instantiated with the true type of the deriving class.
     *
     * \return the prototype.
     */
    static std::shared_ptr< WPrototyped > getPrototype();

    using WDataSetSingle::getSingleRawValue;

protected:
    /**
     * The prototype as singleton.
     */
    static std::shared_ptr< WPrototyped > m_prototype;

private:
    /**
     * The histograms for later use. Each histogram for a requested bucket count gets cached.
     **/
    std::map< size_t, std::shared_ptr< WValueSetHistogram > > m_histograms;

    /**
     * The lock used for securely creating m_histogram on demand.
     */
    boost::mutex m_histogramLock;
};

template< typename T > T WDataSetScalar::getValueAt( int x, int y, int z ) const
{
    std::shared_ptr< WValueSet< T > > vs = std::dynamic_pointer_cast< WValueSet< T > >( m_valueSet );
    std::shared_ptr< WGridRegular3D > grid = std::dynamic_pointer_cast< WGridRegular3D >( m_grid );

    size_t id = x + y * grid->getNbCoordsX() + z * grid->getNbCoordsX() * grid->getNbCoordsY();

    T v = vs->getScalar( id );
    return v;
}

#endif  // WDATASETSCALAR_H
