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

#include "../WProgressCombiner.h"
#include "../math/WMatrix.h"
#include "WMarchingCubesCaseTables.h"
#include "core/graphicsEngine/WTriangleMesh.h"

/**
 * A point consisting of its coordinates and ID
 */
struct WAcceleratedPointXYZId
{
    unsigned int newID; //!< ID of the point
    double x;           //!< x coordinates of the point.
    double y;           //!< y coordinates of the point.
    double z;           //!< z coordinates of the point.
};

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
     *
     * \return the genereated surface
     */
    template <typename T>
    std::shared_ptr<WTriangleMesh> generateSurfaceOriginal(size_t nbCoordsX, size_t nbCoordsY, size_t nbCoordsZ,
                                                           const WMatrix<double> &mat,
                                                           const std::vector<T> *vals,
                                                           double isoValue,
                                                           std::shared_ptr<WProgressCombiner> mainProgress);

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
     *
     * \return the genereated surface
     */
    template <typename T>
    std::shared_ptr<WTriangleMesh> generateSurface(size_t nbCoordsX, size_t nbCoordsY, size_t nbCoordsZ,
                                                   const WMatrix<double> &mat,
                                                   const std::vector<T> *vals,
                                                   double isoValue,
                                                   std::shared_ptr<WProgressCombiner> mainProgress);

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
std::shared_ptr<WTriangleMesh> WAcceleratedMarchingCubesAlgorithm::generateSurface(size_t nbCoordsX, size_t nbCoordsY, size_t nbCoordsZ,
                                                                                   const WMatrix<double> &mat,
                                                                                   const std::vector<T> *vals,
                                                                                   double isoValue,
                                                                                   std::shared_ptr<WProgressCombiner> mainProgress)
{
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
    unsigned int index = 0;
    for (unsigned int z = 0; z < m_nCellsZ; z++)
    {
        for (unsigned int y = 0; y < m_nCellsY; y++)
        {
            for (unsigned int x = 0; x < m_nCellsX; x++)
            {
                WAcceleratedPointXYZId point;
                point.newID = index;
                point.x = x;
                point.y = y;
                point.z = z;
                points.push_back(point);
            }
        }
        index++;
    }

    std::cout << points.back().x << " - " << points.back().y << " - " << points.back().z << std::endl;

    std::cout << "points.size() am Anfang = " << points.size() << std::endl;
    std::vector<unsigned int> xCoordinatesSpan = {0, m_nCellsX};
    std::vector<unsigned int> yCoordinatesSpan = {0, m_nCellsY};
    std::vector<unsigned int> zCoordinatesSpan = {0, m_nCellsZ};
    // std::vector<unsigned int> xCoordinatesSpan(m_nCellsX + 1);
    // std::iota(xCoordinatesSpan.begin(), xCoordinatesSpan.end(), 0);
    // std::vector<unsigned int> yCoordinatesSpan(m_nCellsY + 1);
    // std::iota(yCoordinatesSpan.begin(), yCoordinatesSpan.end(), 0);
    // std::vector<unsigned int> zCoordinatesSpan(m_nCellsZ + 1);
    // std::iota(zCoordinatesSpan.begin(), zCoordinatesSpan.end(), 0);
    // std::cout << "x coordinates: " << m_nCellsX << std::endl;
    // std::cout << "xCoordinatesSpan.size() = " << xCoordinatesSpan.size() << std::endl;
    // std::cout << "xCoordinatesSpan = " << xCoordinatesSpan[0] << " - " << xCoordinatesSpan[xCoordinatesSpan.size() - 1] << std::endl;
    // std::cout << "y coordinates: " << m_nCellsY << std::endl;
    // std::cout << "yCoordinatesSpan.size() = " << yCoordinatesSpan.size() << std::endl;
    // std::cout << "yCoordinatesSpan = " << yCoordinatesSpan[0] << " - " << yCoordinatesSpan[yCoordinatesSpan.size() - 1] << std::endl;
    // std::cout << "z coordinates: " << m_nCellsZ << std::endl;
    // std::cout << "zCoordinatesSpan.size() = " << zCoordinatesSpan.size() << std::endl;
    // std::cout << "zCoordinatesSpan = " << zCoordinatesSpan[0] << " - " << zCoordinatesSpan[zCoordinatesSpan.size() - 1] << std::endl;

    std::cout << "isoValue = " << isoValue << std::endl;
    points = calculateOctree(points, isoValue, vals, xCoordinatesSpan, yCoordinatesSpan, zCoordinatesSpan);
    std::cout << "points.size() nach Octree-Berechnung = " << points.size() << std::endl;

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

            if (point.x == m_nCellsX - 1)
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
            if (point.y == m_nCellsY - 1)
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
            if (point.z == m_nCellsZ - 1)
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
            if ((point.x == m_nCellsX - 1) && (point.y == m_nCellsY - 1))
                if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 1024)
                {
                    WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 10);
                    unsigned int id = getEdgeID(point.x, point.y, point.z, 10);
                    m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
                }
            if ((point.x == m_nCellsX - 1) && (point.z == m_nCellsZ - 1))
                if (wMarchingCubesCaseTables::edgeTable[tableIndex] & 64)
                {
                    WAcceleratedPointXYZId pt = calculateIntersection(vals, point.x, point.y, point.z, 6);
                    unsigned int id = getEdgeID(point.x, point.y, point.z, 6);
                    m_idToVertices.insert(ID2WAcceleratedPointXYZId::value_type(id, pt));
                }
            if ((point.y == m_nCellsY - 1) && (point.z == m_nCellsZ - 1))
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
    return triMesh;
}

template <typename T>
std::vector<WAcceleratedPointXYZId> WAcceleratedMarchingCubesAlgorithm::calculateOctree(const std::vector<WAcceleratedPointXYZId> &points, double isoValue, const std::vector<T> *vals, std::vector<unsigned int> xCoordinatesSpan, std::vector<unsigned int> yCoordinatesSpan, std::vector<unsigned int> zCoordinatesSpan)
{
    // std::cout << "calculateOctree:" << std::endl;
    // std::cout << "points.size(): " << points.size() << std::endl;
    // std::cout << "xCoordinatesSpan: " << xCoordinatesSpan[0] << " - " << xCoordinatesSpan[1] << std::endl;
    // std::cout << "yCoordinatesSpan: " << yCoordinatesSpan[0] << " - " << yCoordinatesSpan[1] << std::endl;
    // std::cout << "zCoordinatesSpan: " << zCoordinatesSpan[0] << " - " << zCoordinatesSpan[1] << std::endl;

    std::vector<WAcceleratedPointXYZId> result;
    if (points.size() == 1)
    {
        result.push_back(points.front());
        return result;
    }
    else if (points.size() == 0)
    {
        return result;
    }
    // if (points.size() < 8)
    // {
    //     result.insert(result.end(), points.begin(), points.end());
    //     return result;
    // }

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
    std::vector<unsigned int> xCoordinatesSpanFirstHalf;
    std::vector<unsigned int> xCoordinatesSpanSecondHalf;
    if (dividedXCoordinatesSpan[1].size() != 2)
    {
        // std::cout << "dividedXCoordinatesSpan[1].size(): " << dividedXCoordinatesSpan[1].size() << std::endl;
        xCoordinatesSpanFirstHalf = {dividedXCoordinatesSpan.front().front(), dividedXCoordinatesSpan.front().back()};
    }
    else
    {
        xCoordinatesSpanFirstHalf = {dividedXCoordinatesSpan.front().front(), dividedXCoordinatesSpan.front().back()};
        xCoordinatesSpanSecondHalf = {dividedXCoordinatesSpan.back().front(), dividedXCoordinatesSpan.back().back()};
    }
    // std::cout << "xCoordinatesSpan = " << xCoordinatesSpan[0] << " - " << xCoordinatesSpan[1] << std::endl;
    // std::cout << "xCoordinatesSpanFirstHalf = " << xCoordinatesSpanFirstHalf[0] << " - " << xCoordinatesSpanFirstHalf[1] << std::endl;
    // std::cout << "xCoordinatesSpanSecondHalf = " << xCoordinatesSpanSecondHalf[0] << " - " << xCoordinatesSpanSecondHalf[1] << std::endl;

    std::vector<std::vector<unsigned int>> dividedYCoordinatesSpan = getDividedCoordinatesSpan(yCoordinatesSpan);
    std::vector<unsigned int> yCoordinatesSpanFirstHalf;
    std::vector<unsigned int> yCoordinatesSpanSecondHalf;
    if (dividedYCoordinatesSpan[1].size() != 2)
    {
        // std::cout << "dividedYCoordinatesSpan[1].size(): " << dividedYCoordinatesSpan[1].size() << std::endl;
        yCoordinatesSpanFirstHalf = {dividedYCoordinatesSpan.front().front(), dividedYCoordinatesSpan.front().back()};
    }
    else
    {
        yCoordinatesSpanFirstHalf = {dividedYCoordinatesSpan.front().front(), dividedYCoordinatesSpan.front().back()};
        yCoordinatesSpanSecondHalf = {dividedYCoordinatesSpan.back().front(), dividedYCoordinatesSpan.back().back()};
    }
    // std::cout << "yCoordinatesSpan = " << yCoordinatesSpan[0] << " - " << yCoordinatesSpan[1] << std::endl;
    // std::cout << "yCoordinatesSpanFirstHalf = " << yCoordinatesSpanFirstHalf[0] << " - " << yCoordinatesSpanFirstHalf[1] << std::endl;
    // std::cout << "yCoordinatesSpanSecondHalf = " << yCoordinatesSpanSecondHalf[0] << " - " << yCoordinatesSpanSecondHalf[1] << std::endl;

    std::vector<std::vector<unsigned int>> dividedZCoordinatesSpan = getDividedCoordinatesSpan(zCoordinatesSpan);
    std::vector<unsigned int> zCoordinatesSpanFirstHalf;
    std::vector<unsigned int> zCoordinatesSpanSecondHalf;
    if (dividedZCoordinatesSpan[1].size() != 2)
    {
        // std::cout << "dividedZCoordinatesSpan[1].size(): " << dividedZCoordinatesSpan[1].size() << std::endl;
        zCoordinatesSpanFirstHalf = {dividedZCoordinatesSpan.front().front(), dividedZCoordinatesSpan.front().back()};
    }
    else
    {
        zCoordinatesSpanFirstHalf = {dividedZCoordinatesSpan.front().front(), dividedZCoordinatesSpan.front().back()};
        zCoordinatesSpanSecondHalf = {dividedZCoordinatesSpan.back().front(), dividedZCoordinatesSpan.back().back()};
    }
    // std::cout << "zCoordinatesSpan = " << zCoordinatesSpan[0] << " - " << zCoordinatesSpan[1] << std::endl;
    // std::cout << "zCoordinatesSpanFirstHalf = " << zCoordinatesSpanFirstHalf[0] << " - " << zCoordinatesSpanFirstHalf[1] << std::endl;
    // std::cout << "zCoordinatesSpanSecondHalf = " << zCoordinatesSpanSecondHalf[0] << " - " << zCoordinatesSpanSecondHalf[1] << std::endl << std::endl;

    // std::cout << "xCoordinatesSpanFirstHalf[1].size(): " << xCoordinatesSpanFirstHalf[1].size() << std::endl;
    // std::cout << "xCoordinatesSpanSecondHalf[1].size(): " << xCoordinatesSpanSecondHalf[1].size() << std::endl;
    // std::cout << "yCoordinatesSpanFirstHalf[1].size(): " << yCoordinatesSpanFirstHalf[1].size() << std::endl;
    // std::cout << "yCoordinatesSpanSecondHalf[1].size(): " << yCoordinatesSpanSecondHalf[1].size() << std::endl;
    // std::cout << "zCoordinatesSpanFirstHalf[1].size(): " << zCoordinatesSpanFirstHalf[1].size() << std::endl;
    // std::cout << "zCoordinatesSpanSecondHalf[1].size(): " << zCoordinatesSpanSecondHalf[1].size() << std::endl << std::endl;

    // int midX = xCoordinatesSpan.size() / 2;
    // int midY = yCoordinatesSpan.size() / 2;
    // int midZ = zCoordinatesSpan.size() / 2;
    // std::vector<unsigned int> xCoordinatesSpanFirstHalf(xCoordinatesSpan.begin(), xCoordinatesSpan.begin() + midX);
    // std::vector<unsigned int> yCoordinatesSpanFirstHalf(yCoordinatesSpan.begin(), yCoordinatesSpan.begin() + midY);
    // std::vector<unsigned int> zCoordinatesSpanFirstHalf(zCoordinatesSpan.begin(), zCoordinatesSpan.begin() + midZ);
    // std::vector<unsigned int> xCoordinatesSpanSecondHalf(xCoordinatesSpan.begin() + midX, xCoordinatesSpan.end());
    // std::vector<unsigned int> yCoordinatesSpanSecondHalf(yCoordinatesSpan.begin() + midY, yCoordinatesSpan.end());
    // std::vector<unsigned int> zCoordinatesSpanSecondHalf(zCoordinatesSpan.begin() + midZ, zCoordinatesSpan.end());
    // std::cout << "points1.size() = " << points1.size() << std::endl;
    // std::cout << "points2.size() = " << points2.size() << std::endl;
    // std::cout << "points3.size() = " << points3.size() << std::endl;
    // std::cout << "points4.size() = " << points4.size() << std::endl;
    // std::cout << "points5.size() = " << points5.size() << std::endl;
    // std::cout << "points6.size() = " << points6.size() << std::endl;
    // std::cout << "points7.size() = " << points7.size() << std::endl;
    // std::cout << "points8.size() = " << points8.size() << std::endl;
    // std::cout << "gesamt berechnet: " << points1.size() + points2.size() + points3.size() + points4.size() + points5.size() + points6.size() + points7.size() + points8.size() << std::endl;
    // std::cout << "xCoordinates: " << xCoordinatesSpan[0] << " - " << xCoordinatesSpan[1] << std::endl;
    // std::cout << "yCoordinates: " << yCoordinatesSpan[0] << " - " << yCoordinatesSpan[1] << std::endl;
    // std::cout << "zCoordinates: " << zCoordinatesSpan[0] << " - " << zCoordinatesSpan[1] << std::endl;
    // std::cout << "xCoordinatesSpanFirstHalf = " << xCoordinatesSpanFirstHalf[0] << " - " << xCoordinatesSpanFirstHalf[1] << std::endl;
    // std::cout << "xCoordinatesSpanSecondHalf = " << xCoordinatesSpanSecondHalf[0] << " - " << xCoordinatesSpanSecondHalf[1] << std::endl;
    // std::cout << "yCoordinatesSpanFirstHalf = " << yCoordinatesSpanFirstHalf[0] << " - " << yCoordinatesSpanFirstHalf[1] << std::endl;
    // std::cout << "yCoordinatesSpanSecondHalf = " << yCoordinatesSpanSecondHalf[0] << " - " << yCoordinatesSpanSecondHalf[1] << std::endl;
    // std::cout << "zCoordinatesSpanFirstHalf = " << zCoordinatesSpanFirstHalf[0] << " - " << zCoordinatesSpanFirstHalf[1] << std::endl;
    // std::cout << "zCoordinatesSpanSecondHalf = " << zCoordinatesSpanSecondHalf[0] << " - " << zCoordinatesSpanSecondHalf[1] << std::endl;

    if (points1.size() > 0)
    {
        // std::cout << "points1.size() = " << points1.size() << std::endl;
        // std::cout << std::endl;
        bool inside = isInside(points1, isoValue, vals);
        if (inside)
        {
            // std::cout << "points1 sind inside" << std::endl;
            if (isOnlyOneBlock(xCoordinatesSpanFirstHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanFirstHalf))
            {
                // std::cout << "is only one block" << std::endl;
                result.insert(result.end(), points1.begin(), points1.end());
            }
            else
            {
                std::vector<WAcceleratedPointXYZId> octreeResult = calculateOctree(points1, isoValue, vals, xCoordinatesSpanFirstHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanFirstHalf);
                result.insert(result.end(), octreeResult.begin(), octreeResult.end());
            }
        }
        // else
        // {
        //     std::cout << "points1 sind nicht inside" << std::endl;
        // }
    }
    if (points2.size() > 0)
    {
        // std::cout << "points2.size() = " << points2.size() << std::endl;
        if (!zCoordinatesSpanSecondHalf.empty())
        {
            bool inside = isInside(points2, isoValue, vals);
            if (inside)
            {

                if (isOnlyOneBlock(xCoordinatesSpanFirstHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanSecondHalf))
                {
                    result.insert(result.end(), points2.begin(), points2.end());
                }
                else
                {
                    // std::cout << "points2 sind inside" << std::endl;
                    std::vector<WAcceleratedPointXYZId> octreeResult = calculateOctree(points2, isoValue, vals, xCoordinatesSpanFirstHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanSecondHalf);
                    result.insert(result.end(), octreeResult.begin(), octreeResult.end());
                }
            }
        }
        // else
        // {
        //     std::cout << "points2 sind nicht inside" << std::endl;
        // }
    }
    if (points3.size() > 0)
    {
        // std::cout << "points3.size() = " << points3.size() << std::endl;
        if (!yCoordinatesSpanSecondHalf.empty())
        {
            bool inside = isInside(points3, isoValue, vals);
            if (inside)
            {
                if (isOnlyOneBlock(xCoordinatesSpanFirstHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanFirstHalf))
                {
                    result.insert(result.end(), points3.begin(), points3.end());
                }
                else
                {
                    // std::cout << "points3 sind inside" << std::endl;
                    std::vector<WAcceleratedPointXYZId> octreeResult = calculateOctree(points3, isoValue, vals, xCoordinatesSpanFirstHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanFirstHalf);
                    result.insert(result.end(), octreeResult.begin(), octreeResult.end());
                }
            }
        }
        // else
        // {
        //     std::cout << "points3 sind nicht inside" << std::endl;
        // }
    }
    if (points4.size() > 0)
    {
        // std::cout << "points4.size() = " << points4.size() << std::endl;
        if (!yCoordinatesSpanSecondHalf.empty() && !zCoordinatesSpanSecondHalf.empty())
        {
            bool inside = isInside(points4, isoValue, vals);
            if (inside)
            {
                if (isOnlyOneBlock(xCoordinatesSpanFirstHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanSecondHalf))
                {
                    result.insert(result.end(), points4.begin(), points4.end());
                }
                else
                {
                    // std::cout << "points4 sind inside" << std::endl;
                    std::vector<WAcceleratedPointXYZId> octreeResult = calculateOctree(points4, isoValue, vals, xCoordinatesSpanFirstHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanSecondHalf);
                    result.insert(result.end(), octreeResult.begin(), octreeResult.end());
                }
            }
        }
        // else
        // {
        //     std::cout << "points4 sind nicht inside" << std::endl;
        // }
    }
    if (points5.size() > 0)
    {
        // std::cout << "points5.size() = " << points5.size() << std::endl;
        if (!xCoordinatesSpanSecondHalf.empty())
        {
            bool inside = isInside(points5, isoValue, vals);
            if (inside)
            {
                if (isOnlyOneBlock(xCoordinatesSpanSecondHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanFirstHalf))
                {
                    result.insert(result.end(), points5.begin(), points5.end());
                }
                else
                {
                    // std::cout << "points5 sind inside" << std::endl;
                    std::vector<WAcceleratedPointXYZId> octreeResult = calculateOctree(points5, isoValue, vals, xCoordinatesSpanSecondHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanFirstHalf);
                    result.insert(result.end(), octreeResult.begin(), octreeResult.end());
                }
            }
        }
        // else
        // {
        //     std::cout << "points5 sind nicht inside" << std::endl;
        // }
    }
    if (points6.size() > 0)
    {
        // std::cout << "points6.size() = " << points6.size() << std::endl;
        if (!xCoordinatesSpanSecondHalf.empty() && !zCoordinatesSpanSecondHalf.empty())
        {
            bool inside = isInside(points6, isoValue, vals);
            if (inside)
            {
                if (isOnlyOneBlock(xCoordinatesSpanSecondHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanSecondHalf))
                {
                    result.insert(result.end(), points6.begin(), points6.end());
                }
                else
                {
                    // std::cout << "points6 sind inside" << std::endl;
                    std::vector<WAcceleratedPointXYZId> octreeResult = calculateOctree(points6, isoValue, vals, xCoordinatesSpanSecondHalf, yCoordinatesSpanFirstHalf, zCoordinatesSpanSecondHalf);
                    result.insert(result.end(), octreeResult.begin(), octreeResult.end());
                }
            }
        }
        // else
        // {
        //     std::cout << "points6 sind nicht inside" << std::endl;
        // }
    }
    if (points7.size() > 0)
    {
        // std::cout << "points7.size() = " << points7.size() << std::endl;
        if (!xCoordinatesSpanSecondHalf.empty() && !yCoordinatesSpanSecondHalf.empty())
        {
            bool inside = isInside(points7, isoValue, vals);
            if (inside)
            {
                if (isOnlyOneBlock(xCoordinatesSpanSecondHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanFirstHalf))
                {
                    result.insert(result.end(), points7.begin(), points7.end());
                }
                else
                {
                    // std::cout << "points7 sind inside" << std::endl;
                    std::vector<WAcceleratedPointXYZId> octreeResult = calculateOctree(points7, isoValue, vals, xCoordinatesSpanSecondHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanFirstHalf);
                    result.insert(result.end(), octreeResult.begin(), octreeResult.end());
                }
            }
        }
        // else
        // {
        //     std::cout << "points7 sind nicht inside" << std::endl;
        // }
    }
    if (points8.size() > 0)
    {
        // std::cout << "points8.size() = " << points8.size() << std::endl;
        if (!xCoordinatesSpanSecondHalf.empty() && !yCoordinatesSpanSecondHalf.empty() && !zCoordinatesSpanSecondHalf.empty())
        {
            bool inside = isInside(points8, isoValue, vals);
            if (inside)
            {
                if (isOnlyOneBlock(xCoordinatesSpanSecondHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanSecondHalf))
                {
                    result.insert(result.end(), points8.begin(), points8.end());
                }
                else
                {
                    // std::cout << "points8 sind inside" << std::endl;
                    std::vector<WAcceleratedPointXYZId> octreeResult = calculateOctree(points8, isoValue, vals, xCoordinatesSpanSecondHalf, yCoordinatesSpanSecondHalf, zCoordinatesSpanSecondHalf);
                    result.insert(result.end(), octreeResult.begin(), octreeResult.end());
                }
            }
        }
        // else
        // {
        //     std::cout << "points8 sind nicht inside" << std::endl;
        // }
    }
    return result;
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

    // std::cout << "lowestValue = " << lowestValue << std::endl;
    // std::cout << "highestValue = " << highestValue << std::endl;
    // std::cout << "ist dazwischen: " << (lowestValue <= isoValue && highestValue >= isoValue) << std::endl << std::endl;

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
