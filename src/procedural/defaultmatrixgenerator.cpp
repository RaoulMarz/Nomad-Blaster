#include "defaultmatrixgenerator.h"

DefaultMatrix DefaultMatrixGenerator::makeMatrix(int size) {
	DefaultMatrix m(size);
	m.randomize();
	return m;
}

DefaultMatrix DefaultMatrixGenerator::makeMatrix(int size, DefaultMatrix activeMatrix) {
	DefaultMatrix m(size);
	m.randomize();
	return m;
}

MatrixTopologyEnum DefaultMatrixGenerator::getMatrixTopology(std::string matrixClassTopology) {
	MatrixTopologyEnum result = MatrixTopologyEnum::MATRIX_TOPOLOGY_NONE;
	if ((matrixClassTopology.length() > 0) && (mapMatrixTypes.size() > 0)) {
		if (mapMatrixTypes.find(matrixClassTopology) != mapMatrixTypes.end())
			result = mapMatrixTypes[matrixClassTopology];
	}
	return result;
}

void DefaultMatrixGenerator::initMatrixMap() {
	mapMatrixTypes["none"] = MatrixTopologyEnum::MATRIX_TOPOLOGY_NONE;
	mapMatrixTypes["symmetry"] = MatrixTopologyEnum::MATRIX_TOPOLOGY_SYMMETRY;
	mapMatrixTypes["chains"] = MatrixTopologyEnum::MATRIX_TOPOLOGY_CHAINS;
	mapMatrixTypes["chains 2"] = MatrixTopologyEnum::MATRIX_TOPOLOGY_CHAINS2;
	mapMatrixTypes["chains 3"] = MatrixTopologyEnum::MATRIX_TOPOLOGY_CHAINS3;
	mapMatrixTypes["snakes"] = MatrixTopologyEnum::MATRIX_TOPOLOGY_SNAKES;
	mapMatrixTypes["zero"] = MatrixTopologyEnum::MATRIX_TOPOLOGY_ZERO;
}

DefaultMatrixGenerator::DefaultMatrixGenerator() {
	initMatrixMap();
	matSize = 6;
	///DefaultMatrix m(matSize);
	///m.randomize();
}

DefaultMatrixGenerator::DefaultMatrixGenerator(std::string matrixClassTopology, int size) {
	if (size > 10000)
		return;
	initMatrixMap();
	matSize = size;
	DefaultMatrix m(size);
	MatrixTopologyEnum enumTopology = getMatrixTopology(matrixClassTopology);
	switch (enumTopology) {
		case MatrixTopologyEnum::MATRIX_TOPOLOGY_NONE:

			break;
		case MatrixTopologyEnum::MATRIX_TOPOLOGY_SYMMETRY:
			m.randomize();
			for (int i = 0; i < m.size(); i++) {
				for (int j = i; j < m.size(); j++) {
					m.set(i, j, m.get(j, i));
				}
			}
			//return m;
			break;
		case MatrixTopologyEnum::MATRIX_TOPOLOGY_CHAINS:
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (j == i || j == (i + 1) % size || j == (i + size - 1) % size) {
						m.set(i, j, 1);
					} else {
						m.set(i, j, -1);
					}
				}
			}
			//return m;
			break;
		case MatrixTopologyEnum::MATRIX_TOPOLOGY_CHAINS2:
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (j == i) {
						m.set(i, j, 1);
					} else if (j == (i + 1) % size || j == (i + size - 1) % size) {
						m.set(i, j, 0.2f);
					} else {
						m.set(i, j, -1);
					}
				}
			}
			break;
		case MatrixTopologyEnum::MATRIX_TOPOLOGY_CHAINS3:
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (j == i) {
						m.set(i, j, 1);
					} else if (j == (i + 1) % size || j == (i + size - 1) % size) {
						m.set(i, j, 0.2);
					} else {
						m.set(i, j, 0);
					}
				}
			}
			break;
		case MatrixTopologyEnum::MATRIX_TOPOLOGY_SNAKES:
			for (int i = 0; i < size; i++) {
				m.set(i, i, 1);
				m.set(i, (i + 1) % m.size(), 0.2);
			}
			break;
		case MatrixTopologyEnum::MATRIX_TOPOLOGY_ZERO:
			//new InfoWrapper<MatrixGenerator>("zero", DefaultMatrix::new)
			break;
		default:
			break;
	}
}