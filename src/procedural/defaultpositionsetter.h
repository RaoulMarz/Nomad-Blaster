#ifndef DEFAULT_POSITIONSETTER_CLASS_H
#define DEFAULT_POSITIONSETTER_CLASS_H

#include <string>
#include <map>
#include <chrono>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

enum MembraneEnum {
    MEMBRANE_NONE = 0,
    MEMBRANE_UNIFORM,
    MEMBRANE_UNICIRCLE,
    MEMBRANE_CENTERED,
    MEMBRANE_CENTEREDCIRCLE,
    MEMBRANE_RING,
    MEMBRANE_BATTLE,
    MEMBRANE_WHEEL,
    MEMBRANE_LINE,
    MEMBRANE_SPIRAL,
    MEMBRANE_RAINBOWSPIRAL
};

class DefaultPositionSetter {
    private:
        std::string membrane;
        godot::Vector3 defPosition = godot::Vector3(0, 0, 0); // godot::Vector3.Zero;
		int type = 0;
		int nTypes = 6;

        std::map<std::string, MembraneEnum> mapMembraneTypes;
        MembraneEnum getMembraneType(std::string positionMembrane);
        void initMembraneMap();
    public:
        DefaultPositionSetter();
        DefaultPositionSetter(std::string positionMembrane);
        void set(godot::Vector3 position, int type, int nTypes);
};

#endif