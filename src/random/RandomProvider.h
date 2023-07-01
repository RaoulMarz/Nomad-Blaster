/* 
 * File:   RandomProvider.h
 * Author: raoul
 *
 * Created on 09 April 2020, 5:39 PM
 */

#ifndef RANDOMPROVIDER_H
#define RANDOMPROVIDER_H

#include <vector>
#include <string>
#include "RandomUtility.h"

class RandomProvider {
public:
    RandomProvider(std::vector<int> randomNumbers);
    RandomProvider();
    RandomProvider(const RandomProvider& orig);
    virtual ~RandomProvider();
    
    int getIntInRange(int low, int high);
    double getDoubleInRange(double low, double high);
    float getFloatInRange(float low, float high);
    std::vector<float> getFloatVector(int count, float minVal, float maxVal);
    std::vector<int> getIntVector(int count, int minVal, int maxVal);
    float getFloatExtent(float value);
    int getIntExtent(int value);
private:
    std::vector<int> randomNumberCache;
    int currentTrackIndex = 0;
};

#endif /* RANDOMPROVIDER_H */

