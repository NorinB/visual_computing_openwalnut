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

#include <string>

#include "WModuleFactory.h"

#include "WPrototypeRequirement.h"

WPrototypeRequirement::WPrototypeRequirement( std::string prototype ):
    WRequirement(),
    m_prototype( prototype )
{
    // initialize members
}

WPrototypeRequirement::~WPrototypeRequirement()
{
    // cleanup
}

bool WPrototypeRequirement::isComplied() const
{
    if( WModuleFactory::getModuleFactory()->isPrototypeAvailable( m_prototype ) )
    {
        WModule::SPtr proto = WModuleFactory::getModuleFactory()->getPrototypeByName( m_prototype );
        // NOTE: checkRequirements returns a pointer to the req which failed -> no fail -> NULL returned
        return ( proto->checkRequirements() == NULL );
    }
    return false;
}

std::string WPrototypeRequirement::getDescription() const
{
    return "Module depends upon the module \"" + m_prototype + "\".";
}

