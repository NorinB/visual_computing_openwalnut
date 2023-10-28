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

#include <cstddef>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>


#include "../common/exceptions/WOutOfBounds.h"
#include "WEEGSegment.h"
#include "WEEG.h"
#include "WEEGChannelInfo.h"
#include "WEEGPositionsLibrary.h"
#include "exceptions/WDHException.h"
#include "io/WPagerEEG.h"
#include "io/WPagerEEGDummy.h"


std::shared_ptr< WPrototyped > WEEG::m_prototype = std::shared_ptr< WPrototyped >();

WEEG::WEEG( std::shared_ptr< WPagerEEG > pager, std::shared_ptr< WEEGPositionsLibrary > positionsLibrary )
{
    init( pager, positionsLibrary );
}

WEEG::WEEG( const WEEGSegmentArray &data,
              const WEEGElectrodeLibrary &electrodeLib,
              const WEEGChannelLabels &channelLabels,
              const std::string filename )
    : WRecording()
{
    assert( data.size() <= WRecording::MAX_RECORDING_SEGMENTS );
    assert( data.size() > 0 );  // ensure that there is really data
    for( WEEGSegmentArray::const_iterator it1 = data.begin(); it1 != data.end(); ++it1 )
    {
        assert( it1->size() <= WRecording::MAX_RECORDING_CHANNELS );
        assert( it1->size() > 0 );  // ensure that there is really data
        for( WEEGSimpleSegment::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2 )
        {
            assert( it2->size() <= WRecording::MAX_RECORDING_SAMPLES );
            assert( it2->size() > 0 );  // ensure that there is really data
        }
    }

    std::map< std::string, WPosition > positionsMap;
    for( size_t id = 0; id < channelLabels.size(); ++id )
    {
        if( id < electrodeLib.size() )
        {
            positionsMap[channelLabels[id].first] = electrodeLib[id].getPosition();
        }
        else
        {
            positionsMap[channelLabels[id].first] = WPosition();
        }
    }
    std::shared_ptr< WEEGPositionsLibrary > positionsLibrary = std::make_shared< WEEGPositionsLibrary >( positionsMap );
    std::shared_ptr< WPagerEEG > pager = std::make_shared<WPagerEEGDummy>( data, filename );
    init( pager, positionsLibrary );
}

void WEEG::init( std::shared_ptr< WPagerEEG > pager, std::shared_ptr< WEEGPositionsLibrary > positionsLibrary )
{
    if( !pager )
    {
        throw WDHException( std::string( "Couldn't construct new EEG: pager invalid" ) );
    }

    if( !positionsLibrary )
    {
        throw WDHException( std::string( "Couldn't construct new EEG: positions library invalid" ) );
    }

    std::size_t nbSegments = pager->getNumberOfSegments();
    if( nbSegments <= 0 || WRecording::MAX_RECORDING_SEGMENTS < nbSegments )
    {
        throw WDHException( std::string( "Couldn't construct new EEG: invalid number of segments" ) );
    }

    std::size_t nbChannels = pager->getNumberOfChannels();
    if( nbChannels <= 0 || WRecording::MAX_RECORDING_CHANNELS < nbChannels )
    {
        throw WDHException( std::string( "Couldn't construct new EEG: invalid number of channels" ) );
    }

    m_samplingRate = pager->getSamplingRate();
    if( m_samplingRate <= 0.0 || WRecording::MAX_RECORDING_SAMPLING_FREQUENCY < m_samplingRate )
    {
        throw WDHException( std::string( "Couldn't construct new EEG: invalid sampling rate" ) );
    }

    setFilename( pager->getFilename() );

    m_segments.reserve( nbSegments );
    for( std::size_t segmentID = 0; segmentID < nbSegments; ++segmentID )
    {
        m_segments.push_back( std::shared_ptr< WEEGSegment >( new WEEGSegment( segmentID, pager ) ) );
    }

    m_channelInfos.reserve( nbChannels );
    for( std::size_t channelID = 0; channelID < nbChannels; ++channelID )
    {
        m_channelInfos.push_back( std::shared_ptr< WEEGChannelInfo >( new WEEGChannelInfo( channelID, pager, positionsLibrary ) ) );
    }
    m_infoProperties->addProperty( "Segments", "The number of segments", static_cast< WPVBaseTypes::PV_INT >( nbSegments ) );
    m_infoProperties->addProperty( "Channels", "The number of channels", static_cast< WPVBaseTypes::PV_INT >( nbChannels ) );
    m_infoProperties->addProperty( "Sampling rate", "Sampling rate of the recording", static_cast< WPVBaseTypes::PV_DOUBLE >( m_samplingRate ) );
}

WEEG::WEEG()
{
}

std::size_t WEEG::getNumberOfSegments() const
{
    return m_segments.size();
}

std::size_t WEEG::getNumberOfChannels() const
{
    return m_channelInfos.size();
}

double WEEG::getSamplingRate() const
{
    return m_samplingRate;
}

std::shared_ptr< WEEGSegment > WEEG::getSegment( std::size_t segmentID ) const
{
    if( segmentID >= m_segments.size() )
    {
        std::ostringstream stream;
        stream << "The EEG has no segment number " << segmentID;
        throw WOutOfBounds( stream.str() );
    }

    return m_segments[segmentID];
}

std::shared_ptr< WEEGChannelInfo > WEEG::getChannelInfo( std::size_t channelID ) const
{
    if( channelID >= m_channelInfos.size() )
    {
        std::ostringstream stream;
        stream << "The EEG has no channel number " << channelID;
        throw WOutOfBounds( stream.str() );
    }

    return m_channelInfos[channelID];
}

const std::string WEEG::getName() const
{
    return "WEEG";
}

const std::string WEEG::getDescription() const
{
    return "Contains EEG data";
}

std::shared_ptr< WPrototyped > WEEG::getPrototype()
{
    if( !m_prototype )
    {
        m_prototype = std::shared_ptr< WPrototyped >( new WEEG() );
    }

    return m_prototype;
}


WEEGElectrodeObject::WEEGElectrodeObject( WPosition position ):
    m_position( position )
{
}

WPosition WEEGElectrodeObject::getPosition() const
{
    return m_position;
}
