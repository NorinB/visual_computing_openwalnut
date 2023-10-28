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

#ifndef WMEEGVIEW_H
#define WMEEGVIEW_H

#include <memory>
#include <string>
#include <vector>

#include <osg/Texture1D>
#include <osgSim/ScalarsToColors>

#include "core/kernel/WModule.h"

// forward declarations
class WUIViewWidget;
class WDataSetDipole;
class WEEG;
class WEEGSourceCalculator;
class WEEGViewHandler;
class WGEGroupNode;
class WROIBox;
template< class T > class WModuleInputData;

/**
 * Test module to open a new widget and display EEG data
 * \ingroup modules
 */
class WMEEGView : public WModule
{
public:
    /**
     * default constructor
     */
    WMEEGView();

    /**
     * destructor
     */
    virtual ~WMEEGView();

    /**
     * Due to the prototype design pattern used to build modules, this method
     * returns a new instance of this method.
     * NOTE: it should never be initialized or modified in some other way. A
     * simple new instance is required.
     *
     * \return the prototype used to create every module in OpenWalnut.
     */
    virtual std::shared_ptr< WModule > factory() const;

    /**
     * Gets the name of this module.
     *
     * \return the name.
     */
    virtual const std::string getName() const;

    /**
     * Gets the description for this module.
     *
     * \return the description
     */
    virtual const std::string getDescription() const;

    /**
     * Get the icon for this module in XPM format.
     *
     * \return the icon.
     */
    virtual const char** getXPMIcon() const;

protected:
    /**
     * Initialize connectors in this function.
     */
    virtual void connectors();

    /**
     * Initialize properties in this function.
     */
    virtual void properties();

    /**
     * Gets called whenever a connector gets connected to the specified input.
     * Sets the m_dataChanged flag.
     */
    virtual void notifyConnectionEstablished(
        std::shared_ptr< WModuleConnector > /*here*/, std::shared_ptr< WModuleConnector > /*there*/ );

    /**
     * Gets called when the data on one input connector changed.
     * Sets the m_dataChanged flag.
     */
    virtual void notifyDataChange(
        std::shared_ptr< WModuleConnector > /*input*/, std::shared_ptr< WModuleConnector > /*output*/ );

    /**
     * Entry point after loading the module. Runs in separate thread.
     */
    virtual void moduleMain();

    /**
     * Initialize requirements for this module.
     */
    virtual void requirements();

private:
    /**
     * Input connector for a EEG dataset
     */
    std::shared_ptr< WModuleInputData< WEEG > > m_eeg_input;

    /**
     * Input connector for dipoles of EEG data
     */
    std::shared_ptr< WModuleInputData< WDataSetDipoles > > m_dipoles_input;

    /**
     * A condition used to notify about changes in several properties.
     */
    std::shared_ptr< WCondition > m_propCondition;

    /**
     * Group for parameters that are normally adjusted using mouse actions.
     */
    WPropGroup m_manualNavigationGroup;

    /**
     * Group for parameters that adjust the appearance of the EEG widget
     */
    WPropGroup m_appearanceGroup;

    /**
     * Property determining whether electode positions should be drawn.
     */
    WPropBool m_drawElectrodes;

    /**
     * Property determining whether the head surface should be drawn.
     */
    WPropBool m_drawHeadSurface;

    /**
     * Property determining whether electrode labels should be drawn.
     */
    WPropBool m_drawLabels;

    /**
     * Property determining whether we only show the proof of concept or the real dipoles
     */
    WPropBool m_proofOfConcept;

    /**
     * Property determining whether the selected time position should be snapped to an active dipole
     */
    WPropBool m_snapToDipole;

    /**
     * Property switching between standard and butterfly plot of curves (overlay of all curves in one row)
     */
    WPropBool m_butterfly;

    /**
     * Size of the region of interest
     */
    WPropDouble m_ROIsize;

    /**
     * the width of the label display in pixel as property
     */
    WPropInt m_labelsWidth;

    /**
     * the time position in seconds where to start the graph at the left edge as
     * property
     */
    WPropDouble m_timePos;

    /**
     * the width of the graph in seconds as property
     */
    WPropDouble m_timeRange;

    /**
     * the width of the graph in pixel as property
     */
    WPropInt m_graphWidth;

    /**
     * the y position in pixel at the lower edge as property
     */
    WPropDouble m_yPos;

    /**
     * the distance between two curves of the graph in pixel as property
     */
    WPropDouble m_ySpacing;

    /**
     * the sensitivity of the graph in microvolt per pixel as property
     */
    WPropDouble m_ySensitivity;

    /**
     * The sensitivity of the color map as property. The color map ranges
     * from -m_colorSensitivity to +m_colorSensitivity in microvolt.
     */
    WPropDouble m_colorSensitivity;

    /**
     * event marking a special time position as WFlag
     */
    std::shared_ptr< WFlag< std::shared_ptr< WEEGEvent > > > m_event;

    /**
     * Pointer to the loaded EEG dataset
     */
    std::shared_ptr< WEEG > m_eeg;

    /**
     * Pointer to the loaded dipoles dataset
     */
    std::shared_ptr< WDataSetDipoles > m_dipoles;

    /**
     * Custom widget which is used by this module to display its data.
     */
    std::shared_ptr< WUIViewWidget > m_widget;

    /**
     * GUI event handler used for interactive changing of many properties
     */
    osg::ref_ptr< WEEGViewHandler > m_handler;

    /**
     * OSG node for all 2D stuff of this module. All other OSG nodes should be
     * placed as child to this node.
     */
    osg::ref_ptr< WGEGroupNode > m_rootNode2d;

    /**
     * OSG node for all 3D stuff of this module. All other OSG nodes should be
     * placed as child to this node.
     */
    osg::ref_ptr< WGEGroupNode > m_rootNode3d;

    /**
     * OSG node for the 3D display of the electrode positions
     */
    osg::ref_ptr< osg::Node > m_electrodesNode;

    /**
     * OSG node for the 3D display of the head surface
     */
    osg::ref_ptr< osg::Node > m_headSurfaceNode;

    /**
     * OSG node for the 3D display of the electrode labels
     */
    osg::ref_ptr< osg::Node > m_labelsNode;

    /**
     * The ROIs around the source dipole positions at the time determined by
     * m_event.
     * Used to select the fibers around this dipoles.
     */
    std::vector< osg::ref_ptr< WROIBox > > m_rois;

    /**
     * Bool flag which gets set when the data was changed.
     * The module threads waits for this flag and performs a redraw.
     */
    WBoolFlag m_dataChanged;

    /**
     * The current active-state. Whether the widget is open and usable.
     */
    bool m_wasActive;

    /**
     * The time of the current event. Used to check whether the event changed.
     */
    double m_currentEventTime;

    /**
     * A ScalarsToColors object mapping the potentials at the electrodes to
     * colors. Used for the display of electrode positions and the head surface.
     */
    osg::ref_ptr< osgSim::ScalarsToColors > m_colorMap;

    /**
     * A 1D texture containing the color map as image. Used for the
     * interpolation on the head surface.
     */
    osg::ref_ptr< osg::Texture1D > m_colorMapTexture;

    /**
     * calculates a source position at a given time position
     */
    std::shared_ptr< WEEGSourceCalculator > m_sourceCalculator;

    /**
     * Prepare textures for colormapping EEG signal
     */
    void createColorMap();

    /**
     * Opens a custom widget and connects the m_node with it.
     *
     * \returns whether the custom widget could be opened successfully
     */
    bool openCustomWidget();

    /**
     * Disconnects the m_node from the custom widget and closes the widget.
     */
    void closeCustomWidget();

    /**
     * Removes all Nodes from m_rootNode2d and m_rootNode3d and adds new ones
     * based on the current data stored in m_eeg.
     */
    void redraw();

    /**
     * Draw the electrode positions in 3D.
     *
     * \return an OSG Node containing the electrode positions
     */
    osg::ref_ptr< osg::Node > drawElectrodes();

    /**
     * Draw the head surface in 3D.
     *
     * \return an OSG Node containing the head surface
     */
    osg::ref_ptr< osg::Node > drawHeadSurface();

    /**
     * Draw the electrode labels in 3D.
     *
     * \return an OSG Node containing the electrode labels
     */
    osg::ref_ptr< osg::Node > drawLabels();
};

#endif  // WMEEGVIEW_H
