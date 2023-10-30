//---------------------------------------------------------------------------
//
// Project: OpenWalnut ( http://www.openwalnut.org )
//
// Copyright 2013-2023  OpenWalnut Community, Hochschule Coburg, Hochschul Worms
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

#include <string>
#include <iostream>

#include <osg/Geometry>
#include <osg/ShapeDrawable>

#include "core/dataHandler/WDataSetScalar.h"
#include "core/graphicsEngine/WGEGeodeUtils.h"
#include "core/graphicsEngine/WGEManagedGroupNode.h"
#include "core/kernel/WKernel.h"
#include "core/kernel/WModuleInputData.h"
#include "WMThresholdingExample.xpm"
#include "WMThresholdingExample.h"

// This line is needed by the module loader to actually find your module.
W_LOADABLE_MODULE(WMThresholdingExample)

WMThresholdingExample::WMThresholdingExample() : WModule(),
                                                 m_propCondition(new WCondition())
{
}

WMThresholdingExample::~WMThresholdingExample()
{
}

std::shared_ptr<WModule> WMThresholdingExample::factory() const
{
    return std::shared_ptr<WModule>(new WMThresholdingExample());
}

const char **WMThresholdingExample::getXPMIcon() const
{
    return WMThresholdingExample_xpm;
}
const std::string WMThresholdingExample::getName() const
{
    return "[EDU] Thresholding Example";
}

const std::string WMThresholdingExample::getDescription() const
{
    return "Should draw values above some threshold.";
}

void WMThresholdingExample::connectors()
{
    m_scalarIC = WModuleInputData<WDataSetScalar>::createAndAdd(shared_from_this(), "scalarData", "Scalar data.");

    WModule::connectors();
}

void WMThresholdingExample::properties()
{
    // ---> Put the code for your properties here. See "src/modules/template/" for an extensively documented example.
    // m_propCondition = std::shared_ptr<WCondition>(new WCondition());

    threshold = m_properties->addProperty("Threshold", "Threshold, which needs to be crossed to be counted towards the internal counter.", 60.0, m_propCondition);

    WModule::properties();
}

void WMThresholdingExample::requirements()
{
}

void WMThresholdingExample::moduleMain()
{
    infoLog() << "Thrsholding example main routine started";

    // get notified about data changes
    m_moduleState.setResetable(true, true);
    m_moduleState.add(m_scalarIC->getDataChangedCondition());
    m_moduleState.add(m_propCondition);

    ready();

    // graphics setup
    m_rootNode = osg::ref_ptr<WGEManagedGroupNode>(new WGEManagedGroupNode(m_active));
    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->insert(m_rootNode);
    m_shader = new WGEShader("WGELighting", m_localPath);
    m_shader->setDefine( "USE_MATERIAL_DIFFUSE" );

    // main loop
    while (!m_shutdownFlag())
    {
        infoLog() << "Waiting ...";
        m_moduleState.wait();


        // woke up since the module is requested to finish?
        if (m_shutdownFlag())
        {
            break;
        }

        // save data behind connectors since it might change during processing
        std::shared_ptr<WDataSetScalar> scalarData = m_scalarIC->getData();

        if (!scalarData)
        {
            continue;
        }

        // ---> Insert code doing the real stuff here

        // Assignment 4.2
        currentDataSet = scalarData;
        counter = 0;
        for (size_t i = 0; i < scalarData->getValueSet()->rawSize(); i++)
        {
            double currentScalar = scalarData->getValueSet()->getScalarDouble(i);
            if (currentScalar > threshold->get(true))
            {
                counter += 1;
            }
        }
        std::cout << " Count of points above the threshold: " << counter << "\n";

        // Assignment 4.3
        osg::ref_ptr< osg::Geode > geode = new osg::Geode();
        std::shared_ptr<WGridRegular3D> grid = std::dynamic_pointer_cast<WGridRegular3D>(scalarData->getGrid());
        for (int i = 0; i < grid->size(); i++) {
            if (scalarData->getValueSet()->getScalarDouble(i) > threshold->get(true)) {
                WVector3d position = grid->getPosition(i);
                geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(position.x(), position.y(), position.z()), 0.25)));
            }
        }

        m_rootNode->remove( m_geode );
        m_geode = geode;
        // And insert the new node
        m_rootNode->insert( m_geode );       
    }

    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->remove(m_rootNode);
}
