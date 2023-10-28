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

#ifndef WMDATACREATORVECTOR_H
#define WMDATACREATORVECTOR_H

#include <memory>
#include <string>

#include "WDataSetSingleCreatorInterface.h"
#include "core/common/WObjectNDIP.h"
#include "core/common/WStrategyHelper.h"
#include "core/dataHandler/WDataHandlerEnums.h"
#include "core/dataHandler/WDataSetVector.h"
#include "core/dataHandler/WValueSetBase.h"
#include "core/kernel/WModule.h"
#include "core/kernel/WModuleOutputData.h"

/**
 * Module which utilizes the strategy pattern to provide a multitude of dataset creation algorithms for vector data.
 *
 * \ingroup modules
 */
class WMDataCreatorVector: public WModule
{
public:
    /**
     * Standard constructor.
     */
    WMDataCreatorVector();

    /**
     * Destructor.
     */
    ~WMDataCreatorVector();

    /**
     * Gives back the name of this module.
     * \return the module's name.
     */
    virtual const std::string getName() const;

    /**
     * Gives back a description of this module.
     * \return description of module.
     */
    virtual const std::string getDescription() const;

    /**
     * Due to the prototype design pattern used to build modules, this method returns a new instance of this method. NOTE: it
     * should never be initialized or modified in some other way. A simple new instance is required.
     *
     * \return the prototype used to create every module in OpenWalnut.
     */
    virtual std::shared_ptr< WModule > factory() const;

    /**
     * Define the interface which is injected into an WObjectNDIP.
     */
    class DataCreatorInterface
    {
    public:
        /**
         * Create the dataset. This needs to be implemented by all the creators you write.
         *
         * \param progress the progress instance you should increment each time you fill the value for one voxel.
         * \param grid the grid on which the value set has to be build
         * \param type the value type in the value set
         *
         * \return the value set for the given grid
         */
        virtual WValueSetBase::SPtr operator()( WProgress::SPtr progress, WGridRegular3D::ConstSPtr grid, dataType type = W_DT_FLOAT ) = 0;

        /**
         * Destructor
         */
        virtual ~DataCreatorInterface()
        {
        }
    };

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
     * A condition used to notify about changes in several properties.
     */
    std::shared_ptr< WCondition > m_propCondition;

    std::shared_ptr< WModuleOutputData< WDataSetVector > > m_output; //!< The only output of this module.


    WPropInt m_nbVoxelsX; //!< number of voxels in x direction
    WPropInt m_nbVoxelsY; //!< number of voxels in y direction
    WPropInt m_nbVoxelsZ; //!< number of voxels in z direction

    WPropPosition m_origin; //!< where to put the origin
    WPropPosition m_size; //!< where to put the origin

    WPropSelection m_valueType; //!< the datatype of the valueset

    WStrategyHelper< WObjectNDIP< WDataSetSingleCreatorInterface > > m_strategy; //!< the strategy currently active.
};

#endif  // WMDATACREATORVECTOR_H
