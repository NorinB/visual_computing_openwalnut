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

#ifndef WACCELEARTEDMARCHINGCUBESALGORITHM_H
#define WACCELEARTEDMARCHINGCUBESALGORITHM_H

#include <map>
#include <memory>
#include <vector>
#include <numeric>
#include <chrono>

#include "../WProgressCombiner.h"
#include "../math/WMatrix.h"
#include "WMarchingCubesCaseTables.h"
#include "core/graphicsEngine/WTriangleMesh.h"
#include "Octree.h"

#include "WAcceleratedPointXYZId.h"

typedef std::map<unsigned int, WAcceleratedPointXYZId> ID2WAcceleratedPointXYZId;

/**
 * Encapsulated ids representing a triangle.
 */
struct WAcceleratedMCTriangle
{
    unsigned int pointID[3]; //!< The IDs of the vertices of the triangle.
};

typedef std::vector<WAcceleratedMCTriangle> WAcceleratedMCTriangleVECTOR;

// -------------------------------------------------------
//
// Numbering of edges (0..B) and vertices (0..7) per cube.
//
//      5--5--6
//     /|    /|
//    4 |   6 |    A=10
//   /  9  /  A
//  4--7--7   |
//  |   | |   |
//  |   1-|1--2
//  8  /  B  /
//  | 0   | 2      B=11
//  |/    |/
//  0--3--3
//
//  |  /
//  z y
//  |/
//  0--x--
//
// -------------------------------------------------------

/**
 * This class does the actual computation of marching cubes.
 */
class WAcceleratedMarchingCubesAlgorithm
{
    /**
     * Only UnitTests may be friends.
     */
    friend class WAcceleratedMarchingCubesAlgorithmTest;

public:
    /**
     * Constructor needed for matrix initalization.
     */
    WAcceleratedMarchingCubesAlgorithm();

    /**
     * Generate the triangles for the surface on the given dataSet (inGrid, vals). The texture coordinates in the resulting mesh are relative to
     * the grid. This means they are NOT transformed. This ensure faster grid matrix updates in texture space.
     * This might be useful where texture transformation matrices are used.
     *
     * \param nbCoordsX number of vertices in X direction
     * \param nbCoordsY number of vertices in Y direction
     * \param nbCoordsZ number of vertices in Z direction
     * \param mat the matrix transforming the vertices from canonical space
     * \param vals the values at the vertices
     * \param isoValue The surface will run through all positions with this value.
     * \param mainProgress progress combiner used to report our progress to
     * \param octree Octree to use for the calculation
     *
     * \return the genereated surface
     */
    template <typename T>
    std::shared_ptr<WTriangleMesh> generateSurfaceWithOctree(size_t nbCoordsX, size_t nbCoordsY, size_t nbCoordsZ,
                                                             const WMatrix<double> &mat,
                                                             const std::vector<T> *vals,
                                                             double isoValue,
                                                             std::shared_ptr<WProgressCombiner> mainProgress, Octree &octree);

    /**
     * Generates the Octree for the given points and iso value, which can be used later on to calculate the isosurface faster.
     * \param points the points to calculate the octree for
     * \param isoValue the iso value to calculate the octree for
     * \param vals the values at the vertices
     * \param xCoordinatesSpan x Coordinates of this octree element
     * \param yCoordinates y Coordinates of this octree element
     * \param zCoordinates z Coordinates of this octree element
     * \param xCells number of cells in x direction
     * \param yCells number of cells in y direction
     *
     * \return the generated octree
     */
    template <typename T>
    Octree generateOctree(const std::vector<WAcceleratedPointXYZId> &points, double isoValue, const std::vector<T> *vals, std::vector<unsigned int> xCoordinatesSpan, std::vector<unsigned int> yCoordinatesSpan, std::vector<unsigned int> zCoordinatesSpan, unsigned int xCells, unsigned int yCells);

    /**
     * Gets the min and max values of the given points and returns them as a vector, where the first value is the min and the second value is the max.
     * \param points the points to get the min and max values from
     * \param vals the values at the vertices
     * \param xCells number of cells in x direction
     * \param yCells number of cells in y direction
     *
     * \return the min and max values as the vector
     */
    template <typename T>
    std::vector<double> getMinAndMax(const std::vector<WAcceleratedPointXYZId> &points, const std::vector<T> *vals, unsigned int xCells, unsigned int yCells);

    /**
     * Constructs a vector of points, which are inside the given coordinates span.
     * \param xCoords number of cells in x direction
     * \param yCoords number of cells in y direction
     * \param zCoords number of cells in z direction
     *
     * \return the vector of points
     */
    std::vector<WAcceleratedPointXYZId> getPoints(unsigned int xCells, unsigned int yCells, unsigned int zCells);

    /**
     * Constructs a vector of points, which are inside the given coordinates span.
     * \param point root point of the cell
     * \param vals the values at the vertices
     * \param xCells number of cells in x direction
     * \param yCells number of cells in y direction
     *
     * \return the vector of points
     */
    template <typename T>
    std::vector<T> getMinAndMaxOfCell(WAcceleratedPointXYZId point, const std::vector<T> *vals, unsigned int xCells, unsigned int yCells);    

protected:
private:
    /**
     * Calculates the intersection point id of the isosurface with an
     * edge.
     *
     * \param vals the values at the vertices
     * \param nX id of cell in x direction
     * \param nY id of cell in y direction
     * \param nZ id of cell in z direction
     * \param nEdgeNo id of the edge the point that will be interpolates lies on
     *
     * \return intersection point id
     */
    template <typename T>
    WAcceleratedPointXYZId calculateIntersection(const std::vector<T> *vals,
                                                 unsigned int nX, unsigned int nY, unsigned int nZ, unsigned int nEdgeNo);

    /**
     * Interpolates between two grid points to produce the point at which
     * the isosurface intersects an edge.
     *
     * \param fX1 x coordinate of first position
     * \param fY1 y coordinate of first position
     * \param fZ1 z coordinate of first position
     * \param fX2 x coordinate of second position
     * \param fY2 y coordinate of first position
     * \param fZ2 z coordinate of first position
     * \param tVal1 scalar value at first position
     * \param tVal2 scalar value at second position
     *
     * \return interpolated point
     */
    WAcceleratedPointXYZId interpolate(double fX1, double fY1, double fZ1, double fX2, double fY2, double fZ2, double tVal1, double tVal2);

    /**
     * Returns the edge ID.
     *
     * \param nX ID of desired cell along x axis
     * \param nY ID of desired cell along y axis
     * \param nZ ID of desired cell along z axis
     * \param nEdgeNo id of edge inside cell
     *
     * \return The id of the edge in the large array.
     */
    int getEdgeID(unsigned int nX, unsigned int nY, unsigned int nZ, unsigned int nEdgeNo);

    /**
     * Returns the ID of the vertex given by by the IDs along the axis
     * \param nX ID of desired vertex along x axis
     * \param nY ID of desired vertex along y axis
     * \param nZ ID of desired vertex along z axis
     *
     * \return ID of vertex with the given coordinates
     */
    unsigned int getVertexID(unsigned int nX, unsigned int nY, unsigned int nZ);

    /**
     * Calculates the tow halfs of the given coordinates span and returns the two halfs as a vector.
     * \param coordinatesSpan the coordinates span to divide
     */
    std::vector<std::vector<unsigned int>> getDividedCoordinatesSpan(const std::vector<unsigned int> coordinatesSpan);

    /**
     * Calculates the middle of the given coordinates span.
     * \param coordinatesSpan the coordinates span to calculate the middle of
     */
    unsigned int getMiddleOfCoordinatesSpan(const std::vector<unsigned int> coordinatesSpan);

    /**
     * Calculates the octree for the given points and iso value. Calls itself recusively until it gets to the smallest possible octree.
     * \param points the points to calculate the octree for
     * \param isoValue the iso value to calculate the octree for
     * \param vals the values at the vertices
     * \param xCoordinatesSpan x Coordinates of this octree element
     * \param yCoordinates y Coordinates of this octree element
     * \param zCoordinates z Coordinates of this octree element
     */
    template <typename T>
    std::vector<WAcceleratedPointXYZId> calculateOctree(const std::vector<WAcceleratedPointXYZId> &points, double isoValue, const std::vector<T> *vals, std::vector<unsigned int> xCoordinatesSpan, std::vector<unsigned int> yCoordinatesSpan, std::vector<unsigned int> zCoordinatesSpan);

    /**
     * Calculates, whether the given points include the given iso value.
     * \param points the points to check
     * \param isoValue the iso value to check
     * \param vals the values at the vertices
     */
    template <typename T>
    bool isInside(const std::vector<WAcceleratedPointXYZId> &points, double isoValue, const std::vector<T> *vals);

    /**
     * Calculates, whether there is only one block in the given points.
     * \param xCoordinatesSpan x Coordinates of this octree element
     * \param yCoordinates y Coordinates of this octree element
     * \param zCoordinates z Coordinates of this octree element
     */
    bool isOnlyOneBlock(std::vector<unsigned int> xCoordinatesSpan, std::vector<unsigned int> yCoordinatesSpan, std::vector<unsigned int> zCoordinatesSpan);

    unsigned int m_nCellsX; //!< No. of cells in x direction.
    unsigned int m_nCellsY; //!< No. of cells in y direction.
    unsigned int m_nCellsZ; //!< No. of cells in z direction.

    double m_tIsoLevel; //!< The isovalue.

    WMatrix<double> m_matrix; //!< The 4x4 transformation matrix for the triangle vertices.

    ID2WAcceleratedPointXYZId m_idToVertices;       //!< List of WAcceleratedPointXYZIds which form the isosurface.
    WAcceleratedMCTriangleVECTOR m_trivecTriangles; //!< List of WAcceleratedMCTriangleS which form the triangulation of the isosurface.
};

template <typename T>
std::shared_ptr<WTriangleMesh> WAcceleratedMarchingCubesAlgorithm::generateSurfaceWithOctree(size_t nbCoordsX, size_t nbCoordsY, size_t nbCoordsZ,
                                                                                             const WMatrix<double> &mat,
                                                                                             const std::vector<T> *vals,
                                                                                             double isoValue,
                                                                                             std::shared_ptr<WProgressCombiner> mainProgress, Octree &octree)
{
    auto start = std::chrono::high_resolution_clock::now();
    WAssert(vals, "No value set provided.");

    m_idToVertices.clear();
    m_trivecTriangles.clear();

    m_nCellsX = nbCoordsX - 1;
    m_nCellsY = nbCoordsY - 1;
    m_nCellsZ = nbCoordsZ - 1;

    m_matrix = mat;

    m_tIsoLevel = isoValue;

    unsigned int nX = m_nCellsX + 1;
    unsigned int nY = m_nCellsY + 1;

    unsigned int nPointsInSlice = nX * nY;

    std::shared_ptr<WProgress> progress(new WProgress("Accelerated Marching Cubes", m_nCellsZ));
    mainProgress->addSubProgress(progress);

    std::vector<WAcceleratedPointXYZId> points;

    points = octree.getPointsIncludingIsoValue(isoValue);

    std::cout << "Number of points for accelerated marching cubes: " << points.size() << std::endl;
    // Generate isosurface.
    for (const auto &point : points)
    {
        ++*progress;
        // Calculate table lookup index from those
        // vertices which are below the isolevel.
        unsigned int tableIndex = 0;
        if ((*vals)[point.z * nPointsInSlice + point.y * nX + point.x] < m_tIsoLevel)
            tableIndex |= 1;
        if ((*vals)[point.z * nPointsInSlice + (point.y + 1) * nX + point.x] < m_tIsoLevel)
            tableIndex |= 2;
        if ((*vals)[point.z * nPointsInSlice + (point.y + 1) * nX + (point.x + 1)] < m_tIsoLevel)
            tableIndex |= 4;
        if ((*vals)[point.z * nPointsInSlice + point.y * nX + (point.x + 1)] < m_tIsoLevel)
            tableIndex |= 8;
        if ((*vals)[(point.z + 1) * nPointsInSlice + point.y * nX + point.x] < m_tIsoLevel)
            tableIndex |= 16;
        if ((*vals)[(point.z + 1) * nPointsInSlice + (point.y + 1) * nX + point.x] < m_tIsoLevel)
            tableIndex |= 32;
        if ((*vals)[(point.z + 1) * nPointsInSlice + (point.y + 1) * nX + (point.x + 1)] < m_tIsoLevel)
            tableIndex |= 64;
        if ((*vals)[(point.z + 1) * nPointsInSlice + point.y * nX + (point.x + 1)] < m_tIsoLevel)
            tableIndex |= 128;

        // Now create a triangulation of the isosurface in this
        // cell.
        if (wMarchingCubesCaseTables::edgeTable[tableIndex] != 0)
        {
            if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 8)
            {
                WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 3);
                unsigned int id = getEdgeID(point.x, point.y, point.z, 3);
                m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
            }
            if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 1)
            {
                WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 0);
                unsigned int id = getEdgeID(point.x, point.y, point.z, 0);
                m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
            }
            if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 256)
            {
                WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 8);
                unsigned int id = getEdgeID(point.x, point.y, point.z, 8);
                m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
            }

            // if (point.x == m_nCellsX - 1)
            {
                if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 4)
                {
                    WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 2);
                    unsigned int id = getEdgeID(point.x, point.y, point.z, 2);
                    m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
                }
                if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 2048)
                {
                    WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 11);
                    unsigned int id = getEdgeID(point.x, point.y, point.z, 11);
                    m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
                }
            }
            // if (point.y == m_nCellsY - 1)
            {
                if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 2)
                {
                    WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 1);
                    unsigned int id = getEdgeID(point.x, point.y, point.z, 1);
                    m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
                }
                if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 512)
                {
                    WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 9);
                    unsigned int id = getEdgeID(point.x, point.y, point.z, 9);
                    m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
                }
            }
            // if (point.z == m_nCellsZ - 1)
            {
                if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 16)
                {
                    WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 4);
                    unsigned int id = getEdgeID(point.x, point.y, point.z, 4);
                    m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
                }
                if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 128)
                {
                    WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 7);
                    unsigned int id = getEdgeID(point.x, point.y, point.z, 7);
                    m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
                }
            }
            // if ((point.x == m_nCellsX - 1) && (point.y == m_nCellsY - 1))
            if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 1024)
            {
                WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 10);
                unsigned int id = getEdgeID(point.x, point.y, point.z, 10);
                m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
            }
            // if ((point.x == m_nCellsX - 1) && (point.z == m_nCellsZ - 1))
            if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 64)
            {
                WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 6);
                unsigned int id = getEdgeID(point.x, point.y, point.z, 6);
                m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
            }
            // if ((point.y == m_nCellsY - 1) && (point.z == m_nCellsZ - 1))
            if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 32)
            {
                WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 5);
                unsigned int id = getEdgeID(point.x, point.y, point.z, 5);
                m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
            }

            for (int i = 0; wMarchingCubesCaseTables::triTable[tableIndex][i] != -1; i += 3)
            {
                WAcceleratedMCTriangle triangle;
                unsigned int pointID0, pointID1, pointID2;
                pointID0 = getEdgeID(point.x, point.y, point.z, wMarchingCubesCaseTables::triTable[tableIndex][i]);
                pointID1 = getEdgeID(point.x, point.y, point.z, wMarchingCubesCaseTables::triTable[tableIndex][i + 1]);
                pointID2 = getEdgeID(point.x, point.y, point.z, wMarchingCubesCaseTables::triTable[tableIndex][i + 2]);
                triangle.pointID[0] = pointID0;
                triangle.pointID[1] = pointID1;
                triangle.pointID[2] = pointID2;
                m_trivecTriangles.push_back(triangle);
            }
        }
    }

    unsigned int nextID = 0;
    std::shared_ptr<WTriangleMesh> triMesh(new WTriangleMesh(m_idToVertices.size(), m_trivecTriangles.size()));

    // Rename vertices.
    ID2WAcceleratedPointXYZId::iterator mapIterator = m_idToVertices.begin();
    while (mapIterator != m_idToVertices.end())
    {
        WPosition texCoord = WPosition(mapIterator->second.x / nbCoordsX,
                                       mapIterator->second.y / nbCoordsY,
                                       mapIterator->second.z / nbCoordsZ);

        // transform from grid coordinate system to world coordinates
        WPosition pos = WPosition(mapIterator->second.x, mapIterator->second.y, mapIterator->second.z);

        std::vector<double> resultPos4D(4);
        resultPos4D[0] = m_matrix(0, 0) * pos[0] + m_matrix(0, 1) * pos[1] + m_matrix(0, 2) * pos[2] + m_matrix(0, 3) * 1;
        resultPos4D[1] = m_matrix(1, 0) * pos[0] + m_matrix(1, 1) * pos[1] + m_matrix(1, 2) * pos[2] + m_matrix(1, 3) * 1;
        resultPos4D[2] = m_matrix(2, 0) * pos[0] + m_matrix(2, 1) * pos[1] + m_matrix(2, 2) * pos[2] + m_matrix(2, 3) * 1;
        resultPos4D[3] = m_matrix(3, 0) * pos[0] + m_matrix(3, 1) * pos[1] + m_matrix(3, 2) * pos[2] + m_matrix(3, 3) * 1;

        (*mapIterator).second.newID = nextID;
        triMesh->addVertex(resultPos4D[0] / resultPos4D[3], resultPos4D[1] / resultPos4D[3], resultPos4D[2] / resultPos4D[3]);
        triMesh->addTextureCoordinate(texCoord);
        nextID++;
        mapIterator++;
    }

    // Now rename triangles.
    WAcceleratedMCTriangleVECTOR::iterator vecIterator = m_trivecTriangles.begin();
    while (vecIterator != m_trivecTriangles.end())
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            unsigned int newID = m_idToVertices[(*vecIterator).pointID[i]].newID;
            (*vecIterator).pointID[i] = newID;
        }
        triMesh->addTriangle((*vecIterator).pointID[0], (*vecIterator).pointID[1], (*vecIterator).pointID[2]);
        vecIterator++;
    }

    progress->finish();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time to generate with accelerated marching cubes: " << duration.count() << "ms" << std::endl;
    return triMesh;
}

template <typename T>
Octree WAcceleratedMarchingCubesAlgorithm::generateOctree(const std::vector<WAcceleratedPointXYZId> &points, double isoValue, const std::vector<T> *vals, std::vector<unsigned int> xCoordinatesSpan, std::vector<unsigned int> yCoordinatesSpan, std::vector<unsigned int> zCoordinatesSpan, unsigned int xCells, unsigned int yCells)
{
    Octree octree;
    if (points.size() <= 8)
    {
        octree.points = points;
        std::vector<double> minAndMax = getMinAndMax(points, vals, xCells, yCells);
        octree.min = minAndMax[0];
        octree.max = minAndMax[1];
        return octree;
    }

    std::vector<WAcceleratedPointXYZId> points1;
    std::vector<WAcceleratedPointXYZId> points2;
    std::vector<WAcceleratedPointXYZId> points3;
    std::vector<WAcceleratedPointXYZId> points4;
    std::vector<WAcceleratedPointXYZId> points5;
    std::vector<WAcceleratedPointXYZId> points6;
    std::vector<WAcceleratedPointXYZId> points7;
    std::vector<WAcceleratedPointXYZId> points8;

    for (const auto &point : points)
    {
        if (point.x < getMiddleOfCoordinatesSpan(xCoordinatesSpan))
        {
            if (point.y < getMiddleOfCoordinatesSpan(yCoordinatesSpan))
            {
                if (point.z < getMiddleOfCoordinatesSpan(zCoordinatesSpan))
                {
                    points1.push_back(point);
                }
                else
                {
                    points2.push_back(point);
                }
            }
            else
            {
                if (point.z < getMiddleOfCoordinatesSpan(zCoordinatesSpan))
                {
                    points3.push_back(point);
                }
                else
                {
                    points4.push_back(point);
                }
            }
        }
        else
        {
            if (point.y < getMiddleOfCoordinatesSpan(yCoordinatesSpan))
            {
                if (point.z < getMiddleOfCoordinatesSpan(zCoordinatesSpan))
                {
                    points5.push_back(point);
                }
                else
                {
                    points6.push_back(point);
                }
            }
            else
            {
                if (point.z < getMiddleOfCoordinatesSpan(zCoordinatesSpan))
                {
                    points7.push_back(point);
                }
                else
                {
                    points8.push_back(point);
                }
            }
        }
    }

    std::vector<std::vector<unsigned int>> dividedXCoordinatesSpan = getDividedCoordinatesSpan(xCoordinatesSpan);
    std::vector<unsigned int> xCoordinatesSpanFirstHalf = {dividedXCoordinatesSpan.front().front(), dividedXCoordinatesSpan.front().back()};
    std::vector<unsigned int> xCoordinatesSpanSecondHalf = {dividedXCoordinatesSpan.back().front(), dividedXCoordinatesSpan.back().back()};
    std::vector<std::vector<unsigned int>> dividedYCoordinatesSpan = getDividedCoordinatesSpan(yCoordinatesSpan);
    std::vector<unsigned int> yCoordinatesSpanFirstHalf = {dividedYCoordinatesSpan.front().front(), dividedYCoordinatesSpan.front().back()};
    std::vector<unsigned int> yCoordinatesSpanSecondHalf = {dividedYCoordinatesSpan.back().front(), dividedYCoordinatesSpan.back().back()};
    std::vector<std::vector<unsigned int>> dividedZCoordinatesSpan = getDividedCoordinatesSpan(zCoordinatesSpan);
    std::vector<unsigned int> zCoordinatesSpanFirstHalf = {dividedZCoordinatesSpan.front().front(), dividedZCoordinatesSpan.front().back()};
    std::vector<unsigned int> zCoordinatesSpanSecondHalf = {dividedZCoordinatesSpan.back().front(), dividedZCoordinatesSpan.back().back()};
    octree.children.push_back(generateOctree(points1, isoValue, vals, xCoordinatesSpanFirstHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanFirstHalf, xCells, yCells));
    octree.children.push_back(generateOctree(points2, isoValue, vals, xCoordinatesSpanFirstHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanSecondHalf, xCells, yCells));
    octree.children.push_back(generateOctree(points3, isoValue, vals, xCoordinatesSpanFirstHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanFirstHalf, xCells, yCells));
    octree.children.push_back(generateOctree(points4, isoValue, vals, xCoordinatesSpanFirstHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanSecondHalf, xCells, yCells));
    octree.children.push_back(generateOctree(points5, isoValue, vals, xCoordinatesSpanSecondHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanFirstHalf, xCells, yCells));
    octree.children.push_back(generateOctree(points6, isoValue, vals, xCoordinatesSpanSecondHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanSecondHalf, xCells, yCells));
    octree.children.push_back(generateOctree(points7, isoValue, vals, xCoordinatesSpanSecondHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanFirstHalf, xCells, yCells));
    octree.children.push_back(generateOctree(points8, isoValue, vals, xCoordinatesSpanSecondHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanSecondHalf, xCells, yCells));

    std::vector<double> minAndMax = octree.calculateMinAndMax();
    octree.min = minAndMax[0];
    octree.max = minAndMax[1];

    return octree;
}

template <typename T>
std::vector<T> WAcceleratedMarchingCubesAlgorithm::getMinAndMaxOfCell(WAcceleratedPointXYZId point, const std::vector<T> *vals, unsigned int xCells, unsigned int yCells)
{
    unsigned int nX = xCells + 1;
    unsigned int nY = yCells + 1;
    unsigned int nPointsInSlice = nX * nY;
    T minValue = (*vals)[point.z * nPointsInSlice + point.y * nX + point.x];
    T maxValue = (*vals)[point.z * nPointsInSlice + point.y * nX + point.x];
    T valueAtPoint1 = (*vals)[point.z * nPointsInSlice + point.y * nX + point.x];
    T valueAtPoint2 = (*vals)[point.z * nPointsInSlice + point.y * nX + (point.x + 1)];
    T valueAtPoint3 = (*vals)[point.z * nPointsInSlice + (point.y + 1) * nX + point.x];
    T valueAtPoint4 = (*vals)[point.z * nPointsInSlice + (point.y + 1) * nX + (point.x + 1)];
    T valueAtPoint5 = (*vals)[(point.z + 1) * nPointsInSlice + point.y * nX + point.x];
    T valueAtPoint6 = (*vals)[(point.z + 1) * nPointsInSlice + point.y * nX + (point.x + 1)];
    T valueAtPoint7 = (*vals)[(point.z + 1) * nPointsInSlice + (point.y + 1) * nX + point.x];
    T valueAtPoint8 = (*vals)[(point.z + 1) * nPointsInSlice + (point.y + 1) * nX + (point.x + 1)];
    if (valueAtPoint1 < minValue) {
        minValue = valueAtPoint1;
    } else if (valueAtPoint1 > maxValue) {
        maxValue = valueAtPoint1;
    }
    if (valueAtPoint2 < minValue) {
        minValue = valueAtPoint2;
    } else if (valueAtPoint2 > maxValue) {
        maxValue = valueAtPoint2;
    }
    if (valueAtPoint3 < minValue) {
        minValue = valueAtPoint3;
    } else if (valueAtPoint3 > maxValue) {
        maxValue = valueAtPoint3;
    }
    if (valueAtPoint4 < minValue) {
        minValue = valueAtPoint4;
    } else if (valueAtPoint4 > maxValue) {
        maxValue = valueAtPoint4;
    }
    if (valueAtPoint5 < minValue) {
        minValue = valueAtPoint5;
    } else if (valueAtPoint5 > maxValue) {
        maxValue = valueAtPoint5;
    }
    if (valueAtPoint6 < minValue) {
        minValue = valueAtPoint6;
    } else if (valueAtPoint6 > maxValue) {
        maxValue = valueAtPoint6;
    }
    if (valueAtPoint7 < minValue) {
        minValue = valueAtPoint7;
    } else if (valueAtPoint7 > maxValue) {
        maxValue = valueAtPoint7;
    }
    if (valueAtPoint8 < minValue) {
        minValue = valueAtPoint8;
    } else if (valueAtPoint8 > maxValue) {
        maxValue = valueAtPoint8;
    }

    return {minValue, maxValue};
}


template <typename T>
std::vector<double> WAcceleratedMarchingCubesAlgorithm::getMinAndMax(const std::vector<WAcceleratedPointXYZId> &points, const std::vector<T> *vals, unsigned int xCells, unsigned int yCells)
{

    unsigned int nX = xCells + 1;
    unsigned int nY = yCells + 1;
    unsigned int nPointsInSlice = nX * nY;
    if (points.size() == 0)
    {
        return {};
    }
    else if (points.size() == 1)
    {
        return {(*vals)[points.front().z * nPointsInSlice + points.front().y * nX + points.front().x], (*vals)[points.front().z * nPointsInSlice + points.front().y * nX + points.front().x]};
    }

    double minValue = (*vals)[points.front().z * nPointsInSlice + points.front().y * nX + points.front().x];
    double maxValue = (*vals)[points.front().z * nPointsInSlice + points.front().y * nX + points.front().x];
    for (auto &point : points)
    {
        std::vector<double> minAndMax = getMinAndMaxOfCell<double>(point, vals, xCells, yCells);
        double currentMinValue = minAndMax[0];
        double currentMaxValue = minAndMax[1];
        if (currentMinValue < minValue)
        {
            minValue = currentMinValue;
        }
        if (currentMaxValue > maxValue)
        {
            maxValue = currentMaxValue;
        }
    }
    return {minValue, maxValue};
}

template <typename T>
bool WAcceleratedMarchingCubesAlgorithm::isInside(const std::vector<WAcceleratedPointXYZId> &points, double isoValue, const std::vector<T> *vals)
{
    if (points.size() == 0)
    {
        return false;
    }
    else if (points.size() == 1)
    {
        return true;
    }
    // if (points.size() <= 8)
    // {
    //     return true;
    // }

    unsigned int nX = m_nCellsX + 1;
    unsigned int nY = m_nCellsY + 1;

    unsigned int nPointsInSlice = nX * nY;

    T firstValue = (*vals)[points[0].z * nPointsInSlice + points[0].y * nX + points[0].x];
    T lowestValue = firstValue;
    T highestValue = firstValue;

    for (const auto &point : points)
    {
        T currentVal = (*vals)[point.z * nPointsInSlice + point.y * nX + point.x];
        if (currentVal < lowestValue)
        {
            lowestValue = currentVal;
        }
        else if (currentVal > highestValue)
        {
            highestValue = currentVal;
        }
    }

    return lowestValue <= isoValue && highestValue >= isoValue;
}

template <typename T>
WAcceleratedPointXYZId WAcceleratedMarchingCubesAlgorithm::calculateIntersection(const std::vector<T> *vals,
                                                                                 unsigned int nX, unsigned int nY, unsigned int nZ,
                                                                                 unsigned int nEdgeNo)
{
    double x1;
    double y1;
    double z1;

    double x2;
    double y2;
    double z2;

    unsigned int v1x = nX;
    unsigned int v1y = nY;
    unsigned int v1z = nZ;

    unsigned int v2x = nX;
    unsigned int v2y = nY;
    unsigned int v2z = nZ;

    switch (nEdgeNo)
    {
    case 0:
        v2y += 1;
        break;
    case 1:
        v1y += 1;
        v2x += 1;
        v2y += 1;
        break;
    case 2:
        v1x += 1;
        v1y += 1;
        v2x += 1;
        break;
    case 3:
        v1x += 1;
        break;
    case 4:
        v1z += 1;
        v2y += 1;
        v2z += 1;
        break;
    case 5:
        v1y += 1;
        v1z += 1;
        v2x += 1;
        v2y += 1;
        v2z += 1;
        break;
    case 6:
        v1x += 1;
        v1y += 1;
        v1z += 1;
        v2x += 1;
        v2z += 1;
        break;
    case 7:
        v1x += 1;
        v1z += 1;
        v2z += 1;
        break;
    case 8:
        v2z += 1;
        break;
    case 9:
        v1y += 1;
        v2y += 1;
        v2z += 1;
        break;
    case 10:
        v1x += 1;
        v1y += 1;
        v2x += 1;
        v2y += 1;
        v2z += 1;
        break;
    case 11:
        v1x += 1;
        v2x += 1;
        v2z += 1;
        break;
    }

    x1 = v1x;
    y1 = v1y;
    z1 = v1z;
    x2 = v2x;
    y2 = v2y;
    z2 = v2z;

    unsigned int nPointsInSlice = (m_nCellsX + 1) * (m_nCellsY + 1);
    double val1 = (*vals)[v1z * nPointsInSlice + v1y * (m_nCellsX + 1) + v1x];
    double val2 = (*vals)[v2z * nPointsInSlice + v2y * (m_nCellsX + 1) + v2x];

    WAcceleratedPointXYZId intersection = interpolate(x1, y1, z1, x2, y2, z2, val1, val2);
    intersection.newID = 0;
    return intersection;
}

#endif // WACCELERATEDMARCHINGCUBESALGORITHM_H
