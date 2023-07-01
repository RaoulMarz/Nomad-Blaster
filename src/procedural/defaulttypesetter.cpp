#include "defaulttypesetter.h"

void DefaultTypeSetter::initTypeMap() {
    mapParticleTypes["none"] = ParticleTypeEnum::PARTICLETYPE_NONE;
    mapParticleTypes["random"] = ParticleTypeEnum::PARTICLETYPE_RANDOM;
    mapParticleTypes["randomize10"] = ParticleTypeEnum::PARTICLETYPE_RANDOMIZE10;
    mapParticleTypes["slices"] = ParticleTypeEnum::PARTICLETYPE_SLICES;
    mapParticleTypes["onion"] = ParticleTypeEnum::PARTICLETYPE_ONION;
    mapParticleTypes["rotate"] = ParticleTypeEnum::PARTICLETYPE_ROTATE;
    mapParticleTypes["flip"] = ParticleTypeEnum::PARTICLETYPE_FLIP;
    mapParticleTypes["more-first"] = ParticleTypeEnum::PARTICLETYPE_MORE_FIRST;
    mapParticleTypes["kill-still"] = ParticleTypeEnum::PARTICLETYPE_KILLSTILL;
}

ParticleTypeEnum DefaultTypeSetter::getEnumType(std::string strType) {
    ParticleTypeEnum result = ParticleTypeEnum::PARTICLETYPE_NONE;
    if ( (mapParticleTypes.size() > 0) && (strType.length() > 0) ) {
        if (mapParticleTypes.find(strType) != mapParticleTypes.end() )
            result = mapParticleTypes[strType];
    }
    return result;
}

DefaultTypeSetter::DefaultTypeSetter() {
    initTypeMap();
}

DefaultTypeSetter::DefaultTypeSetter(std::string setFlavour) {
    initTypeMap();
    ParticleTypeEnum particleType = getEnumType(setFlavour);
}

int DefaultTypeSetter::getType(godot::Vector3 position, godot::Vector3 velocity, int type, int nTypes) {
    int result = 0;
    return result;
}

std::string DefaultTypeSetter::getFlavour() const {
    return flavour;
}

std::ostream& operator << (std::ostream& outs, DefaultTypeSetter const& p)
{
  return outs << "(enum" << p.getFlavour() << ")";
}

DefaultTypeSetter::operator std::string() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}
/*
std::string to_string(const DefaultTypeSetter& value)
{
  std::ostringstream ss;
  ss << value;
  return ss.str();
}
*/