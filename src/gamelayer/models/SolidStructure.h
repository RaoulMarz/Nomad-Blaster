#ifndef CPP_SOLIDSTRUCTURE_H
#define CPP_SOLIDSTRUCTURE_H

#include <string>
#include <vector>
#include <iostream>
#include "MVector2d.h"
#include "AxisOrientation.h"

struct SolidStructure
{
    MVector2d startPosition;
    MVector2d endPosition;
    AxisOrientation orientation;
    int extent;

    MVector2d getClosestDistanceToStructure(MVector2d fromCoordinate)
    {
        MVector2d res{-1, -1};
        MVector2d vectDistStart = startPosition - fromCoordinate;
        MVector2d vectDistEnd = endPosition - fromCoordinate;
        if (orientation == AxisOrientation::Horizontal)
        {
            if (vectDistStart.distance() <= vectDistEnd.distance())
            {
            }
        }
        if (orientation == AxisOrientation::Vertical)
        {
            if (vectDistStart.distance() <= vectDistEnd.distance())
            {
            }
        }
        return res;
    }
};

#endif