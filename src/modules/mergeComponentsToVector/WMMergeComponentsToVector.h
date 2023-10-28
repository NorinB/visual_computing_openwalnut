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

#ifndef WMMERGECOMPONENTSTOVECTOR_H
#define WMMERGECOMPONENTSTOVECTOR_H

#include <memory>
#include <string>

#include "core/dataHandler/WDataSetScalar.h"
#include "core/dataHandler/WDataSetVector.h"
#include "core/kernel/WModule.h"
#include "core/kernel/WModuleInputData.h"
#include "core/kernel/WModuleOutputData.h"

/**
 * This modules takes several scalar inputs and merges them to a vector dataset
 *
 * \ingroup modules
 */
class WMMergeComponentsToVector: public WModule
{
public:
    /**
     * Default constructor.
     */
    WMMergeComponentsToVector();

    /**
     * Destructor.
     */
    virtual ~WMMergeComponentsToVector();

    /**
     * Gives back the name of this module.
     * \return the module's name.
     */
    virtual const std::string getName() const;

    /**
     * Provide description.
     *
     * \return the description
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

private:
    /**
     * An input connector used to get datasets from other modules. The connection management between connectors must not be handled by the module.
     */
    std::shared_ptr< WModuleInputData< WDataSetScalar > > m_scalarInX;

    /**
     * An input connector used to get datasets from other modules. The connection management between connectors must not be handled by the module.
     */
    std::shared_ptr< WModuleInputData< WDataSetScalar > > m_scalarInY;

    /**
     * An input connector used to get datasets from other modules. The connection management between connectors must not be handled by the module.
     */
    std::shared_ptr< WModuleInputData< WDataSetScalar > > m_scalarInZ;

    /**
     * The output connector used to provide the calculated data to other modules.
     */
    std::shared_ptr< WModuleOutputData< WDataSetVector > > m_vectorOut;

    /**
     * A condition used to notify about changes in several properties.
     */
    std::shared_ptr< WCondition > m_propCondition;
};

#endif  // WMMERGECOMPONENTSTOVECTOR_H

