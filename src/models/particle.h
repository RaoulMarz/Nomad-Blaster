#ifndef PARTICLE_CLASS_H
#define PARTICLE_CLASS_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>

class Particle {
    public:
        godot::Vector3 position = godot::Vector3(0, 0, 0);
        godot::Vector3 velocity = godot::Vector3(0, 0, 0);
        int type = 0;
};

#endif