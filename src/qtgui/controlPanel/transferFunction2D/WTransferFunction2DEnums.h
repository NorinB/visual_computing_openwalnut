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

#ifndef WTRANSFERFUNCTION2DENUMS_H
#define WTRANSFERFUNCTION2DENUMS_H

/**
 * Points where we can perform a resizing for widget shapes
 * */
enum ResizePoints
{
    TOPLEFT,
    TOPRIGHT,
    BOTTOMLEFT,
    BOTTOMRIGHT,
    LEFT_TRI,
    MID_TRI,
    RIGHT_TRI,
    FIRST,
    SECOND,
    THIRD,
    FOURTH,
    NONE,
};

/**
 * Shapes for differantiating fucntion calls
 * */
enum Shapes
{
    BOX,
    TRIANGLE,
    QUADRANGLE,
    ELLIPSIS,
    NOSHAPE,
};

enum MapType
{
    // All Color- and Opacity Maps
    O_DECREASE_CONT,
    C_VIRIDIS,
    C_GYR_CONT,
    C_BW_CONT,
    C_INFERNO,
    C_REDBLUE,
    C_TWILIGHT,
    C_CONST_RED,
    C_CONST_GREEN,
    C_CONST_BLUE,

    //All maps inverted
    O_INCREASE_CONT,
    C_INV_VIRIDIS,
    C_INV_GYR_CONT,
    C_INV_BW_CONT,
    C_INV_INFERNO,
    C_INV_REDBLUE,
    C_INV_TWILIGHT,
};

enum AnimationType
{
    S_TOPDOWN,
    S_BOTTOMUP,
    S_MAX_Y,
    S_MIN_Y,
    S_LEFT_TO_RIGHT,
    S_RIGHT_TO_LEFT,
    S_MAX_X,
    S_MIN_X,
    NO_ANIM,
};


enum PointSortPolicy
{
    X_ASCENDING,
    Y_ASCENDING,
    NO_POLICY,
};
#endif  // WTRANSFERFUNCTION2DENUMS_H
