#include "physicssettings.h"

int PhysicsSettings::matrixSize = 6;

int PhysicsSettings::getMatrixSize() {
	return matrixSize;
}

PhysicsSettings *PhysicsSettings::deepCopy() {
	PhysicsSettings *p = new PhysicsSettings();

	p->wrap = wrap;
	p->rmax = rmax;
	p->velocityHalfLife = velocityHalfLife;
	p->force = force;
	p->dt = dt;
	p->physMatrix = *(physMatrix.deepCopy());

	return p;
}

bool PhysicsSettings::isWrap() {
	return wrap;
}

bool PhysicsSettings::isDebugEnabled() {
	return debugFlag;
}

void PhysicsSettings::setDebugEnabled(bool debug) {
	debugFlag = debug;
}

float PhysicsSettings::getParameter(enumPhysicsParameter paramType) {
	float res = 0.0f;
	switch (paramType) {
		case enumPhysicsParameter::PHYSICS_PARAM_DT:
			res = dt;
			break;
		case enumPhysicsParameter::PHYSICS_PARAM_RMAX:
			res = rmax;
			break;
		case enumPhysicsParameter::PHYSICS_PARAM_FORCE:
			res = force;
			break;
		case enumPhysicsParameter::PHYSICS_PARAM_VELOCITY_HL:
			res = velocityHalfLife;
			break;
		default:
			break;
	}
	return res;
}

int PhysicsSettings::getIntParameter(enumConfigurationParameter paramType) {
	int res = 0;
	switch (paramType) {
		case enumConfigurationParameter::CONFIG_PARAM_NTYPES:
			res = nTypes;
			break;
		case enumConfigurationParameter::CONFIG_PARAM_PARTICLE_COUNT:
			res = particleCount;
			break;
		default:
			break;
	}
	return res;
}

void PhysicsSettings::setParameter(enumPhysicsParameter paramType, float value) {
	switch (paramType) {
		case enumPhysicsParameter::PHYSICS_PARAM_DT:
			dt = value;
			break;
		case enumPhysicsParameter::PHYSICS_PARAM_RMAX:
			rmax = value;
			break;
		case enumPhysicsParameter::PHYSICS_PARAM_FORCE:
			force = value;
			break;
		case enumPhysicsParameter::PHYSICS_PARAM_VELOCITY_HL:
			velocityHalfLife = value;
			break;
		default:
			break;
	}
}

void PhysicsSettings::setIntParameter(enumConfigurationParameter paramType, int value) {
	switch (paramType) {
		case enumConfigurationParameter::CONFIG_PARAM_NTYPES:
			nTypes = value;
			break;
		case enumConfigurationParameter::CONFIG_PARAM_PARTICLE_COUNT:
			particleCount = value;
			break;
		default:
			break;
	}
}
