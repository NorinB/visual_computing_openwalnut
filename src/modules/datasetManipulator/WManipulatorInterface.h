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

#ifndef WMANIPULATORINTERFACE_H
#define WMANIPULATORINTERFACE_H

#include "core/common/math/linearAlgebra/WMatrixFixed.h"

/**
 * An interface for dataset transformation manipulators.
 */
class WManipulatorInterface
{
public:
    /**
     * Destructor.
     */
    virtual ~WManipulatorInterface();

    /**
     * Get the transformation matrix from this manipulator.
     *
     * \return The current transform.
     */
    virtual WMatrixFixed< double, 4, 4 > getTransformationMatrix() const = 0;

    /**
     * Check if the transform has changed, for example because of a change to properties.
     *
     * \return true, iff the transformation has changed.
     */
    virtual bool transformationChanged() const = 0;

    /**
     * Reset the transform.
     */
    virtual void reset() = 0;
};

#endif  // WMANIPULATORINTERFACE_H
