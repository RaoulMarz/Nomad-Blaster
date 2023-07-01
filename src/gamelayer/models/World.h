#ifndef CPPBOT_WORLD_WORLDGAMEOBJECT_H
#define CPPBOT_WORLD_WORLDGAMEOBJECT_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <optional>
#include <algorithm>
#include "SignalRHelper.h"
#include "signalrclient/signalr_value.h"
#include "MVector2d.h"
#include "GridCoordinateStore.h"
#include "ObjectType.h"
#include "SolidStructure.h"

class World
{
public:
    int size;
    int currentTick;
    MVector2d playerCoordinate;
    MVector2d gameWindowOffset;

    void processJsonWindow(std::vector<signalr::value> windowData, MVector2d windowOffset);
    std::optional<std::vector<GridCoordinateStore<int>>> getImmediateWindowAt(MVector2d& position, int blockSpan = 1);
    std::optional<std::vector<GridCoordinateStore<int>>> getPlayerImmediateWindow(int blockSpan = 1);
    std::optional<std::map<int, std::vector<GridCoordinateStore<int>>>> getPlayerWindow();
    std::optional<std::vector<SolidStructure>> getLadderStructures();
    std::optional<std::vector<SolidStructure>> getPlatformStructures();
    // void processJsonMap(std::map<std::string, signalr::value> worldMap);
    std::pair<ObjectType, ObjectType> getBlocksBelowPlayer();
    MVector2d getPlayerCoordinate()
    {
        return playerCoordinate;
    }

    /*
    Air = 0,
    Solid = 1,
    Collectible = 2,
    Hazard = 3,
    Platform = 4,
    Ladder = 5,
    Opponent = 6
    */

    static ObjectType getObjectTypeFrom(int value) {
        return static_cast<ObjectType>(value);
    }

    static int IntFromObjectType(ObjectType objType) {
        int res = -1;
        switch (objType) {
            case ObjectType::Air :
                res = 0;
            case ObjectType::Solid :
                res = 1;
            case ObjectType::Collectible :
                res = 2;
            case ObjectType::Hazard :
                res = 3;
            case ObjectType::Platform :
                res = 4;
            case ObjectType::Ladder :
                res = 5;
            case ObjectType::Opponent :
                res = 6;
        }
        return res;
    }

    static bool ObjectTypeInGroup(ObjectType objType, std::vector<ObjectType> &typeGroup);
private:
    std::map<int, std::vector<GridCoordinateStore<int>>> mapPlayerWindow;
    bool debugInfo = true;
    bool invertHorizontal = true;

    std::map<int, std::vector<GridCoordinateStore<int>>> convertColumnarMap(std::vector<std::vector<GridCoordinateStore<int>>> columnarVectorMapData);
    bool coordinateArrayContains(std::vector<MVector2d> &coordinateArray, int direction, int coordComponent);
};

#endif // CPPBOT_WORLD_WORLDGAMEOBJECT_H
