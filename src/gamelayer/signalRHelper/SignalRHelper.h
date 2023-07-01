#ifndef CPPBOT_SIGNALRHELPER_H
#define CPPBOT_SIGNALRHELPER_H

#include <iostream>
#include <future>
#include <map>
#include <string>
#include <sstream>
#include "signalrclient/hub_connection.h"
#include "signalrclient/hub_connection_builder.h"
#include "signalrclient/signalr_value.h"
#include "Logger.hpp"
#include "PlayerAction.h"
#include "PlayerCommand.h"

class SignalRHelper {
private:
    static std::string getRunnerEndpoint();
public:
    static signalr::hub_connection initializeHubConnect();
    //static void send_register(signalr::hub_connection &connection, std::string &token, std::string &nickname);
	static void send_register(signalr::hub_connection &connection, std::string &token, std::string &nickname);
    static void send_player_command(signalr::hub_connection &connection, PlayerCommand &playerCmd);
    static std::string signalr_value_tostring(signalr::value sigvalue, bool iterateMap = false, bool iterateArray = false);
};


#endif //CPPBOT_SIGNALRHELPER_H
