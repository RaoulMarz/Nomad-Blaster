#include "SignalRHelper.h"

void SignalRHelper::send_register(signalr::hub_connection &connection, std::string &token, std::string &nickname)
{
    std::vector<signalr::value> arr{token, nickname};
    std::vector<signalr::value> args(arr);
    //std::vector<signalr::value> args{nickname};

    if (connection.get_connection_state() == signalr::connection_state::connected)
    {
        connection.invoke("Register", args, [](const signalr::value &value, const std::exception_ptr &exception)
                          {
            try {
                if (exception) {
                    std::rethrow_exception(exception);
                }
                if (value.is_string()) {
                    std::cout << "Received: " << value.as_string() << std::endl;
                } else {
                    std::cout << "Hub method invocation has completed" << std::endl;
                }
            }
            catch (const std::exception &e) {
                std::cout << "Error while sending data: " << e.what() << std::endl;
            } });
    }
}

void SignalRHelper::send_player_command(signalr::hub_connection &connection, PlayerCommand &playerCmd)
{
    std::map<std::string, signalr::value> mapPlayerCmd;
    mapPlayerCmd.insert(std::make_pair("BotId", playerCmd.getPlayerID()));
    int cmdNum = playerCmd.getAction().toInteger();
    mapPlayerCmd.insert(std::make_pair("Action", static_cast<double>(cmdNum)));

    // signalr::value args(arr);
    std::vector<signalr::value> args{mapPlayerCmd};
    if (connection.get_connection_state() == signalr::connection_state::connected)
    {
        connection.invoke("SendPlayerCommand", args,
                          [](const signalr::value &value, const std::exception_ptr &exception)
                          {
                              try
                              {
                                  if (exception)
                                  {
                                      std::rethrow_exception(exception);
                                  }
                                  if (value.is_string())
                                  {
                                      // std::cout << "Received: " << value.as_string() << std::endl;
                                  }
                                  else
                                  {
                                      // std::cout << "Hub method invocation has completed" << std::endl;
                                  }
                              }
                              catch (const std::exception &e)
                              {
                                  std::cout << "Error while sending data: " << e.what() << std::endl;
                              }
                          });
    }
}

signalr::hub_connection SignalRHelper::initializeHubConnect()
{
    std::string endpoint = SignalRHelper::getRunnerEndpoint();
    signalr::hub_connection connection = signalr::hub_connection_builder::create(endpoint)
                                             .with_logging(std::make_shared<Logger>(), signalr::trace_level::none)
                                             .build();
    return connection;
}

std::string SignalRHelper::getRunnerEndpoint()
{
    const char *ipAddr = std::getenv("RUNNER_IPV4");
    if (ipAddr == nullptr)
    { // invalid to assign nullptr to std::string
        return "http://127.0.0.1:5000/runnerhub";
    }
    else
    {
        std::string endpoint;

        if (std::string(ipAddr).rfind("http://", 0) != 0)
        {
            endpoint.append("http://");
        }

        endpoint.append(ipAddr);
        endpoint.append(":5000/runnerhub");
        return endpoint;
    }
}

std::string SignalRHelper::signalr_value_tostring(signalr::value sigvalue, bool iterateMap, bool iterateArray)
{
    std::string res = "";
    std::stringstream ss;
    if (sigvalue.is_string())
        ss << sigvalue.as_string() << "\t";
    if (sigvalue.is_double())
        ss << sigvalue.as_double() << "\t";
    if (sigvalue.is_bool())
        ss << sigvalue.as_bool() << "\t";
    if ((iterateMap) && (sigvalue.is_map()))
    {
        for (const auto &[key, value] : sigvalue.as_map())
        {
            ss << "[" << key << "]=" << signalr_value_tostring(value, iterateMap, iterateArray) << std::endl;
        }
    }
    if ((iterateArray) && (sigvalue.is_array()))
    {
        for (const auto &value : sigvalue.as_array())
        {
            ss << signalr_value_tostring(value, iterateMap, iterateArray) << std::endl;
        }
    }
    res = ss.str();
    return res;
}
