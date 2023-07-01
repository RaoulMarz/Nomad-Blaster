#ifndef DEFAULT_MATRIXGEN_CLASS_H
#define DEFAULT_MATRIXGEN_CLASS_H

#include <string>
#include <vector>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include "infowrapper.h"
#include "defaultmatrix.h"

enum MatrixTopologyEnum {
    MATRIX_TOPOLOGY_NONE,
    MATRIX_TOPOLOGY_SYMMETRY,
    MATRIX_TOPOLOGY_CHAINS,
    MATRIX_TOPOLOGY_CHAINS2,
    MATRIX_TOPOLOGY_CHAINS3,
    MATRIX_TOPOLOGY_SNAKES,
    MATRIX_TOPOLOGY_ZERO
};

class DefaultMatrixGenerator {
    private:
        std::string topology = "symmetry";
        int matSize = 0;
        std::map<std::string, MatrixTopologyEnum> mapMatrixTypes;

        MatrixTopologyEnum getMatrixTopology(std::string matrixClassTopology);
        void initMatrixMap();
    public:
        DefaultMatrix makeMatrix(int size);
        DefaultMatrix makeMatrix(int size, DefaultMatrix activeMatrix);
        DefaultMatrixGenerator(std::string matrixClassTopology, int size);
        DefaultMatrixGenerator();
};

#endif