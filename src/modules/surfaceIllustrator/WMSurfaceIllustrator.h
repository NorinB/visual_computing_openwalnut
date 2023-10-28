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

#ifndef WMSURFACEILLUSTRATOR_H
#define WMSURFACEILLUSTRATOR_H

#include <memory>
#include <string>

#include <osg/Uniform>

#include "core/common/datastructures/WColoredVertices.h"
#include "core/common/math/linearAlgebra/WVectorFixed.h"
#include "core/graphicsEngine/WGEManagedGroupNode.h"
#include "core/kernel/WModule.h"
#include "core/kernel/WModuleInputData.h"
#include "core/kernel/WModuleOutputData.h"


class WTriangleMesh;
class WGEShader;

/**
 * This module renders the triangle mesh given at its input connector
 * as a surface.
 *
 * \ingroup modules
 */
class WMSurfaceIllustrator: public WModule
{
public:
    /**
     * Constructor. Creates the module skeleton.
     */
    WMSurfaceIllustrator();

    /**
     * Destructor.
     */
    virtual ~WMSurfaceIllustrator();

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

private:
    /**
     * Calculates the bounding box of a vector and increases the specified one if needed.
     *
     * \param minX old maximum X and gets overwritten by new one
     * \param maxX old maximum Y and gets overwritten by new one
     * \param minY old minimum Z and gets overwritten by new one
     * \param maxY old maximum X and gets overwritten by new one
     * \param minZ old maximum Y and gets overwritten by new one
     * \param maxZ old maximum Z and gets overwritten by new one
     * \param vector the new vector to include in bbox calculation.
     */
    void updateMinMax( double& minX, double& maxX, double& minY, double& maxY, double& minZ, double& maxZ, const osg::Vec3d& vector ) const;

    /**
     * Gets the median of three values.
     *
     * \param x first value
     * \param y second value
     * \param z third value
     *
     * \return the median of x,y,z
     */
    double getMedian( double x, double y, double z ) const;

    /**
     * Center of the mesh. Needed  for applying transformation with the mesh in (0,0,0).
     */
    WVector3d m_meshCenter;

    /**
     * Group for all color and colormapping options.
     */
    WPropGroup m_coloringGroup;

    /**
     * Turn Colormapping on/off
     */
    WPropBool m_colormap;

    /**
     * Set center of selected surface parameter
     */
    WPropDouble m_parameterCenter;

    /**
     * Set width of selected surface parameter interval
     */
    WPropDouble m_parameterWidth;

    /**
     * Select the type of illustration applied in the shader
     */
    WPropSelection m_illustrationMode;

    /**
     * A condition used to notify about changes in several properties.
     */
    std::shared_ptr< WCondition > m_propCondition;

    /**
     * An input connector used to get meshes from other modules. The connection management between connectors must not be handled by the module.
     */
    std::shared_ptr< WModuleInputData< WTriangleMesh > > m_meshInput;

    /**
     * A map for mapping each vertex to a color.
     */
    std::shared_ptr< WModuleInputData< WColoredVertices > > m_colorMapInput;

    /**
     * A group wich contains all transformation tools.
     */
    WPropGroup m_groupTransformation;

    /**
     * Set the transformation tool to default
     */
    WPropTrigger  m_setDefault;

    /**
     * Render the mesh
     *
     * \param mesh The mesh to be rendered.
     */
    void renderMesh( std::shared_ptr< WTriangleMesh > mesh );
    /**
     * OSG Uniform for the transformation matrix which transforms the mesh. Needed for the colormapper
    */
    osg::ref_ptr< osg::Uniform > m_colorMapTransformation;

    /**
     * The mesh's opacity value.
     */
    WPropDouble m_opacity;

    /**
     * Toggle showing outline instead fo surface.
     */
    WPropBool m_showOutline;

    /**
     * The color of the mesh to be rendered.
     */
    WPropColor m_color;

    /**
     * Which colormode should be used?
     */
    WPropSelection m_colorMode;

    WPropInt m_nbTriangles; //!< Info-property showing the number of triangles in the mesh.
    WPropInt m_nbVertices; //!< Info-property showing the number of vertices in the mesh.

    /**
     * The node containing all geometry nodes.
     */
    WGEManagedGroupNode::SPtr m_moduleNode;

    /**
     * The shader for the mesh
     */
    osg::ref_ptr< WGEShader > m_shader;
};

#endif  // WMSURFACEILLUSTRATOR_H
