/* 
 * File:   RandomProvider.cpp
 * Author: raoul
 * 
 * Created on 09 April 2020, 5:39 PM
 */

#include <chrono>
#include "RandomProvider.h"

RandomProvider::RandomProvider(std::vector<int> randomNumbers) {
    auto seedG = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    RandomUtility::setRandomSeed(seedG);
    randomNumberCache = randomNumbers;
}

RandomProvider::RandomProvider() {
    auto seedG = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    RandomUtility::setRandomSeed(seedG);
}

RandomProvider::RandomProvider(const RandomProvider& orig) {
    auto seedG = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    RandomUtility::setRandomSeed(seedG);
}

RandomProvider::~RandomProvider() {
}

int RandomProvider::getIntInRange(int low, int high) {
    int res = 0;
    res = low + (randomNumberCache[currentTrackIndex] / std::numeric_limits<int>::max()) *  (high - low);
    currentTrackIndex += 1;
    return res;
}

double RandomProvider::getDoubleInRange(double low, double high) {
    double res = 0.0;
    res = low + double(double(randomNumberCache[currentTrackIndex] + 0.0001) / double(std::numeric_limits<int>::max())) * (high - low);
    currentTrackIndex += 1;
    return res;
}

float RandomProvider::getFloatInRange(float low, float high) {
    float res = 0.0f;
    res = low + float(float(randomNumberCache[currentTrackIndex] + 0.0001) / float(std::numeric_limits<int>::max())) * (high - low);
    currentTrackIndex += 1;
    return res;
}

std::vector<float> RandomProvider::getFloatVector(int count, float minVal, float maxVal) {
    std::vector<float> res;
    for (int ix = 0; ix < count; ix++) {
        float val = RandomUtility::getDoubleInRange(minVal, maxVal);
        res.push_back(val);
    }
    return res;
}

std::vector<int> RandomProvider::getIntVector(int count, int minVal, int maxVal) {
    std::vector<int> res;
    for (int ix = 0; ix < count; ix++) {
        int val = RandomUtility::getIntInRange(minVal, maxVal);
        res.push_back(val);
    }
    return res;
}

float RandomProvider::getFloatExtent(float value) {
    float res = getFloatInRange(0.0f, value);
    return res;
}

int RandomProvider::getIntExtent(int value) {
    int res = getIntInRange(0, value);
    return res;
}
