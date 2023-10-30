//---------------------------------------------------------------------------
//
// Project: OpenWalnut ( http://www.openwalnut.org )
//
// Copyright 2013-2023 OpenWalnut Community, Hochschule Coburg, Hochschul Worms
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

#ifndef WMTHRESHOLDINGEXAMPLE_H
#define WMTHRESHOLDINGEXAMPLE_H

#include <string>

#include "core/kernel/WModule.h"
#include "core/graphicsEngine/shaders/WGEShader.h"

// forward declarations to reduce compile dependencies
template< class T > class WModuleInputData;
class WDataSetScalar;
class WGEManagedGroupNode;

/**
 * Should draw values above some threshold.
 * \ingroup modules
 */
class WMThresholdingExample: public WModule
{
public:
    /**
     * Creates the module.
     */
    WMThresholdingExample();

    /**
     * Destroys this module.
     */
    virtual ~WMThresholdingExample();

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

    /**
     * Get the icon for this module in XPM format.
     *
     * \return The icon.
     */
    virtual const char** getXPMIcon() const;

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
     * Input connector for scalar data.
     */
    std::shared_ptr< WModuleInputData< WDataSetScalar > > m_scalarIC;

    /**
     * The OSG root node for this module. All other geodes or OSG nodes will be attached on this single node.
     */
    osg::ref_ptr< WGEManagedGroupNode > m_rootNode;

    /**
     * Needed for recreating the geometry, incase when resolution changes.
     */
    std::shared_ptr< WCondition > m_propCondition;

    /**
     * Threshold that needs to be crossed to be counted towards the internal counter
    */
    WPropDouble threshold;

    /**
     * Counter for points, that are above a threshold
    */
    int counter;

    /**
     * Current Scalar
    */
    std::shared_ptr< WDataSetScalar > currentDataSet;

    /**
     * The geometry rendered by this module.
     */
    osg::ref_ptr< osg::Geode > m_geode;

    /**
     * We want some nice shading effects, so we need a nice shader.
     */
    WGEShader::RefPtr m_shader;
};

#endif  // WMTHRESHOLDINGEXAMPLE_H
