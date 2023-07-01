#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H

#include <string>
#include <sstream>
#include "CommandType.h"

class PlayerAction
{
    public:
    CommandType type;
    //int units;
    //std::string id;
    PlayerAction() {
        type = CommandType::None;
    }

    PlayerAction(std::string command) {
        int cmdIndex = std::stoi(command);
        type = static_cast<CommandType>(cmdIndex);
    }

    //Up = 1, Down = 2, Left = 3, Right = 4, Upleft = 5, Upright = 6,
    //Downleft = 7, Downright = 8, DigDown = 9, DigLeft = 10, DigRight = 11, Steal = 12, Radar = 13
    static std::string printEnumType(CommandType type) {
        std::string res = "";
        switch (type)
        {
        case CommandType::None :
            res = "0";
            break;
        case CommandType::Up :
            res = "1";
            break;
        case CommandType::Down :
            res = "2";
            break;
        case CommandType::Left :
            res = "3";
            break;
        case CommandType::Right :
            res = "4";
            break;
        case CommandType::Upleft :
            res = "5";
            break;
        case CommandType::Upright :
            res = "6";
            break;
        case CommandType::Downleft :
            res = "7";
            break;
        case CommandType::Downright :
            res = "8";
            break;
        case CommandType::DigDown :
            res = "9";
            break;
        case CommandType::DigLeft :
            res = "10";
            break;
        case CommandType::DigRight :
            res = "11";
            break;
        case CommandType::Steal :
            res = "12";
            break;
        case CommandType::Radar :
            res = "13";
            break;
        default:
            break;
        }
        return res;
    }

    std::string toString() {
        std::stringstream ss;
        ss << printEnumType(type);// << std::endl;
        return ss.str();
    }

    int toInteger() {
        std::string strVal = printEnumType(type);
        if (strVal.length() <= 0)
            strVal = "0";
        return std::stoi(strVal);
    }
};

#endif //PLAYER_ACTION_H
