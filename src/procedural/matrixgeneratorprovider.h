#ifndef MATRIX_GENERATOR_PROVIDER_CLASS_H
#define MATRIX_GENERATOR_PROVIDER_CLASS_H

#include "defaultmatrixgenerator.h"
#include "infowrapper.h"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <string>
#include <vector>

class MatrixGeneratorProvider {
	//private static Logger logger = LogManager.getLogger();
public:
	static std::vector<InfoWrapper<DefaultMatrixGenerator>> create();
};

#endif