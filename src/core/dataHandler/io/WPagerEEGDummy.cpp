//---------------------------------------------------------------------------
//
// Project: OpenWalnut ( http://www.openwalnut.org )
//
// Copyright 2022 OpenWalnut Community, BSV@Uni-Leipzig and CNCF@MPI-CBS
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

#include <clocale>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>


#include "WPagerEEGDummy.h"
#include "core/common/exceptions/WOutOfBounds.h"
#include "core/dataHandler/WEEGValueMatrix.h"
#include "core/dataHandler/WEEG.h"


WPagerEEGDummy::WPagerEEGDummy( const WEEGSegmentArray &data, std::string fileName )
    : WPagerEEG( fileName )
{
    WAssert( data.size() > 0, "No segments found." );
    WAssert( data[0].size() > 0, "No eletrodes found." );
    WAssert( data[0][0].size() > 0, "No values found." );
    m_nbChannels = data[0].size();
    m_nbSamples = data[0][0].size();

    m_values = std::make_shared<WEEGSimpleSegment>( data[0] );

    m_scales = std::vector<double>( m_nbChannels );
    for( size_t channelID = 0; channelID < m_nbChannels; ++channelID )
    {
        m_scales[channelID] = 1; // dummy value
    }
}

WPagerEEGDummy::~WPagerEEGDummy()
{
}

std::size_t WPagerEEGDummy::getNumberOfSegments() const
{
    return 1;
}

std::size_t WPagerEEGDummy::getNumberOfChannels() const
{
    return m_nbChannels;
}

std::size_t WPagerEEGDummy::getNumberOfSamples( std::size_t segmentID ) const
{
    if( segmentID != 0 )
    {
        std::ostringstream stream;
        stream << "Data has no segment number " << segmentID;
        throw WOutOfBounds( stream.str() );
    }

    return m_nbSamples;
}

std::shared_ptr< WEEGValueMatrix > WPagerEEGDummy::getValues( std::size_t segmentID, std::size_t start, std::size_t length ) const
{
    if( segmentID != 0 )
    {
        std::ostringstream stream;
        stream << getFilename() << " has no segment number " << segmentID;
        throw WOutOfBounds( stream.str() );
    }

    if( start + length > m_nbSamples )
    {
        std::ostringstream stream;
        stream << "Could not read sample number " << start + length - 1 << " of file " << getFilename()
               << ", it only has " << m_nbSamples << " samples";
        throw WOutOfBounds( stream.str() );
    }

    std::shared_ptr< WEEGValueMatrix > values( new WEEGValueMatrix( m_nbChannels, std::vector< double >( length ) ) );
    for( size_t channelID = 0; channelID < m_nbChannels; ++channelID )
    {
        for( size_t sampleID = 0; sampleID < length; ++sampleID )
        {
            (*values)[channelID][sampleID] = (*m_values)[channelID][start+sampleID];
        }
    }

    return values;
}

double WPagerEEGDummy::getSamplingRate() const
{
    return 1; // Dummy as we do not know the rate
}

std::string WPagerEEGDummy::getChannelUnit( std::size_t channelID ) const
{
    if( channelID >= m_nbChannels )
    {
        std::ostringstream stream;
        stream << getFilename() << " has no channel number " << channelID;
        throw WOutOfBounds( stream.str() );
    }

    return "unknown unit (not implemented)";
}

std::string WPagerEEGDummy::getChannelLabel( std::size_t channelID ) const
{
    if( channelID >= m_nbChannels )
    {
        std::ostringstream stream;
        stream << getFilename() << " has no channel number " << channelID;
        throw WOutOfBounds( stream.str() );
    }

    return "unknown label (not implemented)";
}

