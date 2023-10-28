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

#ifndef WFIBERACCUMULATOR_H
#define WFIBERACCUMULATOR_H

#include <memory>
#include <vector>

#include <boost/thread.hpp>

#include "../common/math/linearAlgebra/WVectorFixed.h"
#include "WDataSetFiberVector.h"
#include "WDataSetFibers.h"


/**
 * A class that encapsulates the data needed to construct a WDataSetFibers.
 */
class WFiberAccumulator        // NOLINT
{
public:
    /**
     * Constructor.
     */
    WFiberAccumulator();

    /**
     * Destructor.
     */
    virtual ~WFiberAccumulator();

    /**
     * Add a fiber to the dataset.
     *
     * \param in The fiber to add, stored as a vector of Positions.
     *
     * This function is threadsafe.
     */
    void add( std::vector< WVector3d > const& in );

    /**
     * Return the dataset that has been accumulated to this point
     * and start a new dataset.
     *
     * \return A shared_ptr pointing to the WDataSetFibers that has been accumulated.
     *
     * The returned shared_ptr is the sole owner of the WDataSetFibers.
     */
    std::shared_ptr< WDataSetFibers > buildDataSet();

    /**
     * Clears all data.
     */
    void clear();

protected:
private:
    /**
     * A mutex needed to guarantee thread-safety.
     */
    boost::mutex m_fiberMutex;

    /**
     * One of the vectors needed to construct a WDataSetFibers.
     * Stores the points in a vector of floats.
     */
    std::shared_ptr< std::vector< float > > m_points;

    /**
     * One of the vectors needed to construct a WDataSetFibers.
     * Stores the starting indices (refering to the points vector) of the fibers.
     */
    std::shared_ptr< std::vector< size_t > > m_fiberIndices;

    /**
     * One of the vectors needed to construct a WDataSetFibers.
     * Stores the length of the fibers.
     */
    std::shared_ptr< std::vector< size_t > > m_fiberLengths;

    /**
     * One of the vectors needed to construct a WDataSetFibers.
     * Stores information about what fiber a point in the points vector refers to.
     */
    std::shared_ptr< std::vector< size_t > > m_pointToFiber;
};

#endif  // WFIBERACCUMULATOR_H
