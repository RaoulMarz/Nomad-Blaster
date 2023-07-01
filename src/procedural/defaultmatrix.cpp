#include "defaultmatrix.h"

int DefaultMatrix::size() {
	return mySize;
}

float DefaultMatrix::get(int i, int j) {
	float res = 0.0f;
	if (mySize > 0) {
		res = values[i * mySize + j];
	}
	return res;
}

void DefaultMatrix::set(int i, int j, float value) {
	if (mySize > 0) {
		values[i * mySize + j] = value;
	}
}

DefaultMatrix* DefaultMatrix::deepCopy() {
	DefaultMatrix* result = new DefaultMatrix(mySize);
	for (int i = 0; i < mySize; i++) {
		for (int j = 0; j < mySize; j++) {
			result->set(i, j, values[i * mySize + j]);
		}
	}
	return result;
}

void DefaultMatrix::zero() {
	values.clear();
	for (int i = 0; i < mySize; i++) {
		for (int j = 0; j < mySize; j++) {
			//values[i][j] = 0;
			values.push_back(0);
		}
	}
}

void DefaultMatrix::randomize() {
	values.clear();
	godot::RandomNumberGenerator randNumGen;// = new RandomNumberGenerator();
	for (int i = 0; i < mySize; i++) {
		for (int j = 0; j < mySize; j++) {
			//values[i][j] = 2 * randNumGen.randi() - 1;
			values.push_back(2 * randNumGen.randf() - 1);
		}
	}
}

DefaultMatrix::DefaultMatrix(int size) {
	mySize = size;
	//for (int i = 0; i < size; i++) {
	//	values[i] = new float[size];
	//}
	zero();
}
