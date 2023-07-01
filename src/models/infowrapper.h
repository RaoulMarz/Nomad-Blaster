#ifndef INFOWRAPPER_CLASS_H
#define INFOWRAPPER_CLASS_H

#include <string>
#include <vector>
#include <memory>
#include <map>

template <typename T> class InfoWrapper {
    public:
        std::string name;
        std::string description;
        T objectWrap;

        InfoWrapper(std::string name, std::string description, T objectP)
        {
            name = name;
            description = description;
            objectWrap = objectP;
        }

        InfoWrapper(std::string name, T objectP)
        {
            //this(name, "", objectP);
            name = name;
            description = "";
            objectWrap = objectP;
        }
};

#endif