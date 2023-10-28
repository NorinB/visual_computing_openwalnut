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

#include "WQtNetworkOutputPort.h"

WQtNetworkOutputPort::WQtNetworkOutputPort( std::shared_ptr<WModuleOutputConnector> connector )
    : WQtNetworkPort()
{
    setPortName( connector.get()->getName().c_str() );
    setOutPort( connector.get()->isOutputConnector() );
    m_connector = connector;

    // create tooltip
    QString tmp;
    if( isOutPort() == true )
    {
        tmp = "output";
    }
    else if( isOutPort() == false )
    {
        tmp = "input";
    }
    else
    {
        tmp = "undefined";
    }

    QString str = "<b>Name: </b> " + getPortName() +
                  "<br/><b>PortType: </b>" + tmp +
                  "<br/><b>Description: </b>" + connector->getDescription().c_str();
    if( toolTip() != str )
    {
        setToolTip( str );
    }
}

WQtNetworkOutputPort::~WQtNetworkOutputPort()
{
}

int WQtNetworkOutputPort::type() const
{
    return Type;
}

std::shared_ptr<WModuleOutputConnector> WQtNetworkOutputPort::getConnector()
{
    return m_connector;
}

