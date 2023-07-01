#ifndef DEFAULT_TYPESETTER_CLASS_H
#define DEFAULT_TYPESETTER_CLASS_H

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

enum ParticleTypeEnum {
    PARTICLETYPE_NONE = 0,
    PARTICLETYPE_RANDOM,
    PARTICLETYPE_RANDOMIZE10,
    PARTICLETYPE_SLICES,
    PARTICLETYPE_ONION,
    PARTICLETYPE_ROTATE,
    PARTICLETYPE_FLIP,
    PARTICLETYPE_MORE_FIRST,
    PARTICLETYPE_KILLSTILL
};

class DefaultTypeSetter {
    private:
        std::string flavour;

        std::map<std::string, ParticleTypeEnum> mapParticleTypes;
        ParticleTypeEnum getEnumType(std::string strType);
        void initTypeMap();
    public:
        DefaultTypeSetter();
        DefaultTypeSetter(std::string setFlavour);
        //void set(godot::Vector3 position, int type, int nTypes);
        int getType(godot::Vector3 position, godot::Vector3 velocity, int type, int nTypes);
        std::string getFlavour() const;

        friend std::ostream& operator << (std::ostream& outs, DefaultTypeSetter const& p);
        operator std::string() const;
        //friend std::string to_string(const DefaultTypeSetter& value);
};

#endif