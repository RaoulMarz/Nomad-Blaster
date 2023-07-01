#ifndef POSITION_SETTER_PROVIDER_CLASS_H
#define POSITION_SETTER_PROVIDER_CLASS_H

#include "defaultpositionsetter.h"
#include "infowrapper.h"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <string>
#include <vector>

class PositionSetterProvider {
public:
	static std::vector<InfoWrapper<DefaultPositionSetter>> create();
};

#endif