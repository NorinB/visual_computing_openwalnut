#include <vector>
#include <iostream>

#include "Octree.h"

Octree::Octree()
{
}

std::vector<WAcceleratedPointXYZId> Octree::getPointsIncludingIsoValue(double isoValue)
{
    if (this->min > isoValue || this->max < isoValue)
    {
        return {};
    }

    if (this->children.size() == 0)
    {
        return this->points;
    }

    std::vector<WAcceleratedPointXYZId> points;
    for (int i = 0; i < this->children.size(); i++)
    {
        std::vector<WAcceleratedPointXYZId> childPoints = this->children[i].getPointsIncludingIsoValue(isoValue);
        points.insert(points.end(), childPoints.begin(), childPoints.end());
    }
    return points;
}

std::vector<double> Octree::calculateMinAndMax()
{
    if (children.size() != 0)
    {
        double currentMin = this->children[0].min;
        double currentMax = this->children[0].max;
        for (int i = 0; i < this->children.size(); i++)
        {
            if (this->children[i].min < currentMin)
            {
                currentMin = this->children[i].min;
            }
            if (this->children[i].max > currentMax)
            {
                currentMax = this->children[i].max;
            }
        }
        return {currentMin, currentMax};
    }
    else
    {
        return {this->min, this->max};
    }
}

unsigned int Octree::countPoints()
{
    if (this->children.size() == 0)
    {
        return this->points.size();
    }
    else
    {
        unsigned int count = 0;
        for (int i = 0; i < this->children.size(); i++)
        {
            count += this->children[i].countPoints();
        }
        return count;
    }
}