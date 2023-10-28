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

#ifndef WDATASETHISTOGRAM1D_H
#define WDATASETHISTOGRAM1D_H

#include <memory>
#include <string>
#include <vector>

#include "../common/WColor.h"
#include "../common/WHistogramBasic.h"
#include "WDataSet.h"

/**
 * This data set type contains a 1D histogram.
 * \ingroup dataHandler
 */
class WDataSetHistogram1D : public WDataSet // NOLINT
{
public:
    /**
     * shared_ptr abbreviation
     */
    typedef std::shared_ptr< WDataSetHistogram1D > SPtr;

    /**
     * const shared_ptr abbreviation
     */
    typedef std::shared_ptr< const WDataSetHistogram1D > ConstSPtr;

    /**
     * Creates a dataset encapsulating a histogram.
     * The histogram will be copied in order to prevent changes to the data.
     *
     * \param histo The histogram to use.
     */
    explicit WDataSetHistogram1D( std::shared_ptr< WHistogramBasic const > const& histo );

    /**
     * Construct a histogram and allows to set an array of colors used for the bins.
     *
     * \param histo The histogram.
     * \param colors An array of one color per bin.
     */
    WDataSetHistogram1D( std::shared_ptr< WHistogramBasic const > const& histo, std::shared_ptr< std::vector< WColor > const > const& colors );

    /**
     * Construct an empty and unusable instance. This is needed for the prototype mechanism.
     */
    WDataSetHistogram1D();

    /**
     * Destroys this DataSet instance
     */
    virtual ~WDataSetHistogram1D();

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
     * Returns the histogram.
     *
     * \return A const ref pointer to the histogram.
     */
    std::shared_ptr< WHistogramBasic const > const& getHistogram() const;

    /**
     * Returns a prototype instantiated with the true type of the deriving class.
     *
     * \return the prototype.
     */
    static std::shared_ptr< WPrototyped > getPrototype();

    /**
     * Whether this dataset has colors associated with the bins.
     *
     * \return true, if this dataset has colors.
     */
    bool hasColors() const;

    /**
     * Get the color of a bin.
     *
     * \param bin The index of the bin to get the color from.
     *
     * \return The color of the bin.
     */
    WColor getColor( std::size_t bin ) const;

protected:
    /**
     * The prototype as singleton.
     */
    static std::shared_ptr< WPrototyped > m_prototype;

private:
    //! The histogram.
    std::shared_ptr< WHistogramBasic const > const m_histogram;

    //! The colors for the bins.
    std::shared_ptr< std::vector< WColor > const > const m_colors;
};

#endif  // WDATASETHISTOGRAM1D_H

