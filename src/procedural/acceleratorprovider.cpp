#include "acceleratorprovider.h"

std::vector<InfoWrapper<DefaultAccelerator>> AcceleratorProvider::create() {
	std::vector<InfoWrapper<DefaultAccelerator>> result;
	result.push_back(InfoWrapper("particle-life", DefaultAccelerator("particle-life")));
    result.push_back(InfoWrapper("particle-life-r", DefaultAccelerator("particle-life-r")));
    result.push_back(InfoWrapper("particle-life-r2", DefaultAccelerator("particle life2")));
    result.push_back(InfoWrapper("rotator-90", DefaultAccelerator("rotator-90")));
    result.push_back(InfoWrapper("rotator-attr", DefaultAccelerator("rotator-attr")));
	return result;
}