#include "defaultpositionsetter.h"

/*
oct_compressed.y = Math::abs(oct_compressed.y);
return Math::is_equal_approx(x, p_v.x) && Math::is_equal_approx(y, p_v.y) && Math::is_equal_approx(z, p_v.z);
return Math::is_zero_approx(x) && Math::is_zero_approx(y) && Math::is_zero_approx(z);
Math::snapped(x, p_step.x);
*/
void DefaultPositionSetter::initMembraneMap() {
	mapMembraneTypes["none"] = MembraneEnum::MEMBRANE_NONE;
	mapMembraneTypes["uniform"] = MembraneEnum::MEMBRANE_UNIFORM;
	mapMembraneTypes["unicircle"] = MembraneEnum::MEMBRANE_UNICIRCLE;
	mapMembraneTypes["centered"] = MembraneEnum::MEMBRANE_CENTERED;
	mapMembraneTypes["centered-circle"] = MembraneEnum::MEMBRANE_CENTEREDCIRCLE;
	mapMembraneTypes["ring"] = MembraneEnum::MEMBRANE_RING;
	mapMembraneTypes["battle"] = MembraneEnum::MEMBRANE_BATTLE;
	mapMembraneTypes["wheel"] = MembraneEnum::MEMBRANE_WHEEL;
	mapMembraneTypes["line"] = MembraneEnum::MEMBRANE_BATTLE;
	mapMembraneTypes["spiral"] = MembraneEnum::MEMBRANE_BATTLE;
	mapMembraneTypes["rainbow-spiral"] = MembraneEnum::MEMBRANE_RAINBOWSPIRAL;
}

DefaultPositionSetter::DefaultPositionSetter() {
	membrane = "none";
	initMembraneMap();
}

DefaultPositionSetter::DefaultPositionSetter(std::string positionMembrane) {
	membrane = positionMembrane;
	initMembraneMap();

	unsigned seed = std::chrono::system_clock::now()
							.time_since_epoch()
							.count();
	godot::RandomNumberGenerator randNumGen;
	randNumGen.set_seed(seed);
	float angle = 0.0f;
	float radius = 0.0f;
	int maxRotations = 2;
	int numTypes = nTypes;
	if (numTypes <= 0)
		numTypes = 2;
	if (mapMembraneTypes.size() > 0) {
		MembraneEnum membraneSetType = getMembraneType(positionMembrane);
		switch (membraneSetType) {
			case MembraneEnum::MEMBRANE_NONE: {
				break;
			}
			case MembraneEnum::MEMBRANE_UNICIRCLE: {
				angle = godot::UtilityFunctions::randf() * 2.0f * Math_PI;
				radius = godot::Math::sqrt(godot::UtilityFunctions::randf());
				defPosition.x = godot::Math::cos(angle) * radius;
				defPosition.y = godot::Math::sin(angle) * radius;
				break;
			}
			case MembraneEnum::MEMBRANE_CENTERED: {
				defPosition.x = godot::UtilityFunctions::randf() * 0.3f;
				defPosition.y = godot::UtilityFunctions::randf() * 0.3f;
				break;
			}
			case MembraneEnum::MEMBRANE_CENTEREDCIRCLE: {
				angle = godot::UtilityFunctions::randf() * 2.0f * Math_PI; // * (real_t)godot::Math_PI;
				//radius = positionRng.Randf();
				defPosition.x = godot::Math::cos(angle) * radius;
				defPosition.y = godot::Math::sin(angle) * radius;
				break;
			}
			case MembraneEnum::MEMBRANE_RING: {
				angle = godot::UtilityFunctions::randf() * 2 * Math_PI;
				//radius = 0.9f + 0.02f * positionRng.Randf();
				break;
			}
			case MembraneEnum::MEMBRANE_BATTLE: {
				float centerAngle = type / numTypes * 2 * Math_PI;
				float centerRadius = 0.5f;
				//angle = positionRng.Randf() * 2 * Math_PI;
				//radius = positionRng.Randf() * 0.1f;
				defPosition.x = centerRadius * godot::Math::cos(centerAngle) + godot::Math::cos(angle) * radius;
				defPosition.y = centerRadius * godot::Math::sin(centerAngle) + godot::Math::sin(angle) * radius;
				break;
			}
			case MembraneEnum::MEMBRANE_WHEEL: {
				float centerAngle = type / numTypes * 2 * Math_PI;
				float centerRadius = 0.3f;
				float individualRadius = 0.2f;

				defPosition.x = centerRadius * godot::Math::cos(centerAngle) + randNumGen.randf() * individualRadius;
				defPosition.y = centerRadius * godot::Math::sin(centerAngle) + randNumGen.randf() * individualRadius;
				break;
			}
			case MembraneEnum::MEMBRANE_LINE: {
				defPosition.x = (2 * randNumGen.randf() - 1);
				defPosition.y = (2 * randNumGen.randf() - 1) * 0.15f;
				break;
			}
			case MembraneEnum::MEMBRANE_SPIRAL: {
				float maxRotations = 2;
				float f = randNumGen.randf();
				float angle = maxRotations * 2 * Math_PI * f;

				float spread = 0.5f * godot::Math::min(f, 0.2f);
				radius = 0.9f * f + spread * randNumGen.randf() * spread;
				defPosition.x = radius * godot::Math::cos(angle);
				defPosition.y = radius * godot::Math::sin(angle);
				break;
			}
			case MembraneEnum::MEMBRANE_RAINBOWSPIRAL: {
				float maxRotations = 2;
				float typeSpread = 0.3f / nTypes;
				float f = (type + 1) / (float)(nTypes + 2) + typeSpread * randNumGen.randf();
				if (f < 0) {
					f = 0;
				} else if (f > 1) {
					f = 1;
				}
				float angle = maxRotations * 2 * Math_PI * f;

				float spread = 0.5 * godot::Math::min(f, 0.2f);
				radius = 0.9f * f + spread * randNumGen.randf() * spread;
				defPosition.x = radius * godot::Math::cos(angle);
				defPosition.y = radius * godot::Math::sin(angle);
				break;
			}
		}
	}
}

MembraneEnum DefaultPositionSetter::getMembraneType(std::string positionMembrane) {
	MembraneEnum result = MembraneEnum::MEMBRANE_NONE;
	if ((mapMembraneTypes.size() > 0) && (positionMembrane.length() > 0)) {
		if (mapMembraneTypes.find(positionMembrane) != mapMembraneTypes.end())
			result = mapMembraneTypes[positionMembrane];
	}
	return result;
}

void DefaultPositionSetter::set(godot::Vector3 position, int type, int nTypes) {
	position.x = godot::UtilityFunctions::randf() * 2 - 1;
	position.y = godot::UtilityFunctions::randf() * 2 - 1;
	position.z = 0.0f;
}
