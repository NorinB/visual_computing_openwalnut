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

#ifndef WPROTOTYPEREQUIREMENT_H
#define WPROTOTYPEREQUIREMENT_H

#include <string>

#include "../common/WRequirement.h"

/**
 * This requirement ensures that the specified prototype exists in the factory. These requirements are especially useful for container modules.
 * It also checks the requirements of the specified prototype.
 */
class  WPrototypeRequirement: public WRequirement // NOLINT
{
public:
    /**
     * Create instance. If your module uses this requirement, it needs the specified module.
     *
     * \param prototype the module needed.
     */
    explicit WPrototypeRequirement( std::string prototype );

    /**
     * Destructor.
     */
    virtual ~WPrototypeRequirement();

    /**
     * Checks if the requirement is fulfilled on the system. Implement this for your specific case.
     *
     * \return true if the specific requirement is fulfilled.
     */
    virtual bool isComplied() const;

    /**
     * Return a nice description of the requirement.
     *
     * \return the description.
     */
    virtual std::string getDescription() const;

protected:
private:
    /**
     * The required prototype.
     */
    std::string m_prototype;
};

#endif  // WPROTOTYPEREQUIREMENT_H

