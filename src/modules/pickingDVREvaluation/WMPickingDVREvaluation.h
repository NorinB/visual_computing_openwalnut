//---------------------------------------------------------------------------
//
// Project: OpenWalnut ( http://www.openwalnut.org )
//
// Copyright 2017 OpenWalnut Community
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

#ifndef WMPICKINGDVREVALUATION_H
#define WMPICKINGDVREVALUATION_H

#include <memory>
#include <string>

#include <osg/Geode>

#include "core/kernel/WModule.h"
#include "core/kernel/WModuleInputData.h"

// forward declarations to reduce compile dependencies
class WDataSetScalar;

/**
 * Evaluate different picking techniques with regard to certain metrics.
 * Developed for paper: https://doi.org/10.1109/TVCG.2018.2848906
 *
 * \ingroup modules
 */
class WMPickingDVREvaluation: public WModule
{
public:
    /**
     * A simple constructor
     */
    WMPickingDVREvaluation();

    /**
     * A simple destructor
     */
    virtual ~WMPickingDVREvaluation();

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
    /**
     * Needed for recreating the geometry, incase when resolution changes.
     */
    std::shared_ptr< WCondition > m_propCondition;

    /**
     * The viewing and thus projection direction.
     */
    WPropPosition   m_viewDirection;

    /**
     * Number of samples along the ray
     */
    WPropInt m_sampleSteps;

    /**
     * Number of samples for evaluating Delta_vi
     */
    WPropInt m_samplesEval;

    /**
     * Current picking method
     */
    WPropSelection m_pickingCriteriaCur;

    /**
     * Possible criteria
     */
    std::shared_ptr< WItemSelection > m_pickingCriteriaList;

    /**
     * Current importance function
     */
    WPropSelection m_importanceFunctionCur;

    /**
     * Possible importance functions
     */
    std::shared_ptr< WItemSelection > m_impFuncList;

    /**
     * Input connector for scalar data.
     */
    std::shared_ptr< WModuleInputData< WDataSetScalar > > m_scalarData;

    /**
     * The transfer function as an input data set
     */
    std::shared_ptr< WModuleInputData< WDataSetSingle > > m_transferFunction;

    WBoundingBox m_bbox; //!< Bounding box of the treated data set.
    std::shared_ptr< WDataSetScalar > m_scalarDataSet; //!< Input data as WDataSetScalar.
    std::shared_ptr< WDataSetSingle > m_transferFunctionData; //!< Transfer function as WDataSetSingle.

    /**
     * Get position where a given ray intersects a given axis-aligned bounding box.
     * \param bbox The given bounding box
     * \param origin Starting point of the ray
     * \param dir Direction of the ray
     *
     * \result Intersection position. (0,0,0) if no intersection.
     */
    WPosition intersectBoundingBoxWithRay( const WBoundingBox& bbox, const WPosition& origin, const WVector3d& dir );

    /**
     * Importance function
     * \param pos Location in space.
     *
     * \return Importance at \p pos
     */
    double importance( WPosition pos );

    /**
     * interaction Map of directness model. Here: DVR.
     * \param startPos Location in space where interaction takes place.
     * \param viewDir Viewing direction, i.e. direction interaction.
     *
     * \return Result of mapping \p startPos
     */
    WPosition interactionMapping( const WPosition& startPos, const WVector3d& viewDir );

    /**
     * viusalization mapping of directness model. Here: Picking.
     * \param pos Location of data point in space.
     * \param viewDir Viewing direction, i.e. direction of projection.
     *
     * \return Result of mapping \p pos
     */
    WPosition visualizationMapping( const WPosition& pos, const WVector3d& viewDir );
};

#endif  // WMPICKINGDVREVALUATION_H
