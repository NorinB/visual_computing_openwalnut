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

#include <osg/Geode>
#include <osg/Projection>

#include "WMColormapper.h"
#include "WMColormapper.xpm"
#include "core/dataHandler/WDataTexture3D.h"
#include "core/graphicsEngine/WGEColormapping.h"
#include "core/graphicsEngine/WGEGeodeUtils.h"
#include "core/graphicsEngine/callbacks/WGEFunctorCallback.h"
#include "core/graphicsEngine/callbacks/WGENodeMaskCallback.h"
#include "core/graphicsEngine/shaders/WGEShader.h"
#include "core/graphicsEngine/widgets/labeling/WGELabel.h"
#include "core/kernel/WKernel.h"

// This line is needed by the module loader to actually find your module.
W_LOADABLE_MODULE( WMColormapper )

WMColormapper::WMColormapper() :
    WModule(),
    m_windowLevel( 0, 1 )
{
    // initialize
}

WMColormapper::~WMColormapper()
{
    // cleanup
    removeConnectors();
}

std::shared_ptr< WModule > WMColormapper::factory() const
{
    return std::shared_ptr< WModule >( new WMColormapper() );
}

const char** WMColormapper::getXPMIcon() const
{
    return WMColormapper_xpm;
}

const std::string WMColormapper::getName() const
{
    return "Colormapper";
}

const std::string WMColormapper::getDescription() const
{
    return "Can use the input as a texture that can be mapped to the navslices and so on.";
}

void WMColormapper::connectors()
{
    m_input = WModuleInputData< WDataSetSingle >::createAndAdd( shared_from_this(), "input", "Input to apply as texture." );

    // call WModules initialization
    WModule::connectors();
}

void WMColormapper::properties()
{
    m_propCondition = std::shared_ptr< WCondition >( new WCondition() );

    m_defaultName = m_properties->addProperty( "Default Name", "This specifies the name to use for textures which are not yet named.",
            std::string( "Unnamed" ), true );

    WPropGroup colorBarGroup = m_properties->addPropertyGroup( "Colorbar", "The colorbar with several properties." );
    m_showColorbar = colorBarGroup->addProperty( "Show Colorbar", "If true, a colorbar is shown for the current colormap.", false );

    WPropGroup colorBarBorderGroup = colorBarGroup->addPropertyGroup( "Border", "The colorbar border properties." );
    WPropGroup colorBarNameLabelGroup = colorBarGroup->addPropertyGroup( "Name Label", "The colorbar name label properties." );
    WPropGroup colorBarLabelsGroup = colorBarGroup->addPropertyGroup( "Labels", "The colorbar label properties." );

    m_colorBarBorder = colorBarBorderGroup->addProperty( "Show Border", "If true, a thin white border is shown around the colorbar.", true );
    m_colorBarBorderColor = colorBarBorderGroup->addProperty( "Border Color", "Color of the border around the colorbar.",
                                                               WColor( 1.0, 1.0, 1.0, 1.0 ) );

    m_colorBarName = colorBarNameLabelGroup->addProperty( "Show Name", "If true, a shortened version of the data name is shown.", true );
    m_colorBarNameSize = colorBarNameLabelGroup->addProperty( "Text Size", "This defines the size of a character in normalized screen coordinates."
                                                                           "A value of 1 means the char is as large as the view.", 0.015 );
    m_colorBarNameSize->setMin( 0.0 );
    m_colorBarNameSize->setMax( 0.25 );

    m_colorBarNameColor = colorBarNameLabelGroup->addProperty( "Name Color", "Color of the name text", WColor( 0.9, 0.9, 0.9, 1.0 ) );
    m_colorBarNameOutlineColor = colorBarNameLabelGroup->addProperty( "Name Outline Color", "Color of the name outline", defaultColor::BLACK );

    m_possibleNamePositions = std::shared_ptr< WItemSelection >( new WItemSelection() );
    m_possibleNamePositions->addItem( "Side", "On the side." );
    m_possibleNamePositions->addItem( "Below", "Below the colorbar." );          // NOTE: you can add XPM images here.
    m_possibleNamePositions->addItem( "Above", "Above the colorbar." );
    m_colorbarNamePosition = colorBarNameLabelGroup->addProperty( "Colorbar Name Position", "Where to place the name.",
                                                                  m_possibleNamePositions->getSelectorFirst(),
                                                                  m_propCondition );
    WPropertyHelper::PC_SELECTONLYONE::addTo( m_colorbarNamePosition );
    WPropertyHelper::PC_NOTEMPTY::addTo( m_colorbarNamePosition );

    m_colorBarLabels = colorBarLabelsGroup->addProperty( "Colorbar Labels", "This defines the number of labels.", 10 );
    m_colorBarLabels->setMin( 2 );
    m_colorBarLabels->setMax( 100 );
    m_colorBarLabelsSize = colorBarLabelsGroup->addProperty( "Text Size", "This defines the size of a character in normalized screen coordinates."
                                                                          "A value of 1 means the char is as large as the view.", 0.015 );
    m_colorBarLabelsSize->setMin( 0.0 );
    m_colorBarLabelsSize->setMax( 0.25 );
    m_colorBarLabelsColor = colorBarLabelsGroup->addProperty( "Label Color", "Color of the label text", WColor( 0.9, 0.9, 0.9, 1.0 ) );
    m_colorBarLabelsOutlineColor = colorBarLabelsGroup->addProperty( "Label Outline Color", "Color of the label outline.", defaultColor::BLACK );
    m_colorBarLabelsBarColor = colorBarLabelsGroup->addProperty( "Label Bar Color", "Color of the small bar for each label.", defaultColor::WHITE );

    WModule::properties();
}

/**
 * Formats a given string to have the specified maximum length.
 *
 * \param str the string
 * \param maxLen max length
 *
 * \return formatted string
 */
std::string format( std::string str, size_t maxLen = 45 )
{
    // string will be at least 9 chars long: because of " [...] " + first and last char.
    WAssert( maxLen >= 9, "MaxLen has to be 9 or more." );
    std::ostringstream ss;

    // cut away some stuff
    if( str.length() > maxLen )
    {
        size_t keep = maxLen - 3;   // how much chars to keep?
        size_t keepFront = keep / 2;
        size_t keepEnd = keep - keepFront;

        ss << str.substr( 0, keepFront ) << " [...] " << str.substr( str.length() - keepEnd, keepEnd );
    }
    else
    {
        ss << str;
    }
    return ss.str();
}

/**
 * Formats a number properly to be usable as label
 *
 * \tparam T the type of value.
 * \param number the number to format
 *
 * \return the formated number
 */
template< typename T >
std::string format( T number )
{
    std::ostringstream ss;
    ss.precision( 3 );
    ss << number;
    return ss.str();
}

void WMColormapper::moduleMain()
{
    // let the main loop awake if the data changes or the properties changed.
    m_moduleState.setResetable( true, true );
    m_moduleState.add( m_input->getDataChangedCondition() );
    m_moduleState.add( m_propCondition );

    osg::ref_ptr< WGEShader > colormapShader = osg::ref_ptr< WGEShader > ( new WGEShader( "WMColormapper", m_localPath ) );

    // signal ready state
    ready();

    // loop until the module container requests the module to quit
    while( !m_shutdownFlag() )
    {
        // Now, the moduleState variable comes into play. The module can wait for the condition, which gets fired whenever the input receives data
        // or an property changes. The main loop now waits until something happens.
        debugLog() << "Waiting ...";
        m_moduleState.wait();

        // woke up since the module is requested to finish
        if( m_shutdownFlag() )
        {
            break;
        }

        // has the data changed?
        if( m_input->handledUpdate() )
        {
            WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->remove( m_barProjection );
            colormapShader->deactivate( m_colorBar );

            std::shared_ptr< WDataSetSingle > dataSet = m_input->getData();

            // add a colorbar
            if( dataSet && dataSet->isTexture() )
            {
                // create camera oriented 2d projection
                m_barProjection = new osg::Projection();
                m_barProjection->addUpdateCallback( new WGENodeMaskCallback( m_showColorbar ) );
                m_barProjection->addUpdateCallback( new WGENodeMaskCallback( m_active ) );
                m_barProjection->setMatrix( osg::Matrix::ortho2D( 0, 1.0, 0, 1.0 ) );
                m_barProjection->getOrCreateStateSet()->setRenderBinDetails( 15, "RenderBin" );
                m_barProjection->getOrCreateStateSet()->setDataVariance( osg::Object::DYNAMIC );
                m_barProjection->getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::OFF );
                m_barProjection->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );

                float borderWidth = 0.001;

                // create a colorbar geode
                m_colorBar = wge::genFinitePlane( osg::Vec3( 0.025, 0.1, 0.0 ), osg::Vec3( 0.025, 0.0, 0.0 ), osg::Vec3( 0.0, 0.8, 0.0 ) );
                osg::ref_ptr< osg::Geode > colorBarBorder = wge::genFinitePlane( osg::Vec3( 0.025 - borderWidth, 0.1 - borderWidth, -0.1 ),
                                                                                 osg::Vec3( 0.025 + 2.0 * borderWidth, 0.0, -0.1 ),
                                                                                 osg::Vec3( 0.0, 0.8 + 2.0 * borderWidth, -0.1 ) );
                colorBarBorder->getDrawable( 0 )->setUpdateCallback( new WGEFunctorCallback< osg::Drawable >(
                    boost::bind( &WMColormapper::updateColorbarBorder, this, boost::placeholders::_1 ) )
                );

                m_colorBar->getOrCreateStateSet()->addUniform( new WGEPropertyUniform< WPropSelection >( "u_colormap",
                                                               dataSet->getTexture()->colormap() ) );
                m_colorBar->getOrCreateStateSet()->addUniform( new WGEPropertyUniform< WPropDouble >( "u_minV",
                                                                dataSet->getTexture()->minimum() ) );
                m_colorBar->getOrCreateStateSet()->addUniform( new WGEPropertyUniform< WPropDouble >( "u_scaleV",
                                                               dataSet->getTexture()->scale() ) );

                colormapShader->apply( m_colorBar );


                // add the name label
                osg::ref_ptr< WGELabel > nameLabel = new WGELabel();
                nameLabel->setText( format( dataSet->getTexture()->name()->get() ) );
                nameLabel->setPosition( osg::Vec3( 0.015, 0.93, 0.0 ) );
                nameLabel->setCharacterSize( 0.020 );
                nameLabel->setLayout( osgText::TextBase::LEFT_TO_RIGHT );
                nameLabel->setAlignment( osgText::Text::BASE_LINE );
                nameLabel->setUpdateCallback( new WGEFunctorCallback< osg::Drawable >(
                    boost::bind( &WMColormapper::updateColorbarName, this, boost::placeholders::_1 ) )
                );

                // the bar and the labels need to be added in an identity modelview matrix node
                osg::ref_ptr< osg::MatrixTransform > matrix = new osg::MatrixTransform();
                matrix->setMatrix( osg::Matrix::identity() );
                matrix->setReferenceFrame( osg::Transform::ABSOLUTE_RF );

                // this geode contains the labels
                m_needScaleUpdate = true;
                osg::ref_ptr< osg::Geode > labels = new osg::Geode();
                labels->addDrawable( nameLabel );
                m_scaleLabels = new osg::Geode();
                m_scaleLabels->addUpdateCallback( new WGEFunctorCallback< osg::Node >(
                    boost::bind( &WMColormapper::updateColorbarScale, this, boost::placeholders::_1 )
                ) );

                // we need to adapt the labels to the window level
                // we therefore watch the window level properties
                m_windowLevelEnabled = dataSet->getTexture()->windowEnabled()->get();
                m_windowLevel = dataSet->getTexture()->window()->get();

                // set some callbacks
                colorBarBorder->addUpdateCallback( new WGENodeMaskCallback( m_colorBarBorder ) );
                labels->addUpdateCallback( new WGENodeMaskCallback( m_colorBarName ) );

                // build pipeline
                matrix->addChild( colorBarBorder );
                matrix->addChild( m_colorBar );
                matrix->addChild( m_scaleLabels );
                matrix->addChild( labels );
                m_barProjection->addChild( matrix );

                m_valueMin = dataSet->getTexture()->minimum()->get();
                m_valueScale = dataSet->getTexture()->scale()->get();

                // add
                WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->insert( m_barProjection );
            }

            // if the texture has no name, use the default name property value
            if( dataSet && dataSet->isTexture() && ( dataSet->getTexture()->name()->get() == std::string( "Unnamed" ) ) )
            {
                dataSet->getTexture()->name()->setRecommendedValue( m_defaultName->get() );
            }

            // replace texture instead of removing it?
            if( dataSet && dataSet->isTexture() && m_lastDataSet )
            {
                debugLog() << "Replacing texture \"" << m_lastDataSet->getTexture()->name()->get() << "\" with \"" <<
                                                        dataSet->getTexture()->name()->get() << "\".";

                // set the _recommended_ values from the previous ones
                // to avoid a critical issue ( #237 ) with the minimum and scaler properties of the texture, we explicitly exclude them here.
                std::vector< std::string > excludes;
                excludes.push_back( "Minimum" );
                excludes.push_back( "Scale" );
                dataSet->getTexture()->getProperties()->set( m_lastDataSet->getTexture()->getProperties(), excludes, true );

                // finally, set the new properties (and remove the old props)
                m_properties->removeProperty( m_lastDataSet->getTexture()->getProperties() );
                m_infoProperties->removeProperty( m_lastDataSet->getTexture()->getInformationProperties() );
                m_properties->addProperty( dataSet->getTexture()->getProperties() );
                m_infoProperties->addProperty( dataSet->getTexture()->getInformationProperties() );

                // tell the colormapper about it
                WGEColormapping::replaceTexture( m_lastDataSet->getTexture(), dataSet->getTexture() );
                m_lastDataSet = dataSet;
            }
            else
            {
                // de-register last input
                if( m_lastDataSet )
                {
                    debugLog() << "Removing previous texture \"" << m_lastDataSet->getTexture()->name()->get() << "\".";
                    m_properties->removeProperty( m_lastDataSet->getTexture()->getProperties() );
                    m_infoProperties->removeProperty( m_lastDataSet->getTexture()->getInformationProperties() );
                    WGEColormapping::deregisterTexture( m_lastDataSet->getTexture() );
                    m_lastDataSet.reset();
                }

                // register only valid data
                if( dataSet && dataSet->isTexture() )
                {
                    m_lastDataSet = dataSet;

                    // register new
                    debugLog() << "Registering new texture \"" << m_lastDataSet->getTexture()->name()->get() << "\".";
                    m_properties->addProperty( m_lastDataSet->getTexture()->getProperties() );
                    m_infoProperties->addProperty( m_lastDataSet->getTexture()->getInformationProperties() );
                    WGEColormapping::registerTexture( m_lastDataSet->getTexture() );
                }
            }
        }
    }

    // remove if module is removed
    if( m_lastDataSet )
    {
        debugLog() << "Removing previous texture \"" << m_lastDataSet->getTexture()->name()->get() << "\".";
        WGEColormapping::deregisterTexture( m_lastDataSet->getTexture() );
        // NOTE: the props get removed automatically
    }

    // remove colorbar and its labels
    WKernel::getRunningKernel()->getGraphicsEngine()->getScene()->remove( m_barProjection );
}

void WMColormapper::activate()
{
    // deactivate the output if wanted
    if( m_lastDataSet )
    {
        m_lastDataSet->getTexture()->active()->set( m_active->get( true ) );
    }

    // Always call WModule's activate!
    WModule::activate();
}

void WMColormapper::updateColorbarBorder( osg::Drawable* border )
{
    osg::ref_ptr< osg::Vec4Array > colors = new osg::Vec4Array;
    colors->push_back( m_colorBarBorderColor->get() );
    dynamic_cast< osg::Geometry* >( border )->setColorArray( colors );
}

void WMColormapper::updateColorbarName( osg::Drawable* label )
{
    WGELabel* l = dynamic_cast< WGELabel* >( label );

    if( m_lastDataSet )
    {
        l->setText( format( m_lastDataSet->getTexture()->name()->get() ) );
    }

    if( m_colorbarNamePosition->changed() || m_colorBarNameSize->changed( true ) )
    {
        switch( m_colorbarNamePosition->get( true ) )
        {
            case 0: // side
                l->setPosition( osg::Vec3( 0.015, 0.9, 0.0 ) );
                l->setCharacterSize( m_colorBarNameSize->get() );
                l->setLayout( osgText::TextBase::VERTICAL );
                break;
            case 1: // below
                l->setPosition( osg::Vec3( 0.015, 0.06, 0.0 ) );
                l->setCharacterSize( m_colorBarNameSize->get() );
                l->setLayout( osgText::TextBase::LEFT_TO_RIGHT );
                break;
            case 2: // above
                l->setPosition( osg::Vec3( 0.015, 0.93, 0.0 ) );
                l->setCharacterSize( m_colorBarNameSize->get() );
                l->setLayout( osgText::TextBase::LEFT_TO_RIGHT );
                break;
            default:
                break;
        }
    }
    l->setColor( m_colorBarNameColor->get() );
    l->setBackdropColor( m_colorBarNameOutlineColor->get() );
}

void WMColormapper::updateColorbarScale( osg::Node* scaleLabels )
{
    if( m_needScaleUpdate || m_colorBarLabels->changed( true ) ||
              m_colorBarLabelsColor->changed( true ) ||
              m_colorBarLabelsOutlineColor->changed( true ) ||
              m_colorBarLabelsBarColor->changed( true ) ||
              m_colorBarLabelsSize->changed( true ) ||
            ( m_windowLevelEnabled != m_lastDataSet->getTexture()->windowEnabled()->get() ) ||
            ( m_windowLevel != m_lastDataSet->getTexture()->window()->get() )
      )
    {
        m_needScaleUpdate = false;
        m_windowLevelEnabled = m_lastDataSet->getTexture()->windowEnabled()->get();
        m_windowLevel = m_lastDataSet->getTexture()->window()->get();

        const double labelXPos = 0.060;
        osg::Geode* g = scaleLabels->asGeode();
        g->removeDrawables( 0, g->getNumDrawables() );

        size_t num = m_colorBarLabels->get( true );
        double coordStep = 0.8 / static_cast< double >( num - 1 );
        double valueStep = m_valueScale / static_cast< double >( num - 1 );
        double valueMin = m_valueMin;

        if( m_windowLevelEnabled )
        {
            valueStep = m_windowLevel.getLength() / static_cast< double >( num - 1 );
            valueMin = m_windowLevel.getLower();
        }

        // less than 2 labels is useless
        if( num < 2 )
        {
            return;
        }

        osg::Vec3Array* lineVerts = new osg::Vec3Array();

        // create enough labels.
        for( size_t i = 0; i < num; ++i )
        {
            double value = valueMin + ( valueStep * i );

            // create the label
            osg::ref_ptr< WGELabel > label = new WGELabel();
            label->setPosition( osg::Vec3( labelXPos, 0.1 + i * coordStep, 0.0 ) );  // bar goes from 0.1 to 0.9 in our coordinate system
            label->setText( format( value ) );
            label->setCharacterSize( m_colorBarLabelsSize->get() );
            label->setAlignment( osgText::Text::LEFT_CENTER );
            label->setColor( m_colorBarLabelsColor->get() );
            label->setBackdropColor( m_colorBarLabelsOutlineColor->get() );

            g->addDrawable( label );

            // create the line next to the label
            lineVerts->push_back( osg::Vec3( labelXPos - 0.010, 0.1 + i * coordStep, 0.0 ) );
            lineVerts->push_back( osg::Vec3( labelXPos - 0.005, 0.1 + i * coordStep, 0.0 ) );
        }

        // create the line drawable
        osg::Geometry* lines = new osg::Geometry();
        lines->setVertexArray( lineVerts );
        osg::Vec4Array* color = new osg::Vec4Array();
        color->push_back( m_colorBarLabelsBarColor->get() );
        lines->setColorArray( color );
        lines->setColorBinding( osg::Geometry::BIND_OVERALL );
        lines->addPrimitiveSet( new osg::DrawArrays( GL_LINES, 0, lineVerts->size() ) );
        g->addDrawable( lines );
    }
}

