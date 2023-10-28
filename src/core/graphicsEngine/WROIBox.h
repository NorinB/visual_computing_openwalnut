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

#ifndef WROIBOX_H
#define WROIBOX_H

#include <memory>
#include <shared_mutex>
#include <string>
#include <utility>

#include <boost/thread.hpp>
#include <osg/Geometry>

#include "WPickHandler.h"
#include "WPickHandler3D.h"
#include "WROI.h"
#include "shaders/WGEShader.h"

/**
 * Forward declaration of WGEViewer.
 */
class WGEViewer;

/**
 * A box representing a region of interest.
 */
class WROIBox : public WROI
{
public:
    /**
     * Yields box with desired extremal points minPos and maxPos
     * \param minPos Left, lower, front corner. Minimal x, y and z coordinates.
     * \param maxPos Right, upper, back corner. Maximal x, y and z coordinates.
     */
    WROIBox(  WPosition minPos, WPosition maxPos );

    /**
     * Destructor
     */
    virtual ~WROIBox();

    /**
     * Get the corner of the box that has minimal x, y and z values
     *
     * \return the corner position
     */
    WPosition getMinPos() const;

    /**
     * Get the corner of the box that has maximal x, y and z values
     *
     * \return the corner position
     */
    WPosition getMaxPos() const;

    /**
     * Get the corner of the box that has minimal x, y and z values
     *
     * \return the corner position
     */
    WPropPosition getMinPosProperty();

    /**
     * Get the corner of the box that has maximal x, y and z values
     *
     * \return the corner position
     */
    WPropPosition getMaxPosProperty();

    /**
     * Setter for standard color
     * \param color The new color.
     */
    void setColor( osg::Vec4 color );

    /**
     * Setter for color in negated state
     * \param color The new color.
     */
    void setNotColor( osg::Vec4 color );

protected:
private:
    static size_t maxBoxId; //!< Current maximum boxId over all boxes.
    size_t boxId; //!< Id of the current box.

    /**
     * Group for box specific props
     */
    WPropGroup m_propGrp;
    WPropPosition m_minPos; //!< The minimum position of the box
    WPropPosition m_maxPos; //!< The maximum position of the box

    /**
     * Shader for proper lighting.
     */
    WGEShader::RefPtr m_lightShader;

    /**
     * If true, the box' vertex data is updated.
     */
    bool m_needVertexUpdate;
    bool m_isPicked; //!< Indicates whether the box is currently picked or not.
    bool m_isPicked3D; //!< Indicates whether the box is currently picked in 3D or not.
    WPosition m_pickedPosition; //!< Caches the old picked position to a allow for cmoparison
    WVector3d m_pickNormal; //!< Store the normal that occured when the pick action was started.
    WVector2d m_oldPixelPosition; //!< Caches the old picked position to a allow for cmoparison
    int16_t m_oldScrollWheel; //!< caches scroll wheel value
    std::shared_mutex m_updateLock; //!< Lock to prevent concurrent threads trying to update the osg node
    osg::ref_ptr< osg::Geometry > m_surfaceGeometry; //!< store this pointer for use in updates

    WPickInfo m_pickInfo; //!< Stores the pick information for potential redraw
    std::pair< WPickInfo3D, WPickInfo3D > m_pickInfo3D; //!< Stores the 3D pick information for potential redraw
    std::pair< WPickInfo3D, WPickInfo3D > m_oldPickInfo3D; //!< Stores the old 3D pick information for potential redraw

    std::shared_ptr< WGEViewer > m_viewer; //!< makes viewer available all over this class.

    osg::Vec4 m_color; //!< the color of the box

    osg::Vec4 m_notColor; //!< the color of the box when negated

    /**
     * note that there was a pick
     * \param pickInfo info from pick
     */
    void registerRedrawRequest( WPickInfo pickInfo );

    /**
     * note that there was a 3D pick
     * \param pickInfo info from 3D pick
     */
    void registerRedrawRequest3D( std::pair< WPickInfo3D, WPickInfo3D > pickInfo );

    /**
     *  updates the graphics
     */
    virtual void updateGFX();

    /**
     * Handles the 2D pick.
     */
    void handlePick();

    /**
     * Handles the 3D pick.
     */
    void handlePick3D();

    /**
     * Node callback to handle updates properly
     */
    class ROIBoxNodeCallback : public osg::NodeCallback
    {
    public: // NOLINT
        /**
         * operator ()
         *
         * \param node the osg node
         * \param nv the node visitor
         */
        virtual void operator()( osg::Node* node, osg::NodeVisitor* nv )
        {
            osg::ref_ptr< WROIBox > module = static_cast< WROIBox* > ( node->getUserData() );
            if( module )
            {
                module->updateGFX();
            }
            traverse( node, nv );
        }
    };

    /**
     * Called when  the specified property has changed. Used to update the ROI when modifying box properties.
     *
     * \param property the property
     */
    void boxPropertiesChanged( std::shared_ptr< WPropertyBase > property );

    /**
     * Set new color of the box in the geometry
     *
     * \param color the new color
     */
    void updateColor( osg::Vec4 color );
};

#endif  // WROIBOX_H
