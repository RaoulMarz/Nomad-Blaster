#include "matrixgeneratorprovider.h"
#include "physicssettings.h"

std::vector<InfoWrapper<DefaultMatrixGenerator>> MatrixGeneratorProvider::create() {
	std::vector<InfoWrapper<DefaultMatrixGenerator>> result;
	godot::UtilityFunctions::print("MatrixGeneratorProvider::create() <1> : ", godot::String(" -- start"));
	int matrixSize = PhysicsSettings::getMatrixSize();
    godot::Vector2 valueDebug(matrixSize, matrixSize);
	godot::UtilityFunctions::print("MatrixGeneratorProvider::create() <2> : ", godot::String(" -- getMatrixSize() = "), godot::UtilityFunctions::var_to_str(valueDebug));

	if ((matrixSize >= 2) && (matrixSize <= 50)) {
		try {
            result.push_back(InfoWrapper<DefaultMatrixGenerator>("default", DefaultMatrixGenerator()));
			//result.push_back(InfoWrapper<DefaultMatrixGenerator>("fully random", DefaultMatrixGenerator("fully random", matrixSize)));
			//result.push_back(InfoWrapper<DefaultMatrixGenerator>("symmetry", DefaultMatrixGenerator("symmetry", matrixSize)));
			result.push_back(InfoWrapper<DefaultMatrixGenerator>("chains", DefaultMatrixGenerator("chains", matrixSize)));
			godot::UtilityFunctions::print("MatrixGeneratorProvider::create() <2--A> : ", godot::String(" -- added <chains> "));
			result.push_back(InfoWrapper<DefaultMatrixGenerator>("chains 2", DefaultMatrixGenerator("chains 2", matrixSize)));
			godot::UtilityFunctions::print("MatrixGeneratorProvider::create() <2--B> : ", godot::String(" -- added <chains 2> "));
			result.push_back(InfoWrapper<DefaultMatrixGenerator>("chains 3", DefaultMatrixGenerator("chains 3", matrixSize)));
			godot::UtilityFunctions::print("MatrixGeneratorProvider::create() <2--C> : ", godot::String(" -- added <chains 3> "));
			result.push_back(InfoWrapper<DefaultMatrixGenerator>("snakes", DefaultMatrixGenerator("snakes", matrixSize)));
			godot::UtilityFunctions::print("MatrixGeneratorProvider::create() <2--D> : ", godot::String(" -- added <snakes> "));
			result.push_back(InfoWrapper<DefaultMatrixGenerator>("zero", DefaultMatrixGenerator("zero", matrixSize)));
			godot::UtilityFunctions::print("MatrixGeneratorProvider::create() <2--E> : ", godot::String(" -- added <zero> "));
		} catch (std::exception ex) {
			godot::UtilityFunctions::print("MatrixGeneratorProvider::create(), exception = ", godot::String(ex.what()));
		}
		godot::UtilityFunctions::print("MatrixGeneratorProvider::create() <3> : ", godot::String(" -- added matrices list "));
	}

	return result;
}