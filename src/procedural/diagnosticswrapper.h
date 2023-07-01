#ifndef DIAGNOSTICS_WRAPPER_CLASS_H
#define DIAGNOSTICS_WRAPPER_CLASS_H

#include <vector>
#include <string>
#include <godot_cpp/variant/utility_functions.hpp>

static bool isDebug = false;

class DiagnosticsWrapper {
public:
    static void setDebugEnabled(bool debug) {
        isDebug = debug;
    }

    static void InfoPrint(std::string format, std::string parameterStr) {
        UtilityFunctions::print(format, parameterStr);
    }
};

#endif