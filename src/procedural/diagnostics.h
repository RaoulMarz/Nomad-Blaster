#ifndef DIAGNOSTICS_CLASS_H
#define DIAGNOSTICS_CLASS_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <string>
#include <vector>
#include <optional>
#include <iomanip>
#include <iostream>

class Diagnostics {
    public:

    static void printNullValueMessage(const void* object,std::string displayObject) {
        std::stringstream ssStore;
        if (object == nullptr)
            ssStore << displayObject << " == null" << std::endl;
        else {
            ssStore << displayObject << " == " << std::hex << object << std::endl;
        }
        godot::UtilityFunctions::print(godot::String(ssStore.str().c_str()));
    }
};

#endif