#ifndef PHYSICS_SETTINGS_CLASS_H
#define PHYSICS_SETTINGS_CLASS_H

#include "defaultmatrix.h"
#include <string>

enum enumPhysicsParameter {
	PHYSICS_PARAM_RMAX,
	PHYSICS_PARAM_VELOCITY_HL,
	PHYSICS_PARAM_FORCE,
	PHYSICS_PARAM_DT
};

enum enumConfigurationParameter {
	CONFIG_PARAM_NTYPES,
	CONFIG_PARAM_PARTICLE_COUNT
};

class PhysicsSettings {
private:
	static int matrixSize;
	bool debugFlag = true;
	/**
	 * Allows particles to move and interact across the world's borders (-1.0, +1.0).
	 */
	bool wrap = true;
	/**
	 * no interaction between particles that are further apart than rmax
	 */
	float rmax = 0.04;

	/**
	 * The time in seconds after which half the velocity of a particle
	 * should be lost due to friction.
	 * The actual friction factor <code>f</code> that the velocity is
	 * multiplied with in every time step is calculated on the basis of
	 * this value according to the following formula:
	 * <code>f = Math.pow(0.5, dt / frictionHalfLife)</code>
	 */
	float velocityHalfLife = 0.043;

	/**
	 * Scaled force by an arbitrary factor.
	 */
	float force = 1.0f;
	/**
	 * Time that is assumed to have passed between each simulation step, in seconds.
	 */
	float dt = 0.02f;
	int nTypes = 6;
	int particleCount = 10000;
public:
	DefaultMatrix physMatrix = DefaultMatrix(6);
	
	static int getMatrixSize();
	float getParameter(enumPhysicsParameter paramType);
	int getIntParameter(enumConfigurationParameter  paramType);
	void setParameter(enumPhysicsParameter paramType, float value);
	void setIntParameter(enumConfigurationParameter paramType, int value);
	bool isWrap();
	bool isDebugEnabled();
	void setDebugEnabled(bool debug);
	PhysicsSettings* deepCopy();
};

#endif