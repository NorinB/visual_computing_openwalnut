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

#ifndef WEEGSEGMENT_H
#define WEEGSEGMENT_H

#include <cstddef>
#include <memory>


#include "WEEGValueMatrix.h"
#include "io/WPagerEEG.h"



/**
 * Class which contains one segment of an EEG recording, read from a WPagerEEG.
 * \ingroup dataHandler
 */
class WEEGSegment // NOLINT
{
public:
    /**
     * Constructor
     *
     * \param segmentID number of this segment
     * \param pager pager class which contains the data, read from a file on
     *              demand
     */
    WEEGSegment( std::size_t segmentID, std::shared_ptr< WPagerEEG > pager );

    /**
     * Get the number of samples this segment consists of.
     *
     * \return number of samples
     */
    std::size_t getNumberOfSamples() const;

    /**
     * Get the values of all channels for a given sample range.
     *
     * \param start start sample of the sample range
     * \param length length of the sample range
     * \return matrix of values
     */
    std::shared_ptr< WEEGValueMatrix > getValues( std::size_t start, std::size_t length ) const;

protected:
private:
    std::size_t m_segmentID; //!< number of this segment
    std::shared_ptr< WPagerEEG > m_pager; //!< pager class which contains the data, read from a file on demand
    std::size_t m_nbSamples; //!< number of samples this segment consists of
};

#endif  // WEEGSEGMENT_H
