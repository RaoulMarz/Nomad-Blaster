#ifndef CPP_MVECTOR2D_H
#define CPP_MVECTOR2D_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

struct MVector2d
{
    int x = 0;
    int y = 0;
    
    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    MVector2d operator-(MVector2d another)
    {
        return MVector2d{x - another.x, y - another.y};
    }

    MVector2d operator+(MVector2d another)
    {
        return MVector2d{x + another.x, y + another.y};
    }

    bool equals(MVector2d another)
    {
        return (x == another.x) && (y == another.y);
    }

    bool compare(std::string compareToken, MVector2d another)
    {
        bool res = false;
        if (compareToken == "=")
            res = equals(another);
        if (compareToken == ">")
            res = (x > another.x) && (y > another.y);
        if (compareToken == "<")
            res = (x < another.x) && (y < another.y);
        if (compareToken == ">=")
            res = (x >= another.x) && (y >= another.y);
        if (compareToken == "<=")
            res = (x <= another.x) && (y <= another.y);
        return res;
    }

    int distance()
    {
        return (int)sqrt(x*x + y*y);
    }

    std::string toString()
    {
        std::stringstream ss;
        ss << "<" << x << "," << y << ">";
        return ss.str();
    }
};

#endif //CPP_MVECTOR2D_H