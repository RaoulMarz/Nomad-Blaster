#ifndef MATH_RANGE_CLASS_H
#define MATH_RANGE_CLASS_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>

class MathRange {
public:
	static inline void wrap(godot::Vector3 xVec) {
		xVec.x = wrap(xVec.x);
		xVec.y = wrap(xVec.y);
		xVec.z = 0; //todo 3D
	}

	static inline void clamp(godot::Vector3 xVec) {
		xVec.x = clamp(xVec.x);
		xVec.y = clamp(xVec.y);
		xVec.z = 0; // todo 3D
	}

private:
	static inline float wrap(float value) {
		return modulo(value + 1, 2) - 1;
	}

	static inline float clamp(float val) {
		if (val < -1) {
			return -1;
		} else if (val > 1) {
			return 1;
		}
		return (float)val;
	}

	static inline float modulo(float a, float b) {
		if (a < 0) {
			do {
				a += b;
			} while (a < 0);
			return (float)a;
		} else if (a >= b) {
			do {
				a -= b;
			} while (a >= b);
			return (float)a;
		}
		return (float)a;
	}
};

#endif