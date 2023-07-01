#ifndef DEFAULT_MATRIX_CLASS_H
#define DEFAULT_MATRIX_CLASS_H

#include <string>
#include <map>
#include <vector>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

class DefaultMatrix {
    private:
        std::string flavour;
        int mySize;
        //float values[][];
        std::vector<float> values;
    public:
        int size();
        float get(int i, int j);
        void set(int i, int j, float value);
        DefaultMatrix* deepCopy();

        void zero();
        void randomize();
        DefaultMatrix(int size);
};

#endif