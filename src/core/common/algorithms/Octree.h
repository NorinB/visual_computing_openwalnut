#ifndef OCTREE_H
#define OCTREE_H

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <numeric>

#include "WAcceleratedMarchingCubesAlgorithm.h"

class Octree
{
public:
  Octree();
  std::vector<WAcceleratedPointXYZId> getPointsIncludingIsoValue(double isoValue);

private:
  double min;
  double max;
  std::vector<Octree> children;
  std::vector<WAcceleratedPointXYZId> points;
};

#endif