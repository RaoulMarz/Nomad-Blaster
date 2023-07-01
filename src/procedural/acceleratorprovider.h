#ifndef ACCELERATOR_PROVIDER_CLASS_H
#define ACCELERATOR_PROVIDER_CLASS_H

#include "defaultaccelerator.h"
#include "infowrapper.h"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <string>
#include <vector>

class AcceleratorProvider {
public:
	static std::vector<InfoWrapper<DefaultAccelerator>> create();
};

#endif