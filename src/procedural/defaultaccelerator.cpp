#include "defaultaccelerator.h"

void DefaultAccelerator::initAcceleratorMap() {
	mapAcceleratorTypes["none"] = AcceleratorCatEnum::ACCELERATOR_CAT_NONE;
    mapAcceleratorTypes["particle-life"] = AcceleratorCatEnum::ACCELERATOR_CAT_PARTICLE_LIFE;
    mapAcceleratorTypes["particle-life-r"] = AcceleratorCatEnum::ACCELERATOR_CAT_PARTICLE_LIFE_R;
	mapAcceleratorTypes["particle-life-r2"] = AcceleratorCatEnum::ACCELERATOR_CAT_PARTICLE_LIFE_R2;
	mapAcceleratorTypes["rotator-90"] = AcceleratorCatEnum::ACCELERATOR_CAT_ROTATOR90;
	mapAcceleratorTypes["rotator-attr"] = AcceleratorCatEnum::ACCELERATOR_CAT_ROTATOR_ATTR;
}

AcceleratorCatEnum DefaultAccelerator::getAcceleratorType(std::string acceleratorCategory) {
	AcceleratorCatEnum result = AcceleratorCatEnum::ACCELERATOR_CAT_NONE;
	if ((mapAcceleratorTypes.size() > 0) && (acceleratorCategory.length() > 0)) {
		if (mapAcceleratorTypes.find(acceleratorCategory) != mapAcceleratorTypes.end())
			result = mapAcceleratorTypes[acceleratorCategory];
	}
	return result;
}

DefaultAccelerator::DefaultAccelerator() {
	initAcceleratorMap();
}

DefaultAccelerator::DefaultAccelerator(std::string acceleratorCategory) {
	initAcceleratorMap();
	if (mapAcceleratorTypes.size() > 0) {
		float rmin = 0.3;
        float dist = position.length();
        float force =  0.01f;
		AcceleratorCatEnum accelTypeCat = getAcceleratorType(acceleratorCategory);
		switch (accelTypeCat) {
			case AcceleratorCatEnum::ACCELERATOR_CAT_PARTICLE_LIFE: {
				force = dist < rmin ? (dist / rmin - 1) : accelerateScalar * (1 - godot::Math::abs(1 + rmin - 2 * dist) / (1 - rmin));
				position = position * (force / dist);
				//pos.mul(force / dist);
				break;
			}
    		case AcceleratorCatEnum::ACCELERATOR_CAT_PARTICLE_LIFE_R: {
				force = dist < rmin ? (dist / rmin - 1) : accelerateScalar * (1 - godot::Math::abs(1 + rmin - 2 * dist) / (1 - rmin));
				position = position * (force / (dist * dist) );
				break;
			}
    		case AcceleratorCatEnum::ACCELERATOR_CAT_PARTICLE_LIFE_R2: {
				force = dist < rmin ? (dist / rmin - 1) : accelerateScalar * (1 - godot::Math::abs(1 + rmin - 2 * dist) / (1 - rmin));
				position = position * (force / (dist * dist * dist) );
				break;
			}
		}
	}
}

godot::Vector3 DefaultAccelerator::accelerate(float a, godot::Vector3 pos) {
	godot::Vector3 res = godot::Vector3(0, 0, 0);
	if (a >= 0.001f) {
		res = pos * a;
	}
	return res;
}