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

#include <QApplication>

#include "../WGuiConsts.h"
#include "../events/WEventTypes.h"
#include "../events/WPropertyChangedEvent.h"
#include "WPropertyBoolWidget.h"
#include "WPropertyColorWidget.h"
#include "WPropertyDoubleWidget.h"
#include "WPropertyFilenameWidget.h"
#include "WPropertyIntWidget.h"
#include "WPropertyIntervalWidget.h"
#include "WPropertyMatrix4X4Widget.h"
#include "WPropertyPositionWidget.h"
#include "WPropertySelectionWidget.h"
#include "WPropertyStringWidget.h"
#include "WPropertyStructWidget.h"
#include "WPropertyTransferFunctionWidget.h"
#include "WPropertyTransferFunction2DWidget.h"
#include "WPropertyTriggerWidget.h"
#include "WPropertyWidget.h"
#include "WQtPropertyGroupWidget.h"
#include "core/common/WLogger.h"

WPropertyWidget::WPropertyWidget(  std::shared_ptr< WPropertyBase > property, QGridLayout* propertyGrid, QWidget* parent ):
    QStackedWidget( parent ),
    m_property( property ),
    m_propertyGrid( propertyGrid ),
    m_label( this ),
    m_separator( this ),
    m_useLabel( m_propertyGrid ),
    m_parameterWidgets(),       // parent gets set by the QStackWidget
    m_informationWidgets(),       // parent gets set by the QStackWidget
    m_invalid( false )
{
    setObjectName( "ControlPanelPropertyWidget" );

    // define some colors
    QPalette palette;
    QColor defaultCol = palette.window().color();

    // label color
    m_labelCol = defaultCol.darker( 115 );
    // property color
    m_propertyCol = defaultCol;
    // separator color
    m_sepCol = defaultCol.darker( 130 );

    m_errorCol = QColor( "#ff3543" );

    if( m_useLabel )
    {
        // initialize members
        m_label.setContentsMargins( 0, 0, 0, 0 );
        m_label.addAdditionalWidth( 8 );    // a 4 px margin around the label
        m_label.setText( property->getName().c_str() );

        // set tooltips
        m_label.setToolTip( getTooltip().c_str() );
        setToolTip( m_label.toolTip() );

        // setup grid layout
        int row = m_propertyGrid->rowCount();
        m_propertyGrid->addWidget( &m_label, row, 0 );
        m_propertyGrid->addWidget( this, row, 1 );
        m_propertyGrid->setColumnStretch( 0, 0.0 );
        m_propertyGrid->setColumnStretch( 1, 10000.0 );

        // ONLY style if in label mode
        // set spearator style
        m_separator.setFixedHeight( 1 );
        // If you use QFrame for m_separator
        // m_separator.setFrameShape( QFrame::HLine );
        // m_separator.setFrameShadow( QFrame::Plain );
        m_propertyGrid->addWidget( &m_separator, row + 1, 0, 1, 2 );
        m_separator.setStyleSheet( "QWidget{ background-color:" + m_sepCol.name() + ";}" );

        // set style of label
        m_label.setObjectName( "ControlPanelPropertyLabelWidget" );
        // increase size of label to be the whole layout cell
        m_label.setSizePolicy( QSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Expanding ) );
        m_label.setStyleSheet( " padding-left:1px; background-color:" + m_labelCol.name() + ";" );

        // set style of this property widget
        setStyleSheet( "QStackedWidget#ControlPanelPropertyWidget{ background-color:" + m_propertyCol.name() +
                                                                   "; margin-left:1px; margin-right:1px; }" );
    }

    // add both widgets to the stacked widget, it then uses the first as default.
    addWidget( &m_parameterWidgets );
    addWidget( &m_informationWidgets );

    // if the purpose of the property is INFORMTION -> activate the information widget
    if( m_property->getPurpose() == PV_PURPOSE_INFORMATION )
    {
        setCurrentIndex( 1 );
    }

    // if the property is hidden initially, hide widget too
    setHidden( m_property->isHidden() );
    m_label.setHidden( m_property->isHidden() );
    m_separator.setHidden( m_property->isHidden() );

    // setup the update callback
    m_connection = m_property->getUpdateCondition()->subscribeSignal( boost::bind( &WPropertyWidget::requestUpdate, this ) );
}

WPropertyWidget::~WPropertyWidget()
{
    // cleanup
    m_connection.disconnect();
}

void WPropertyWidget::forceInformationMode( bool force )
{
    if( !force && ( m_property->getPurpose() != PV_PURPOSE_INFORMATION ) )
    {
        setCurrentIndex( 0 );
        return;
    }

    setCurrentIndex( 1 );
}

void WPropertyWidget::requestUpdate()
{
    QCoreApplication::postEvent( this, new WPropertyChangedEvent() );
}

bool WPropertyWidget::event( QEvent* event )
{
    // a property changed
    if( event->type() == WQT_PROPERTY_CHANGED_EVENT )
    {
        setHidden( m_property->isHidden() );
        m_label.setHidden( m_property->isHidden() );
        m_separator.setHidden( m_property->isHidden() );
        update();
        return true;
    }

    return QWidget::event( event );
}

std::string WPropertyWidget::getTooltip() const
{
    std::string tip = "<b>Property: </b>" + m_property->getName() + "<br/>";
    tip += "<b>Status: </b>";
    tip += m_invalid ? "<font color=#FF0000><b>invalid</b></font>" : "valid";
    tip += "<br/><br/>";
    return tip + m_property->getDescription();
}

std::shared_ptr< WPropertyBase > WPropertyWidget::getProperty()
{
    return m_property;
}

void WPropertyWidget::invalidate( bool invalid )
{
    m_invalid = invalid;

    if( m_useLabel )
    {
        // update tooltip
        m_label.setToolTip( getTooltip().c_str() );
        setToolTip( m_label.toolTip() );

        if( invalid )
        {
            m_label.setStyleSheet( " padding-left:1px; background-color:" + m_errorCol.name() + "; font-weight: bold;" );
        }
        else
        {
            m_label.setStyleSheet( " padding-left:1px; background-color:" + m_labelCol.name() + ";" );
        }
    }
}

QWidget* WPropertyWidget::getParameterWidgets()
{
    return &m_parameterWidgets;
}

QWidget* WPropertyWidget::getInformationWidgets()
{
    return &m_informationWidgets;
}

WPropertyWidget* WPropertyWidget::construct( WPropertyBase::SPtr property, QGridLayout* propertyGrid, QWidget* parent )
{
    switch( property->getType() )
    {
        case PV_BOOL:
            return new WPropertyBoolWidget( property->toPropBool(), propertyGrid, parent );
            break;
        case PV_INT:
            return new WPropertyIntWidget( property->toPropInt(), propertyGrid, parent  );
            break;
        case PV_DOUBLE:
            return new WPropertyDoubleWidget( property->toPropDouble(), propertyGrid, parent  );
            break;
        case PV_STRING:
            return new WPropertyStringWidget( property->toPropString(), propertyGrid, parent  );
            break;
        case PV_PATH:
            return new WPropertyFilenameWidget( property->toPropFilename(), propertyGrid, parent  );
            break;
        case PV_SELECTION:
            return new WPropertySelectionWidget( property->toPropSelection(), propertyGrid, parent  );
            break;
        case PV_COLOR:
            return new WPropertyColorWidget( property->toPropColor(), propertyGrid, parent  );
            break;
        case PV_POSITION:
            return new WPropertyPositionWidget( property->toPropPosition(), propertyGrid, parent );
            break;
        case PV_TRIGGER:
            return new WPropertyTriggerWidget( property->toPropTrigger(), propertyGrid, parent  );
            break;
        case PV_STRUCT:
            return new WPropertyStructWidget( property->toPropGroupBase(), propertyGrid, parent );
            break;
        case PV_MATRIX4X4:
            return new WPropertyMatrix4X4Widget( property->toPropMatrix4X4(), propertyGrid, parent  );
            break;
        case PV_TRANSFERFUNCTION:
            return new WPropertyTransferFunctionWidget( property->toPropTransferFunction(), propertyGrid, parent  );
            break;
        case PV_TRANSFERFUNCTION2D:
            return new WPropertyTransferFunction2DWidget( property->toPropTransferFunction2D(), propertyGrid, parent  );
            break;
        case PV_INTERVAL:
            return new WPropertyIntervalWidget( property->toPropInterval(), propertyGrid, parent );
            break;
        default:    // NOTE:: WPropGroup will be handled in WQtConrolPanel::buildPropWidget
            WLogger::getLogger()->addLogMessage( "This property type is not yet supported.", "WPropertyWidget", LL_WARNING );
            break;
    }
    return NULL;
}
