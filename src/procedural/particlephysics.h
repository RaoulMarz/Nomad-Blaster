#ifndef PARTICLE_PHYSICS_CLASS_H
#define PARTICLE_PHYSICS_CLASS_H

#include "basestructures.h"
#include "defaultaccelerator.h"
#include "defaultmatrixgenerator.h"
#include "defaultpositionsetter.h"
#include "defaulttypesetter.h"
#include "particle.h"
#include "physicssettings.h"
#include "mathrange.h"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <chrono>
#include <limits>
#include <algorithm>
#include <random>

static int DEFAULT_MATRIX_SIZE = 7;

class ParticlePhysics {
private:
	PhysicsSettings *settings = new PhysicsSettings();

	// buffers for sorting by containers:
	std::vector<int> containers; //int[]
	std::vector<std::pair<std::pair<int, int>, int>> containerNeighborhood; //int[][]

	// container layout:
	int nx;
	int ny;
	float containerSize = 0.13;

	DefaultAccelerator accelerator;
	DefaultMatrixGenerator matrixGenerator;
	DefaultPositionSetter positionSetter;
	DefaultTypeSetter typeSetter;

	void calcNxNy();
	void makeContainerNeighborhood();
	float computeFrictionFactor(float halfLife, float dt);
	void updateParticles();
	void setMatrixSize(int newSize);
	void shuffleParticles();
	void updateVelocity(int i);
	void updatePosition(int i);
	int getContainerIndex(godot::Vector3 position);
	int wrapContainerAxis(enumCoordComponent compAxis, int cValue);
	int determineContainerValue(std::pair<std::pair<int, int>, int> value, int index = 0);
	Particle generateParticle();

protected:
	std::vector<Particle> particles;
	std::vector<Particle> particlesBuffer;

public:
	ParticlePhysics();
	ParticlePhysics(DefaultAccelerator paramAccelerator,
			DefaultPositionSetter paramPositionSetter,
			DefaultMatrixGenerator paramMatrixGenerator,
			DefaultTypeSetter paramTypeSetter);

	PhysicsSettings* getPhysicsSettings();
	void setPositions();
	void generateMatrix();
    void setParticleCount(int n);
	void setPosition(Particle p);
	void setType(Particle p);
	void makeContainers();
	void ensurePosition(godot::Vector3 position);
	godot::Vector3 doConnection(godot::Vector3 pos1, godot::Vector3 pos2);
	void update();
};

#endif