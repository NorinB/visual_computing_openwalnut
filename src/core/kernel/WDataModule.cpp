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

#include "WDataModule.h"

WDataModule::WDataModule():
    WModule(),
    m_suppressColormaps( false ),
    m_dataModuleInput( WDataModuleInput::SPtr() ),
    m_inputChanged( new WCondition )
{
    // initialize members
}

WDataModule::~WDataModule()
{
    // cleanup
}

MODULE_TYPE WDataModule::getType() const
{
    return MODULE_DATA;
}

void WDataModule::setSuppressColormaps( bool suppress )
{
    m_suppressColormaps = suppress;
}

bool WDataModule::getSuppressColormaps() const
{
    return m_suppressColormaps;
}

void WDataModule::setInput( WDataModuleInput::SPtr input )
{
    m_dataModuleInput = input;
    m_inputChanged->notify();
    handleInputChange();
}

WDataModuleInput::SPtr WDataModule::getInput() const
{
    return m_dataModuleInput;
}

void WDataModule::reload()
{
    handleInputChange();
}

WCondition::ConstSPtr WDataModule::getInputChangedCondition() const
{
    return m_inputChanged;
}
