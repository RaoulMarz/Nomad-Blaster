#include "World.h"

std::map<int, std::vector<GridCoordinateStore<int>>> World::convertColumnarMap(std::vector<std::vector<GridCoordinateStore<int>>> columnarVectorMapData)
{
    int numColumns = columnarVectorMapData.size();
    std::map<int, std::vector<GridCoordinateStore<int>>> res;
    if (numColumns < 20)
        return res;
    int numRows = columnarVectorMapData[0].size();
    for (int irx = 0; irx < numRows; irx++)
        res[irx] = std::vector<GridCoordinateStore<int>>();
    int icolumn = 0;
    for (std::vector<GridCoordinateStore<int>> columnData : columnarVectorMapData)
    {
        int irow = 0;
        if (invertHorizontal)
            reverse(columnData.begin(), columnData.end());
        for (GridCoordinateStore<int> columnBlock : columnData)
        {
            res[irow].push_back(columnBlock);
            irow += 1;
        }
        icolumn += 1;
    }
    return res;
}

void World::processJsonWindow(std::vector<signalr::value> windowData, MVector2d windowOffset)
{
    gameWindowOffset = windowOffset;
    std::ostringstream debugStream;
    debugStream << "World::processJsonWindow -- start , windowOffset= " << windowOffset.toString() << std::endl;
    std::cout << debugStream.str();
    //if (botLogger)
    //    botLogger->logInfo("World::processJsonWindow", debugStream.str());
    debugStream.str("");
    if (windowData.size() > 0)
    {
        if (debugInfo)
        {
            if (windowData[0].is_array())
            {
                std::cout << "Cols = " << windowData.size() << "\tRows = " << windowData[0].as_array().size() << std::endl;
            }
        }
        std::vector<std::vector<GridCoordinateStore<int>>> columnarVectorMapData;
        int colIndex = 0;
        std::stringstream ss;
        for (signalr::value windowValue : windowData)
        {
            if (windowValue.is_string())
                ss << "value = " << windowValue.as_string() << std::endl;
            if (windowValue.is_array())
            {
                std::vector<signalr::value> dataColumn = windowValue.as_array();
                ss << "Column [" << colIndex << "] = " << std::endl;
                int rowIndex = 0;
                std::vector<GridCoordinateStore<int>> currentColumnVectorData;
                if (dataColumn.size() > 0)
                {
                    for (signalr::value columnValue : dataColumn)
                    {
                        ss << "[row=" << rowIndex << "]=" << columnValue.as_double() << std::endl;
                        currentColumnVectorData.push_back(GridCoordinateStore<int>(MVector2d{colIndex, rowIndex}, (int)columnValue.as_double()));
                        rowIndex += 1;
                    }
                }
                columnarVectorMapData.push_back(currentColumnVectorData);
                colIndex += 1;
            }
            std::cout << ss.str();
            debugStream << ss.str() << std::endl;
            
            debugStream.str("");
            ss.str("");//clear();
        }
        if (columnarVectorMapData.size() >= 20) //size() should be 34 as this is the window width representing the column "stack"
        {
            mapPlayerWindow = convertColumnarMap(columnarVectorMapData);
            debugStream << "convertColumnarMap(), size = " << columnarVectorMapData.size() << std::endl;
            std::cout << debugStream.str();
            //if (botLogger)
            //    botLogger->logInfo("World::processJsonWindow -- [zzz]", debugStream.str());
            debugStream.str("");
        }
    }
    if (mapPlayerWindow.size() > 0)
    {
        int mapY = mapPlayerWindow.size();
        int mapX = mapPlayerWindow[0].size();
        playerCoordinate = MVector2d{(mapX / 2) - 1, (mapY / 2) - 1};
    }
}

bool World::ObjectTypeInGroup(ObjectType objType, std::vector<ObjectType> &typeGroup)
{
    bool res = false;
    if (typeGroup.size() > 0)
    {
        std::vector<ObjectType>::iterator it = std::find(typeGroup.begin(), typeGroup.end(), objType);
        if (it != typeGroup.end())
            res = true;
    }
    return res;
}

bool World::coordinateArrayContains(std::vector<MVector2d> &coordinateArray, int direction, int coordComponent) {
    bool res = false;
    if (coordinateArray.size() > 0)
    {
        for (MVector2d coord : coordinateArray)
        {
            if (direction == 1)
            {
                if (coordComponent == coord.x)
                {
                    res = true;
                    break;
                }
            }
            if (direction == 2)
            {
                if (coordComponent == coord.y)
                {
                    res = true;
                    break;
                }
            }
        }
    }
    return res;
}

std::pair<ObjectType, ObjectType> World::getBlocksBelowPlayer()
{
    std::pair<ObjectType, ObjectType> result = std::make_pair(ObjectType::Air, ObjectType::Air);
    MVector2d playerPosition = getPlayerCoordinate();
    if (playerPosition.x > 0)
    {
        int levelStandingRow = playerPosition.y + 1;
        if (levelStandingRow <= 22)
        {
            std::vector<GridCoordinateStore<int>> rowBlock = mapPlayerWindow[levelStandingRow];
            if (rowBlock.size() >= (playerPosition.x + 1)) {
                GridCoordinateStore<int> block1 = rowBlock[playerPosition.x];
                GridCoordinateStore<int> block2 = rowBlock[playerPosition.x + 1];
                ObjectType objtype1 = static_cast<ObjectType>(block1.getStoreValue());
                ObjectType objtype2 = static_cast<ObjectType>(block2.getStoreValue());
                result = std::make_pair(objtype1, objtype2);
            }
        }
    }
    return result;
}

std::optional<std::vector<GridCoordinateStore<int>>> World::getImmediateWindowAt(MVector2d &position, int blockSpan)
{
    std::optional<std::vector<GridCoordinateStore<int>>> result = std::nullopt;
    if (blockSpan >= 0 && blockSpan <= 4 && (mapPlayerWindow.size() > 1))
    {
        std::vector<GridCoordinateStore<int>> surroundingBlocks;
        int startRow = std::max(0, position.getY() - blockSpan);
        int endRow = startRow + (blockSpan * 2);
        for (int ir = startRow; ir <= endRow; ir++)
        {
            std::vector<GridCoordinateStore<int>> rowBlock = mapPlayerWindow[ir];
            if (rowBlock.size() >= 2) {
                int ic = 0;
                int startCol = std::max(0, position.getX() - blockSpan);
                int endCol = startCol + (blockSpan * 2);
                for (GridCoordinateStore<int> gridCell : rowBlock) {
                    if (ic >= startCol && ic <= endCol)
                        surroundingBlocks.push_back(gridCell);
                    ic += 1;
                }
            }
        }
        result = std::make_optional<std::vector<GridCoordinateStore<int>>>(surroundingBlocks);
    }
    return result;
}

std::optional<std::vector<SolidStructure>> World::getLadderStructures()
{
    std::optional<std::vector<SolidStructure>> res = std::nullopt;
    if (mapPlayerWindow.size() > 0)
    {
        std::vector<MVector2d> coordinateEndPoints;
        for (int ir = 0; ir <= mapPlayerWindow.size(); ir++)
        {
            std::vector<GridCoordinateStore<int>> rowBlock = mapPlayerWindow[ir];
            if (rowBlock.size() >= 20) {
                int ic = 0;
                for (GridCoordinateStore<int> gridCell : rowBlock) {
                    if (gridCell.storedMatches(IntFromObjectType(ObjectType::Ladder)) && 
                    !coordinateArrayContains(coordinateEndPoints, 1, gridCell.getCoordinate().x)) {
                        coordinateEndPoints.push_back(gridCell.getCoordinate());
                    }
                    ic += 1;
                }
            }
        }
    }
    return res;
}

std::optional<std::vector<SolidStructure>> World::getPlatformStructures()
{
    std::optional<std::vector<SolidStructure>> res = std::nullopt;
    if (mapPlayerWindow.size() > 0)
    {
        std::vector<MVector2d> coordinateEndPoints;
        for (int ir = 0; ir <= mapPlayerWindow.size(); ir++)
        {
            int lastY = 0;
            std::vector<GridCoordinateStore<int>> rowBlock = mapPlayerWindow[ir];
            if (rowBlock.size() >= 20) {
                int ic = 0;
                for (GridCoordinateStore<int> gridCell : rowBlock) {
                    if (gridCell.storedMatches(IntFromObjectType(ObjectType::Platform)) && 
                    !coordinateArrayContains(coordinateEndPoints, 2, gridCell.getCoordinate().y)) {
                        coordinateEndPoints.push_back(gridCell.getCoordinate());
                        lastY = ic;
                    } else
                    if (gridCell.storedMatches(IntFromObjectType(ObjectType::Platform)) &&
                    coordinateArrayContains(coordinateEndPoints, 2, gridCell.getCoordinate().y))
                    {
                        lastY = ic;
                    }
                    ic += 1;
                }
            }
        }
    }
    return res;
}

std::optional<std::vector<GridCoordinateStore<int>>> World::getPlayerImmediateWindow(int blockSpan)
{
    return getImmediateWindowAt(playerCoordinate, blockSpan);
}

std::optional<std::map<int, std::vector<GridCoordinateStore<int>>>> World::getPlayerWindow()
{
    std::optional<std::map<int, std::vector<GridCoordinateStore<int>>>> res = std::nullopt;
    if (mapPlayerWindow.size() >= 8)
        res = std::make_optional<std::map<int, std::vector<GridCoordinateStore<int>>>>(mapPlayerWindow);
    return res;
}

/*
void World::processJsonMap(std::map<std::string, signalr::value> worldMap) {
    if (worldMap.size() >= 2) {
        std::map <std::string, bool> sectionKeyMap;
        std::stringstream ss;
        for (const auto& [key, value] : worldMap) {
            if (value.is_string())
                ss << "[" << key << "]=" << value.as_string() << std::endl;
            if (key.compare("size") == 0) {
                sectionKeyMap.insert(std::make_pair("size", true));
            }
            if (key.compare("currentTick") == 0) {
                sectionKeyMap.insert(std::make_pair("currentTick", true));
            }
            //if (key.compare("populationTiers") == 0) {
            //    sectionKeyMap.insert(std::make_pair("populationTiers", true));
            //}
        }
        std::map<std::string, signalr::value> gameMap;
        // = worldMap.find("map")->second.as_map();
        if (worldMap.find("map")->second.is_map())
            gameMap = worldMap.find("map")->second.as_map();
        if (worldMap.find("map")->second.is_array())
            gameMap = worldMap.find("map")->second.as_array()[0].as_map();
        std::cout << "World::processJsonMap = " << std::endl
                  << ss.str() << std::endl;
        map.processJsonMap(gameMap);
    }
}
*/
