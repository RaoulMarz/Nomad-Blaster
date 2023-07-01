#ifndef CPP_GRIDCOORD_STORE_H
#define CPP_GRIDCOORD_STORE_H

#include <string>
#include <vector>
#include <iostream>
#include "MVector2d.h"

template <typename T>
class GridCoordinateStore
{
public:
    GridCoordinateStore(MVector2d coord, T value)
    {
        coordinate = coord;
        storeValue = value;
    }

    MVector2d getCoordinate()
    {
        return coordinate;
    }

    T getStoreValue()
    {
        return storeValue;
    }

    bool storedMatches(T value)
    {
        return value == storeValue;
    }

private:
    MVector2d coordinate;
    T storeValue;
};

#endif // CPP_GRIDCOORD_STORE_H