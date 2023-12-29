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

#include <vector>

#include "WAcceleratedMarchingCubesAlgorithm.h"

WAcceleratedMarchingCubesAlgorithm::WAcceleratedMarchingCubesAlgorithm()
    : m_matrix(4, 4)
{
}

WAcceleratedPointXYZId WAcceleratedMarchingCubesAlgorithm::interpolate(double fX1, double fY1, double fZ1, double fX2, double fY2, double fZ2,
                                                                       double tVal1, double tVal2)
{
    WAcceleratedPointXYZId interpolation;
    double mu;

    mu = static_cast<double>((m_tIsoLevel - tVal1)) / (tVal2 - tVal1);
    interpolation.x = fX1 + mu * (fX2 - fX1);
    interpolation.y = fY1 + mu * (fY2 - fY1);
    interpolation.z = fZ1 + mu * (fZ2 - fZ1);
    interpolation.newID = 0;

    return interpolation;
}

int WAcceleratedMarchingCubesAlgorithm::getEdgeID(unsigned int nX, unsigned int nY, unsigned int nZ, unsigned int nEdgeNo)
{
    switch (nEdgeNo)
    {
    case 0:
        return 3 * getVertexID(nX, nY, nZ) + 1;
    case 1:
        return 3 * getVertexID(nX, nY + 1, nZ);
    case 2:
        return 3 * getVertexID(nX + 1, nY, nZ) + 1;
    case 3:
        return 3 * getVertexID(nX, nY, nZ);
    case 4:
        return 3 * getVertexID(nX, nY, nZ + 1) + 1;
    case 5:
        return 3 * getVertexID(nX, nY + 1, nZ + 1);
    case 6:
        return 3 * getVertexID(nX + 1, nY, nZ + 1) + 1;
    case 7:
        return 3 * getVertexID(nX, nY, nZ + 1);
    case 8:
        return 3 * getVertexID(nX, nY, nZ) + 2;
    case 9:
        return 3 * getVertexID(nX, nY + 1, nZ) + 2;
    case 10:
        return 3 * getVertexID(nX + 1, nY + 1, nZ) + 2;
    case 11:
        return 3 * getVertexID(nX + 1, nY, nZ) + 2;
    default:
        // Invalid edge no.
        return -1;
    }
}

unsigned int WAcceleratedMarchingCubesAlgorithm::getVertexID(unsigned int nX, unsigned int nY, unsigned int nZ)
{
    return nZ * (m_nCellsY + 1) * (m_nCellsX + 1) + nY * (m_nCellsX + 1) + nX;
}

std::vector<std::vector<unsigned int>> WAcceleratedMarchingCubesAlgorithm::getDividedCoordinatesSpan(const std::vector<unsigned int> coordinatesSpan)
{
    // std::cout << "coordinatesSpan: " << coordinatesSpan.front() << " " << coordinatesSpan.back() << std::endl;
    std::vector<std::vector<unsigned int>> result;
    std::vector<unsigned int> firstHalf;
    std::vector<unsigned int> secondHalf;
    if (coordinatesSpan[1] - coordinatesSpan[0] == 0)
    {
        return result;
    }
    else if (coordinatesSpan[1] - coordinatesSpan[0] == 1)
    {
        // std::cout << "Nur eine Hälfte, weil coordinatesSpan: " << coordinatesSpan.front() << " - " << coordinatesSpan.back() << std::endl << std::endl;
        firstHalf = {coordinatesSpan.front(), coordinatesSpan.back()};
        result.push_back(firstHalf);
        result.push_back({});
        return result;
    }
    // else if (coordinatesSpan[1] - coordinatesSpan[0] == 2)
    // {
    //     firstHalf = {coordinatesSpan.front(), coordinatesSpan.front() + 1};
    //     secondHalf = {coordinatesSpan.front() + 1, coordinatesSpan.back()};
    // }
    // else if (coordinatesSpan[1] - coordinatesSpan[0] == 3)
    // {
    //     firstHalf = {coordinatesSpan.front(), coordinatesSpan.front() + 1};
    //     secondHalf = {coordinatesSpan.front() + 1, coordinatesSpan.back()};
    // }
    else
    {
        unsigned int mid = coordinatesSpan.front() + ((coordinatesSpan.back() - coordinatesSpan.front()) / 2);
        firstHalf = {coordinatesSpan.front(), mid};
        secondHalf = {mid, coordinatesSpan.back()};
    }
    result.push_back(firstHalf);
    result.push_back(secondHalf);
    return result;
}

unsigned int WAcceleratedMarchingCubesAlgorithm::getMiddleOfCoordinatesSpan(const std::vector<unsigned int> coordinatesSpan)
{
    if (coordinatesSpan[1] - coordinatesSpan[0] == 1)
    {
        return coordinatesSpan.back();
    }
    else if (coordinatesSpan[1] - coordinatesSpan[0] == 0)
    {
        return coordinatesSpan.front();
    }
    return coordinatesSpan.front() + ((coordinatesSpan.back() - coordinatesSpan.front()) / 2);
}

bool WAcceleratedMarchingCubesAlgorithm::isOnlyOneBlock(std::vector<unsigned int> xCoordinatesSpan, std::vector<unsigned int> yCoordinatesSpan, std::vector<unsigned int> zCoordinatesSpan)
{
    if (xCoordinatesSpan[1] - xCoordinatesSpan[0] == 1 && yCoordinatesSpan[1] - yCoordinatesSpan[0] == 1 && zCoordinatesSpan[1] - zCoordinatesSpan[0] == 1)
    {
        return true;
    }
    return false;
}
