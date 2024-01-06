#include <vector>
#include <iostream>

#include "Octree.h"

Octree::Octree()
{
}

std::vector<WAcceleratedPointXYZId> Octree::getPointsIncludingIsoValue(double isoValue)
{
    if (this->min > this->max)
    {
        std::cout << "min ist größer als max: " << this->min << " max: " << this->max << std::endl;
    }
    // std::cout << isoValue << std::endl;
    // std::cout << "min: " << this->min << " max: " << this->max << std::endl;
    if (this->min > isoValue || this->max < isoValue)
    {
    std::cout << "min: " << this->min << ", isoValue: " << isoValue << ", max: " << this->max << std::endl;
        return {};
    }

    // std::cout << "wir habe nes nach den ersten check geschafft" << std::endl;

    if (this->children.size() == 0)
    {
        return this->points;
    }

    // std::cout << "children sind auch nicht 0" << std::endl;

    std::vector<WAcceleratedPointXYZId> points;
    for (int i = 0; i < this->children.size(); i++)
    {
        std::vector<WAcceleratedPointXYZId> childPoints = this->children[i].getPointsIncludingIsoValue(isoValue);
        points.insert(points.end(), childPoints.begin(), childPoints.end());
    }
    // std::cout << "points nach der Berechnung von den children size: " << points.size() << std::endl;
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

void Octree::print()
{
    if (this->min > this->max)
    {
        std::cout << "min ist größer als max: " << this->min << " max: " << this->max << std::endl;
    }
    // std::cout << "min: " << this->min << " max: " << this->max << std::endl;
    if (this->children.size() != 0)
    {
        // std::cout << "children: " << this->children.size() << std::endl;
        // std::cout << "hat also keine points: " << this->points.size() << std::endl;
        if (this->points.size() != 0)
        {
            std::cout << "check, dass children aber keine points: " << ((this->points.size() == 0) && (this->children.size() != 0)) << std::endl;
        }
        // std::cout << "check, dass children aber keine points: " << ((this->points.size() == 0) && (this->children.size() != 0)) << std::endl;
        for (int i = 0; i < this->children.size(); i++)
        {
            this->children[i].print();
        }
    }
    else
    {
        // std::cout << "hat keine children: " << this->children.size() << std::endl;
        // std::cout << "points: " << this->points.size() << std::endl << std::endl;
        // std::cout << "check, dass points aber keine children: " << ((this->points.size() != 0) && (this->children.size() == 0)) << std::endl;
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