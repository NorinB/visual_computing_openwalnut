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

#include <memory>
#include <string>
#include <vector>

#include "WMTransferFunction2D.h"
#include "WMTransferFunction2D.xpm"
#include "core/common/WTransferFunction2D.h"
#include "core/dataHandler/WDataSetScalar.h"
#include "core/dataHandler/WGrid.h"
#include "core/dataHandler/WGridRegular3D.h"
#include "core/dataHandler/WValueSet.h"
#include "core/dataHandler/WValueSetBase.h"
#include "core/dataHandler/datastructures/WValueSetHistogram.h"
#include "qtgui/controlPanel/transferFunction2D/WTransferFunction2DEnums.h"
#include "core/kernel/WKernel.h"

// This line is needed by the module loader to actually find your module. Do not remove. Do NOT add a ";" here.
W_LOADABLE_MODULE( WMTransferFunction2D )

WMTransferFunction2D::WMTransferFunction2D():
    WModule()
{
}

WMTransferFunction2D::~WMTransferFunction2D()
{
    // Cleanup!
}

std::shared_ptr< WModule > WMTransferFunction2D::factory() const
{
    return std::shared_ptr< WModule >( new WMTransferFunction2D() );
}

const char** WMTransferFunction2D::getXPMIcon() const
{
    return WMTransferFunction2D_xpm;
}

const std::string WMTransferFunction2D::getName() const
{
    return "Transfer Function 2D";
}

const std::string WMTransferFunction2D::getDescription() const
{
    return "A module to modify a 2D transfer function.";
}

void WMTransferFunction2D::connectors()
{
    // the data set we use for displaying the histogram
    m_inputDataSet1 = WModuleInputData < WDataSetSingle >::createAndAdd( shared_from_this(),
            "histogram input data set 0", "The data set used to display a histogram." );

    // the data set we use for displaying the histogram
    m_inputDataSet0 = WModuleInputData < WDataSetSingle >::createAndAdd( shared_from_this(),
                                                                         "histogram input data set 1", "The data set used to display a histogram." );

    // an output connector for the transfer function created
    m_output = WModuleOutputData < WDataSetSingle >::createAndAdd( shared_from_this(),
            "TransferFunction2D", "The selected transfer function" );

    WModule::connectors();
}

void WMTransferFunction2D::properties()
{
    m_propCondition = std::shared_ptr< WCondition >( new WCondition() );

    WTransferFunction2D tf;
    std::vector<MapType> mapsEmpty;
    WTransferFunction2D::WidgetPoint points[4];
    points[0].x = 0.0;
    points[0].y = 0.0;
    points[1].x = 50.0;
    points[1].y = 0.0;
    points[2].x = 50.0;
    points[2].y = 50.0;
    points[3].x = 0.0;
    points[3].y = 50.0;

    tf.addWidget( BOX, points, mapsEmpty, mapsEmpty, false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.167, 0.167, WColor( 1.0, 0.0, 0.0, 0.125 ) );
    m_transferFunction = m_properties->addProperty( "2D transfer function",
                                                    "The 2D transfer function editor. "
                                                    "The origin (0, 0) is in the bottom left corner. "
                                                    "The first connected data set is shown on the x-axis from left to right. "
                                                    "The second connected data set is shown on the y-axis from bottom to top. ",
                                                    tf,
                                                    m_propCondition,
                                                    false );

    m_opacityScale = m_properties->addProperty( "Opacity scaling",
                                                "Factor used to scale opacity for easier interaction.",
                                                1.0,
                                                m_propCondition );
    m_opacityScale->setMin( 0 );
    m_opacityScale->setMax( 1 );

    m_resolution = m_properties->addProperty( "No. samples ",
                                               "Number of samples in the transfer function. "
                                               "Some modules connected to the output may have additional restrictions."
                                               , 128, m_propCondition );
    m_resolution->setMin( 4 );
    m_resolution->setMax( 1024 );


    m_logHistogram = m_properties->addProperty( "Logarithmic brightness",
                                                "Brightness of histogram is varied logarithmicly instead of linearly.",
                                                true, m_propCondition );

    WModule::properties();
}

void WMTransferFunction2D::requirements()
{
    //m_requirements.push_back( new WGERequirement() );
}

void WMTransferFunction2D::moduleMain()
{
    m_moduleState.setResetable( true, true );
    m_moduleState.add( m_inputDataSet0->getDataChangedCondition() );
    m_moduleState.add( m_inputDataSet1->getDataChangedCondition() );
    m_moduleState.add( m_propCondition );

    ready();

    while( !m_shutdownFlag() )
    {
        m_moduleState.wait();

        if( m_shutdownFlag() )
          break;

        bool tfChanged = m_transferFunction->changed();
        WTransferFunction2D tf = m_transferFunction->get( true );

        //debugLog() << "Current transfer function " << tf.numWidgets() << " shape widgets.";
        if( m_inputDataSet0->updated() || m_inputDataSet1->updated() || m_logHistogram->changed() )
        {
            std::shared_ptr< WDataSetSingle > dataSet0 = m_inputDataSet0->getData();
            std::shared_ptr< WDataSetSingle > dataSet1 = m_inputDataSet1->getData();

            bool dataValid = ( dataSet0 != NULL && dataSet1 != NULL );
            if( !dataValid )
            {
            }
            else
            {
                std::shared_ptr< WValueSetBase > values0 = dataSet0->getValueSet();
                std::shared_ptr< WValueSetBase > values1 = dataSet1->getValueSet();

                // At the moment we only support equal sized data sets
                // TODO(Kai?): bucketsize based on user value
                auto histogram = std::make_shared< WHistogram2D >( values0->getMinimumValue(),
                                                  values0->getMaximumValue(),
                                                  values1->getMinimumValue(),
                                                  values1->getMaximumValue(),
                                                  256,
                                                  256 );
                histogram->setLogRawTexture( m_logHistogram->get( true ) );

                for( size_t i = 0; i < values0->size(); ++i )
                {
                    histogram->insert( values0->getScalarDouble( i ), values1->getScalarDouble( i ) );
                }

                // We need a copy of the data here, because of the way how the data is handled in WTransferFunction2D
                //WHistogram2D vhistogram( histogram );
                auto vhistogram = histogram;
                tf.setHistogram( vhistogram );
            }
            // either way, we changed the data and want to update the TF
            m_transferFunction->set( tf );
        }
        if( tfChanged || m_opacityScale->changed()
            || m_resolution->changed() )
        {
            //wlog::debug( "WMTransferFunction2D" ) << "tf changed";
            // debugLog() << "resampling transfer function";
            const unsigned int resolution = m_resolution->get( true );
            const unsigned int numValuePerEntry = 4; // RGBA
            std::shared_ptr< std::vector<unsigned char>> data( new std::vector<unsigned char>( resolution * resolution * numValuePerEntry ) );
            tf.setOpacityScale( m_opacityScale->get( true ) );
            // Get the 2D texture from the TF
            tf.sample2DTransferFunction( &( *data )[0], resolution, resolution );

            // Create data set which holds the TF
            std::shared_ptr< WValueSetBase > newValueSet( new WValueSet<unsigned char>( 1, 4, data, W_DT_UNSIGNED_CHAR ) );

            WGridTransformOrtho transform;
            std::shared_ptr< WGridRegular3D > newGrid( new WGridRegular3D( resolution, resolution, 1, transform ) );
            std::shared_ptr< WDataSetSingle > newData( new WDataSetSingle( newValueSet, newGrid ) );
            // publish the TF
            m_output->updateData( newData );
        }
    }
}
