#ifndef EXTENDED_PARTICLE_PHYSICS_CLASS_H
#define EXTENDED_PARTICLE_PHYSICS_CLASS_H

#include "basestructures.h"
#include "particle.h"
#include "physicssettings.h"
#include "arrayutils.h"
#include "mathrange.h"
#include "defaultaccelerator.h"
#include "defaultmatrixgenerator.h"
#include "defaultpositionsetter.h"
#include "defaulttypesetter.h"
#include "particlephysics.h"
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

class ExtendedParticlePhysics : public ParticlePhysics {
private:
    void shuffleParticles();
    void swapIntVector(std::vector<int> &array, int i, int j);
public:
    ExtendedParticlePhysics();
    ExtendedParticlePhysics(DefaultAccelerator &accelerator, DefaultPositionSetter &positionSetter, DefaultMatrixGenerator &matrixGenerator, DefaultTypeSetter &typeSetter);

    std::vector<int> getTypeCount();
    void setTypeCountEqual();
    void setTypeCount(std::vector<int> &typeCount);
};

#endif