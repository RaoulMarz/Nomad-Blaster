#ifndef CPP_ALIVECONNECT_STRUCT_H
#define CPP_ALIVECONNECT_STRUCT_H

#include <string>
#include <iostream>
#include <sstream>

struct AliveConnectStruct
{
bool server;
bool broker;
std::string clientRunToken;
std::string exitToken;
int portNumber;

std::string to_string() const
{
    std::stringstream ssOut;
    ssOut << "<AliveConnectStruct>;server=" << server << ";broker=" << broker << ";clientRunToken=" << clientRunToken
    << ";exitToken=" << exitToken << ";port=" << portNumber << std::endl;
    return ssOut.str();
}

};

#endif //CPP_ALIVECONNECT_STRUCT_H
