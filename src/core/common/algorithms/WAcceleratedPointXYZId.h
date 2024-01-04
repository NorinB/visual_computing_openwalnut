#ifndef WACCELERATEDPOINTXYZID_H
#define WACCELERATEDPOINTXYZID_H

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

#endif