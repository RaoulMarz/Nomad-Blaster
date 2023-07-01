#include "GameState.h"

GameState::GameState() {

}

void GameState::generateRandomParagraph(std::ostream & outStream, int parWordCount, int minWordCharLen, int maxWordCharLen)
{
    for (int iwx = 0; iwx < parWordCount; iwx++)
    {
        std::string genWord = "";
        std::string seedString = "abcdefghijklmnopqrstuvwxyz";
        int wordCharCount = RandomUtility::getIntInRange(minWordCharLen, maxWordCharLen);
        int newLineMarker = RandomUtility::getIntInRange(0, 7);
        for (int ix = 0; ix < wordCharCount; ix++) {
            int randCPos = RandomUtility::getIntInRange(0, seedString.length() - 1);
            genWord += seedString.at(randCPos);
        }
        if (newLineMarker == 3)
            outStream << std::endl;
        outStream << genWord << " ";
    }
    outStream << std::endl;
    outStream << std::endl;
}

void GameState::generateRandomParagraphs(std::ostream & outStream, int minParagraphs, int maxParagraphs,
                                         int minParWords, int maxParWords, int minWordCharLen, int maxWordCharLen) {
    int paragraphCount = RandomUtility::getIntInRange(minParagraphs, maxParagraphs);
    std::vector<int> paragraphWordLengths = RandomUtility::getIntVector(paragraphCount, minParWords, maxParWords);
    for (int parWordCount : paragraphWordLengths)
    {
        generateRandomParagraph(outStream, parWordCount, minWordCharLen, maxWordCharLen);
    }
}

void GameState::writeJsonStateFile(std::string outJson, std::ostringstream &outStream) {
    std::ofstream jsonFile(outJson, std::ios::trunc | std::ios::out);
    jsonFile << outStream.str();
}

bool GameState::processJsonMap(std::map<std::string, signalr::value> gameStateMap, bool &forceJsonProcess,
                               std::string workingPath, std::string logSubpath)
{
    std::string exceptionMarker;
    try
    {
        int winX = 0;
        int winY = 0;
        bool printDebugInfo = false;
        bool produceTrackedGameState = true;
        jed_utils::datetime currentTime;
        std::ostringstream debugStream;
        debugStream.str("");
        debugStream << currentTime.to_string() << " starting ..." << std::endl;
        if (printDebugInfo)
            std::cout << currentTime.to_string() << " GameState::processJsonMap starting = " << debugStream.str();
        debugStream.str("");
        debugStream << "working path=" << workingPath << "\tlogSubpath=" << logSubpath;
        if (printDebugInfo)
            std::cout << debugStream.str() << std::endl;
        std::string strDbg1 = debugStream.str();
        debugStream.str("");
        
        //if (botLogger)
        //    botLogger->logInfo("GameState::processJsonMap", strDbg1);
        Json::Value jsonGameState = signalr::createJson(gameStateMap);
        Json::StreamWriterBuilder builder = signalr::getJsonWriter();
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        std::ostringstream os;
        writer->write(jsonGameState, &os);
        std::map<std::string, signalr::value> copyStateMap = gameStateMap;
        copyStateMap.erase("elapsedTime");
        Json::Value jsonCacheState = signalr::createJson(copyStateMap);
        std::ostringstream osCache;
        writer->write(jsonCacheState, &osCache);
        bool cacheContentMatches = false;
        //Remove "elapsedTime" from the json gamestate map to easy compare the content of 2 consecutive calls to this method
        std::string jsonCacheStorePath = ExtraHelper::combineFilePath(workingPath, "cache");
        if ( (jsonCacheStorePath.length() >= 1) && (!ExtraHelper::pathExists(jsonCacheStorePath) ) ) {
            ExtraHelper::createPath(jsonCacheStorePath);
        }
        std::string outJsonCacheFile = ExtraHelper::combineFilePath(jsonCacheStorePath, "gamestate-cache#.json");
        if (ExtraHelper::fileExists(outJsonCacheFile))
        {
            std::string cachedJsonContent = osCache.str();
            cachedJsonContent.erase(std::remove_if(cachedJsonContent.begin(), cachedJsonContent.end(), isJsonWhitespace), cachedJsonContent.end());
            std::string cachJStr = ExtraHelper::readFileAsString(outJsonCacheFile);
            cachJStr.erase(std::remove_if(cachJStr.begin(), cachJStr.end(), isJsonWhitespace), cachJStr.end());
            auto levenshteinDist = CollectionAlgoritms::levenshtein_distance(cachedJsonContent, cachJStr);
            if (printDebugInfo)
                std::cout << "levenshteinDist for cached Json = " << levenshteinDist << std::endl;
            cacheContentMatches = (cachJStr == cachedJsonContent) || (levenshteinDist <= 12);
            debugStream.str("");
            debugStream << "levenshteinDist for cached Json = " << levenshteinDist << " ; cache matches = " << cacheContentMatches << std::endl;
            debugStream.str("");
        }
        //jsonLastStore = std::make_optional<std::ostringstream>(os);

        if ( (!forceJsonProcess) && (cacheContentMatches) )
            return false;
        if (forceJsonProcess)
            forceJsonProcess = false;
        std::string stateFile = "gamestate_" + currentTime.to_string() + ".json";
        std::string jsonLogPath = ExtraHelper::combineFilePath(workingPath, logSubpath);
        std::string outJsonStateFile = ExtraHelper::combineFilePath(jsonLogPath, stateFile);
        if ( (jsonLogPath.length() >= 1) && (!ExtraHelper::pathExists(jsonLogPath) ) ) {
            ExtraHelper::createPath(jsonLogPath);
        }
        if (produceTrackedGameState) {
            std::string jsonStatePath = ExtraHelper::combineFilePath(workingPath, "gamestate");
            std::string trackJsonStateFile = ExtraHelper::combineFilePath(jsonStatePath, stateFile);
            if ( (jsonLogPath.length() >= 1) && (!ExtraHelper::pathExists(jsonStatePath) ) ) {
                ExtraHelper::createPath(jsonStatePath);
            }
            writeJsonStateFile(trackJsonStateFile, os);
        }
        ////////// DEBUG ///////////////////////
        std::cout << "outJsonCacheFile = " << outJsonCacheFile << std::endl;
        std::cout << "outJsonStateFile = " << outJsonStateFile << std::endl;
        ////////// DEBUG ///////////////////////
        writeJsonStateFile(outJsonStateFile, os);
        writeJsonStateFile(outJsonCacheFile, osCache);
        std::map <std::string, bool> sectionKeyMap;
        if (gameStateMap.size() >= 2)
        {
            std::stringstream ss;
            for (const auto &[key, value] : gameStateMap)
            {
                // if (value.is_string())
                //     ss << "[" << key << "]=" << value.as_string() << std::endl;
                ss << "[" << key << "]=";
                ss << SignalRHelper::signalr_value_tostring(value, true, true);

                if (key.compare("collected") == 0) {
                    sectionKeyMap.insert(std::make_pair("collected", true));
                }
                if (key.compare("connectionId") == 0) {
                    sectionKeyMap.insert(std::make_pair("connectionId", true));
                }
                if (key.compare("currentLevel") == 0) {
                    sectionKeyMap.insert(std::make_pair("currentLevel", true));
                }
                if (key.compare("elapsedTime") == 0) {
                    sectionKeyMap.insert(std::make_pair("elapsedTime", true));
                }
                if (key.compare("heroWindow") == 0) {
                    sectionKeyMap.insert(std::make_pair("heroWindow", true));
                }
                if (key.compare("x") == 0) {
                    //sectionKeyMap.insert(std::make_pair("x", true));
                    if (value.is_double()) {
                        winX = (int)(value.as_double());
                    }
                }
                if (key.compare("y") == 0) {
                    //sectionKeyMap.insert(std::make_pair("x", true));
                    if (value.is_double()) {
                        winY = (int)(value.as_double());
                    }
                }
            }
            /*
             *
             *//// arbitrary text to test the pipe output dead-live lock bug of livemethod=2
            debugStream.str("");
            /*
            generateRandomParagraphs(debugStream, 5, 40, 120, 200, 5, 22);
            std::cout << debugStream.str();
            if (botLogger)
                botLogger->logInfo("GameState::processJsonMap", "[Generate random text tester] = " + debugStream.str());
            debugStream.str("");
            */
            // arbitrary text to test the pipe output dead-live lock bug of livemethod=2

            exceptionMarker = "iterate map values";
            debugStream << "GameState::processJsonMap = " << std::endl
                      << ss.str();
            //std::cout << debugStream.str(); // this is the original point which "triggers" (make visible) the deadlock bug
            debugStream.str("");

            //std::map<std::string, signalr::value> heroWindowMap;
            //if (gameStateMap.find("heroWindow")->second.is_map())
            //    heroWindowMap = gameStateMap.find("heroWindow")->second.as_map();
            std::vector<signalr::value> heroWindowData;
            if (gameStateMap.find("heroWindow")->second.is_array()) {
                heroWindowData = gameStateMap.find("heroWindow")->second.as_array();
                debugStream << "processJsonMap(), heroWindow extraction , size = " << heroWindowData.size() << std::endl;
                std::cout << debugStream.str();
                
                debugStream.str("");
            }
            exceptionMarker = "heroWindow extraction";
            MVector2d windowOffset = MVector2d{winX, winY};
            world.processJsonWindow(heroWindowData, windowOffset);
            std::cout << "GameState::processJsonMap [z] = Finished world.processJsonWindow()" << std::endl;
            exceptionMarker = "world processJsonWindow";
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "GameState::processJsonMap :: exception: " << e.what() << " :: marker = " << exceptionMarker << std::endl;
        //if (botLogger)
        //    botLogger->logInfo("GameState::processJsonMap", "exception = " + std::string(e.what()));
        return false;
    }
    return true;
}

bool GameState::isSpecialWhitespace(unsigned char c, bool matchSpace) {
    if (c == '\t' || c == '\n' ||
        c == '\r') {
        return true;
    } else {
        return false;
    }
}

bool GameState::isJsonWhitespace(unsigned char c) {
    return isSpecialWhitespace(c, false);
}
