#ifndef CPPBOT_BOT_H
#define CPPBOT_BOT_H

#include <string>
#include <vector>
#include <iostream>
#include "MVector2d.h"

struct Bot
{
    std::string id;
    int currentTierLevel;
    int tick;
    //BotMap map;
    
    MVector2d baseLocation;
};

#endif //CPPBOT_MAP_H
