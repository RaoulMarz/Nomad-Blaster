#ifndef RANDOM_UTILITY_H
#define RANDOM_UTILITY_H

#include <random>
#include <vector>

class RandomUtility {
private:
    
public:
    static void setRandomSeed(int pSeed);
    static float getFloat();
    static int getIntInRange(int low, int high);
    static double getDoubleInRange(double low, double high);
    static std::vector<float> getFloatVector(int count, float minVal, float maxVal);
    static std::vector<int> getIntVector(int count, int minVal, int maxVal);
    static std::string random_string(std::string const &allowed_chars, size_t len = 15);
    static std::string random_string_range(std::string const &allowed_chars, size_t minlen = 4, size_t maxlen = 20);
    static void setSeedSequence();
};


#endif
