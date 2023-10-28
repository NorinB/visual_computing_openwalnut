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

#ifndef WEEG_H
#define WEEG_H

#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>


#include "WEEGSegment.h"
#include "WEEGChannelInfo.h"
#include "WEEGPositionsLibrary.h"
#include "WRecording.h"
#include "io/WPagerEEG.h"


/**
 * An incomplete implementation to store information about electrodes of EEG data. Taken from old WEEG1
 */
class WEEGElectrodeObject // NOLINT
{
public:
    /**
     * Contructor taking the position of the elctrode.
     * \param position The position of the electrode in world space.
     */
    explicit WEEGElectrodeObject( WPosition position );

    /**
     * Returns the position of the electrode.
     * \return The position of the electrode.
     */
    WPosition getPosition() const;
protected:
private:
    WPosition m_position; //!< Position of the electrode in space
};


typedef std::vector< double > WEEGElectrode; // Type taken from the old WEEG1
typedef std::vector< WEEGElectrode > WEEGSimpleSegment; // Type taken from the old WEEG1
typedef std::vector< WEEGSimpleSegment > WEEGSegmentArray; // Type taken from the old WEEG1

typedef std::vector< WEEGElectrodeObject > WEEGElectrodeLibrary; // Type taken from the old WEEG1
typedef std::vector< std::pair< std::string, std::string > > WEEGChannelLabels; // Type taken from the old WEEG1
/**
 * Class which contains EEG recording data, read from a WPagerEEG.
 * \ingroup dataHandler
 */
class WEEG : public WRecording // NOLINT
{
public:
    /**
     * Constructor
     *
     * \param pager pager class which contains the data, read from a file on
     *              demand
     * \param positionsLibrary class which contains the positions of the
     *                         electrodes
     */
    WEEG( std::shared_ptr< WPagerEEG > pager, std::shared_ptr< WEEGPositionsLibrary > positionsLibrary );

    /**
     * Constructs a WEEG object in the way of the old WEEG1 from the give infos.
     * \param data Array of segments
     * \param electrodeLib Information about the electrodes
     * \param channelLabels The names of the channels.
     * \param filename The name of the file the data came from.
     */
     WEEG( const WEEGSegmentArray& data,
                   const WEEGElectrodeLibrary& electrodeLib,
                   const WEEGChannelLabels& channelLabels,
                   const std::string filename );

    /**
     * Supports construction of a WEEG object from the give infos.
     * \param pager pager class which contains the data, read from a file on
     *              demand
     * \param positionsLibrary class which contains the positions of the
     *                         electrodes
     */
    void init( std::shared_ptr< WPagerEEG > pager, std::shared_ptr< WEEGPositionsLibrary > positionsLibrary );


    /**
     * Constructor creating a quite unusable instance. Useful for prototype
     * mechanism.
     */
    WEEG();

    /**
     * Get the number of segments this EEG consists of.
     *
     * \return number of segments
     */
    std::size_t getNumberOfSegments() const;

    /**
     * Get the number of channels this EEG has.
     *
     * \return number of channels
     */
    std::size_t getNumberOfChannels() const;

    /**
     * Get the sampling rate used by the recording.
     *
     * \return sampling rate
     */
    double getSamplingRate() const;

    /**
     * Get one segment.
     *
     * \param segmentID number of segment
     * \return segment
     */
    std::shared_ptr< WEEGSegment > getSegment( std::size_t segmentID ) const;

    /**
     * Get one channel info object.
     *
     * \param channelID number of channel
     * \return object containing information about the channel
     */
    std::shared_ptr< WEEGChannelInfo > getChannelInfo( std::size_t channelID ) const;

    /**
     * Return the name of the dataset
     *
     * \return the name
     */
    virtual const std::string getName() const;

    /**
     * Description of dataset.
     *
     * \return description of dataset
     */
    virtual const std::string getDescription() const;

    /**
     * Get dataset prototype.
     *
     * \return the prototype
     */
    static std::shared_ptr< WPrototyped > getPrototype();

protected:
    /**
     * Prototype needed to allow the EEG dataset to be transferred.
     */
    static std::shared_ptr< WPrototyped > m_prototype;

private:
    double m_samplingRate; //!< sampling rate used by the recording

    std::vector< std::shared_ptr< WEEGSegment > > m_segments; //!< list of all segments this EEG consists of

    std::vector< std::shared_ptr< WEEGChannelInfo > > m_channelInfos; //!< list of the information about all channel infos this EEG has
};

#endif  // WEEG_H
