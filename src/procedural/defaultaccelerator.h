#ifndef DEFAULTACC_CLASS_H
#define DEFAULTACC_CLASS_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/core/math.hpp>
#include <string>
#include <map>

enum AcceleratorCatEnum {
    ACCELERATOR_CAT_NONE,
    ACCELERATOR_CAT_PARTICLE_LIFE,
    ACCELERATOR_CAT_PARTICLE_LIFE_R,
    ACCELERATOR_CAT_PARTICLE_LIFE_R2,
    ACCELERATOR_CAT_ROTATOR90,
    ACCELERATOR_CAT_ROTATOR_ATTR,
    ACCELERATOR_CAT_PLANETS
};

class DefaultAccelerator {
    private:
        std::map<std::string, AcceleratorCatEnum> mapAcceleratorTypes;
        AcceleratorCatEnum getAcceleratorType(std::string acceleratorCategory);
        void initAcceleratorMap();
    public:
        float accelerateScalar = 0.0f;
        godot::Vector3 position = godot::Vector3(0, 0, 0); // = Vector3.Zero;

        DefaultAccelerator();
        DefaultAccelerator(std::string acceleratorCategory);
        godot::Vector3 accelerate(float a, godot::Vector3 pos);
};

#endif