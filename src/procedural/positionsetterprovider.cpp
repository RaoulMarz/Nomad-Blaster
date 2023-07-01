#include "positionsetterprovider.h"

std::vector<InfoWrapper<DefaultPositionSetter>> PositionSetterProvider::create() {
    std::vector<InfoWrapper<DefaultPositionSetter>> result;
    result.push_back(InfoWrapper("uniform", DefaultPositionSetter("uniform")));
    result.push_back(InfoWrapper("uniform circle", DefaultPositionSetter("uniform circle")));
    result.push_back(InfoWrapper("centered", DefaultPositionSetter("centered")));
    result.push_back(InfoWrapper("centered circle", DefaultPositionSetter("centered circle")));
    result.push_back(InfoWrapper("ring", DefaultPositionSetter("ring")));
    result.push_back(InfoWrapper("type battle", DefaultPositionSetter("type battle")));
    result.push_back(InfoWrapper("type wheel", DefaultPositionSetter("type wheel")));
    result.push_back(InfoWrapper("line", DefaultPositionSetter("line")));
    result.push_back(InfoWrapper("spiral", DefaultPositionSetter("spiral")));
    return result;
}