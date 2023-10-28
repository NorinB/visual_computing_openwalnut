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

#ifndef WMREADSPHERICALHARMONICS_H
#define WMREADSPHERICALHARMONICS_H

#include <memory>
#include <string>

#include <osg/Geode>

#include "core/dataHandler/WDataSetSphericalHarmonics.h"
#include "core/kernel/WModule.h"
#include "core/kernel/WModuleInputData.h"
#include "core/kernel/WModuleOutputData.h"

/**
 * This module loads spherical harmonics data given as vectors of coefficients from NIfTI files.
 *
 * \ingroup modules
 */
class WMReadSphericalHarmonics: public WModule
{
public:
    /**
     * Standard constructor
     */
    WMReadSphericalHarmonics();

    /**
     * Destructor
     */
    virtual ~WMReadSphericalHarmonics();

    /**
     * Gives back the name of this module.
     * \return the module's name.
     */
    virtual const std::string getName() const;

    /**
     * Gives back a description of this module.
     * \return description to module.
     */
    virtual const std::string getDescription() const;

    /**
     * Due to the prototype design pattern used to build modules, this method returns a new instance of this method. NOTE: it
     * should never be initialized or modified in some other way. A simple new instance is required.
     *
     * \return the prototype used to create every module in OpenWalnut.
     */
    virtual std::shared_ptr< WModule > factory() const;

protected:
    /**
     * Entry point after loading the module. Runs in separate thread.
     */
    virtual void moduleMain();

    /**
     * Initialize the connectors this module is using.
     */
    virtual void connectors();

    /**
     * Initialize the properties for this module.
     */
    virtual void properties();

    /**
     * Initialize requirements for this module.
     */
    virtual void requirements();


private:
    std::shared_ptr< WModuleOutputData< WDataSetSphericalHarmonics > > m_output; //!< Ouput connector provided by this module.

    std::shared_ptr< WDataSetSphericalHarmonics > m_data; //!< This triangle mesh is provided as output through the connector.
    std::shared_ptr< WCondition > m_propCondition;  //!< A condition used to notify about changes in several properties.
    WPropTrigger m_readTriggerProp; //!< This property triggers the actual reading,
    WPropFilename m_dataFile; //!< The data will be read from this file.
};

#endif  // WMREADSPHERICALHARMONICS_H
