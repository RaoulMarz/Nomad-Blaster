#ifndef CPPBOT_GAMESTATE_H
#define CPPBOT_GAMESTATE_H

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <optional>
#include <algorithm>
#include "datetime.h"
#include "signalrclient/signalr_value.h"
#include "SignalRHelper.h"
#include "json_helpers.h"
#include "extrahelper.h"
#include "RandomUtility.h"
#include "World.h"
#include "Bot.h"
#include "MVector2d.h"
#include "CollectionAlgorithms.h"

class GameState
{
private:
    void writeJsonStateFile(std::string outJson, std::ostringstream &outStream);
    static bool isSpecialWhitespace(unsigned char c, bool matchSpace = false);
    static bool isJsonWhitespace(unsigned char c);
    void generateRandomParagraph(std::ostream & outStream, int parWordCount, int minWordCharLen, int maxWordCharLen);
    void generateRandomParagraphs(std::ostream & outStream, int minParagraphs, int maxParagraphs,
                                         int minParWords, int maxParWords, int minWordCharLen, int maxWordCharLen);

    //std::optional<std::ostringstream> jsonLastStore = std::nullopt;
public:
    World world;
    std::vector<Bot> bots;

    GameState();
    bool processJsonMap(std::map<std::string, signalr::value> gameStateMap, bool &forceJsonProcess,
                        std::string workingPath = "", std::string logSubpath = "");

    World getWorld() const
    {
        return world;
    }
};

#endif // CPPBOT_GAMESTATE_H
