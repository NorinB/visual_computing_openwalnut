//---------------------------------------------------------------------------
//
// Project: OpenWalnut ( http://www.openwalnut.org )
//
// Copyright 2013 OpenWalnut Community, BSV@Uni-Leipzig and CNCF@MPI-CBS
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

#ifndef WMPROJECTIONSASCONTEXT_H
#define WMPROJECTIONSASCONTEXT_H

#include <memory>
#include <string>

#include <osg/Geode>

#include "core/common/WItemSelection.h"
#include "core/common/WItemSelectionItem.h"
#include "core/common/WItemSelectionItemTyped.h"
#include "core/common/WItemSelector.h"
#include "core/common/WPropertyHelper.h"
#include "core/kernel/WModule.h"
#include "core/kernel/WModuleInputData.h"
#include "core/kernel/WModuleOutputData.h"

enum PlaneType
{
    NONE, MIP, COMPOSITING_F2B, COMPOSITING_B2F
};

// forward declarations to reduce compile dependencies
template< class T > class WModuleInputData;
class WDataSetScalar;
class WGEManagedGroupNode;
class WGEShader;

/**
 * Computes contour lines (aka isolines) for the given data and render them on a 2D plane.
 * \ingroup modules
 */
class WMProjectionsAsContext: public WModule
{
public:
    /**
     * Creates the module for drawing contour lines.
     */
    WMProjectionsAsContext();

    /**
     * Destroys this module.
     */
    virtual ~WMProjectionsAsContext();

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

    /**
     * Geode holding the planes
     */
    osg::ref_ptr< osg::Geode > m_geode;

private:
    /**
     * Input connector for scalar data.
     */
    std::shared_ptr< WModuleInputData< WDataSetScalar > > m_scalarIC;

    /**
     * The transfer function as an input data set
     */
    std::shared_ptr< WModuleInputData< WDataSetSingle > > m_transferFunction;

    /**
     * The OSG root node for this module. All other geodes or OSG nodes will be attached on this single node.
     */
    osg::ref_ptr< WGEManagedGroupNode > m_rootNode;

    /**
     * Needed for recreating the geometry, incase when resolution changes.
     */
    std::shared_ptr< WCondition > m_propCondition;

    /**
     * Typedef for plane orientation selection
     */
    typedef WItemSelectionItemTyped< PlaneType > MyItemType;

    /**
     * Plane orientation type selection.
     */
    std::shared_ptr< WItemSelection > m_possibleSelectionsUsingTypes;

    /**
     * Plane orientation type.
     */
    WPropSelection m_singleSelectionAxialTop;

    /**
     * Plane orientation type.
     */
    WPropSelection m_singleSelectionAxialBottom;

    /**
     * Plane orientation type.
     */
    WPropSelection m_singleSelectionCoronalTop;

    /**
     * Plane orientation type.
     */
    WPropSelection m_singleSelectionCoronalBottom;

    /**
     * Plane orientation type.
     */
    WPropSelection m_singleSelectionSagittalTop;

    /**
     * Plane orientation type.
     */
    WPropSelection m_singleSelectionSagittalBottom;

    /**
     * Threshold for early ray termination of DVR
     */
    WPropDouble   m_earlyRayTerminationAlpha;

    /**
     * Info property.
     */
    WPropPosition                m_maxCoordsPosition;

    /**
     * Info property.
     */
    WPropPosition                m_normalOut;

    /**
     * Info property.
     */
    WPropInt                    m_planeTypes[6];

    /**
     * Reference to shader object.
     */
    osg::ref_ptr< WGEShader >    m_shader;

    /**
     * The treated data set.
     */
    std::shared_ptr< WDataSetScalar > scalarData;
};

#endif  // WMPROJECTIONSASCONTEXT_H
