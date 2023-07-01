#ifndef TYPE_SETTER_PROVIDER_CLASS_H
#define TYPE_SETTER_PROVIDER_CLASS_H

#include "defaulttypesetter.h"
#include "infowrapper.h"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <string>
#include <vector>

class TypeSetterProvider {
public:
	static std::vector<InfoWrapper<DefaultTypeSetter>> create();
};

#endif
