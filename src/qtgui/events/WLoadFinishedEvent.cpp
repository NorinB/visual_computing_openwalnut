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

#include <vector>
#include <string>

#include "WEventTypes.h"

#include "WLoadFinishedEvent.h"

WLoadFinishedEvent::WLoadFinishedEvent( boost::filesystem::path filename, std::vector< std::string > errors, std::vector< std::string > warnings )
    : QEvent( static_cast< QEvent::Type >( WQT_LOADFINISHED ) ),
    m_filename( filename ),
    m_errors( errors ),
    m_warnings( warnings )
{
    // initialize members
}

WLoadFinishedEvent::~WLoadFinishedEvent()
{
    // cleanup
}

const std::vector< std::string >& WLoadFinishedEvent::getErrors() const
{
    return m_errors;
}

const std::vector< std::string >& WLoadFinishedEvent::getWarnings() const
{
    return m_warnings;
}

std::string WLoadFinishedEvent::getFilename() const
{
    return m_filename.string();
}

