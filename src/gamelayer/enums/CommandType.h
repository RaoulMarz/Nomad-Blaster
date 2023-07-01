#ifndef CPPBOT_COMMANDTYPE_H
#define CPPBOT_COMMANDTYPE_H

enum class CommandType
{
    None = 0,
    Up = 1,
    Down = 2,
    Left = 3,
    Right = 4,
    Upleft = 5,
    Upright = 6,
    Downleft = 7,
    Downright = 8,
    DigDown = 9,
    DigLeft = 10,
    DigRight = 11,
    Steal = 12,
    Radar = 13
};

#endif //CPPBOT_COMMANDTYPE_H