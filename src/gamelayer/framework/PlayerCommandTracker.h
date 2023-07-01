#ifndef CPPBOT_PLAYERCOMMANDTRACKER_H
#define CPPBOT_PLAYERCOMMANDTRACKER_H

#include <vector>
#include <string>
#include "CommandType.h"
#include "PlayerCommand.h"
#include "datetime.h"

struct CommandStatsStruct {
    int index;
    std::string botId;
    jed_utils::datetime timestamp;
    CommandType command;
};

class PlayerCommandTracker {
private:
    std::vector<CommandStatsStruct> vectorMovementsHistory;
public:
    void addMovementCommand(int cmdIndex, PlayerCommand playerCmd, jed_utils::datetime cmdTimestamp = jed_utils::datetime())
    {
        vectorMovementsHistory.push_back(CommandStatsStruct{cmdIndex, playerCmd.getPlayerID(), cmdTimestamp, playerCmd.getAction().type});
    }
};

#endif
