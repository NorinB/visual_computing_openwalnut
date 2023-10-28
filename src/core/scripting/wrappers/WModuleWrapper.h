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

#ifndef WMODULEWRAPPER_H
#define WMODULEWRAPPER_H

#include <memory>
#include <string>


#include "WInputConnectorWrapper.h"
#include "WOutputConnectorWrapper.h"
#include "WPropertyGroupWrapper.h"
#include "core/kernel/WModule.h"

/**
 * \class WModuleWrapper
 *
 * A wrapper for a module. This is used to expose a part of the WModule functionality
 * to script interpreters.
 */
class WModuleWrapper
{
public:
    /**
     * Constructor.
     *
     * \param module The actual module.
     */
    explicit WModuleWrapper( std::shared_ptr< WModule > module );

    /**
     * Destructor.
     */
    ~WModuleWrapper();

    /**
     * Get the name of the module.
     *
     * \return The name of the module.
     */
    std::string getName() const;

    /**
     * Get the description of the module.
     *
     * \return The description.
     */
    std::string getDescription() const;

    /**
     * Returns the module pointer. Useful to other wrapper classes.
     *
     * \return The module pointer.
     */
    std::shared_ptr< WModule > getModulePtr();

    /**
     * Returns a WPropertyGroupWrapper containing the module's properties. To be used in scripts.
     *
     * \return The module's properties.
     */
    WPropertyGroupWrapper getProperties();

    /**
     * Returns a WPropertyGroupWrapper containing the module's info properties. To be used in scripts.
     *
     * \return The module's properties.
     */
    WPropertyGroupWrapper getInformationProperties();

    /**
     * Get an input connector by name.
     *
     * \param name The name of the connector.
     * \return The retrieved connector.
     */
    WInputConnectorWrapper getInputConnector( std::string const& name );

    /**
     * Get an output connector by name.
     *
     * \param name The name of the connector.
     * \return The retrieved connector.
     */
    WOutputConnectorWrapper getOutputConnector( std::string const& name );

private:
    //! A pointer to the module.
    std::shared_ptr< WModule > m_module;
};

#endif  // WMODULEWRAPPER_H
