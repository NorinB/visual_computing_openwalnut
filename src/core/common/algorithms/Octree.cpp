#include <vector>

#include "Octree.h"

Octree::Octree()
{
}

std::vector<WAcceleratedPointXYZId> Octree::getPointsIncludingIsoValue(double isoValue)
{
    if (min > isoValue || max < isoValue) {
        return {};
    }

    if (children.size() == 0) {
        return this->points;
    }

    std::vector<WAcceleratedPointXYZId> points;
    for (int i = 0; i < children.size(); i++) {
        std::vector<WAcceleratedPointXYZId> childPoints = children[i].getPointsIncludingIsoValue(isoValue);
        points.insert(points.end(), childPoints.begin(), childPoints.end());
    }
    return points;
}