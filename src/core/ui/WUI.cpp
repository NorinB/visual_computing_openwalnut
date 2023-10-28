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

#include "../common/WConditionOneShot.h"
#include "../common/WFlag.h"
#include "WUI.h"

WUI::WUI( int argc, char** argv )
    : std::enable_shared_from_this< WUI >(),
      m_isInitialized( new WConditionOneShot(), false ),
      m_argc( argc ),
      m_argv( argv )
{
}

WUI::~WUI()
{
}

const WFlag< bool >& WUI::isInitialized() const
{
    return m_isInitialized;
}

