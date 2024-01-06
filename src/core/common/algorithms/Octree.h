#ifndef OCTREE_H
#define OCTREE_H

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <numeric>

#include "WAcceleratedPointXYZId.h"

class Octree
{
public:
  Octree();
  std::vector<WAcceleratedPointXYZId> getPointsIncludingIsoValue(double isoValue);
  std::vector<double> calculateMinAndMax();
  void print();
  unsigned int countPoints();
  double min;
  double max;
  std::vector<Octree> children;
  std::vector<WAcceleratedPointXYZId> points;
};

#endif