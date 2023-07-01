#include "typesetterprovider.h"

std::vector<InfoWrapper<DefaultTypeSetter>> TypeSetterProvider::create() {
	std::vector<InfoWrapper<DefaultTypeSetter>> result;
  result.push_back(InfoWrapper("random", DefaultTypeSetter("random")));
	result.push_back(InfoWrapper("randomize10", DefaultTypeSetter("randomize10")));
  result.push_back(InfoWrapper("slices", DefaultTypeSetter("slices")));
  result.push_back(InfoWrapper("onion", DefaultTypeSetter("onion")));
  result.push_back(InfoWrapper("rotate", DefaultTypeSetter("rotate")));
  result.push_back(InfoWrapper("flip", DefaultTypeSetter("flip")));
  result.push_back(InfoWrapper("more-first", DefaultTypeSetter("more-first")));
  result.push_back(InfoWrapper("kill-still", DefaultTypeSetter("kill-still")));
	return result;
}
