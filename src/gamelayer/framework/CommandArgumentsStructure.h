#ifndef COMMAND_ARGUMENTS_STRUCT_H
#define COMMAND_ARGUMENTS_STRUCT_H

#include <vector>
#include <map>

class CommandArgumentsStructure
{
public:
    int argc;
    char **argv;

    CommandArgumentsStructure() {

    }

    CommandArgumentsStructure(std::vector<std::string> vectorArguments) {
        if (vectorArguments.size() > 0)
        {

        }
    }

    void addArgument(std::string argValue)
    {
        argumentValues.push_back(argValue);
    }
private:
    std::vector<std::string> argumentValues;
};

#endif
