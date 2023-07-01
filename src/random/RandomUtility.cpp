#include "RandomUtility.h"
#include <functional>
#include <random>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <array>

static std::mt19937_64 randomBuilder;
static int seed;
static bool seqset = false;

static std::string const default_chars =
        "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

void RandomUtility::setRandomSeed(int pSeed) {
    if (seqset == false) {
        seqset = true;
        RandomUtility::setSeedSequence();
    }
    seed = pSeed;
    randomBuilder.seed(seed);
}

void RandomUtility::setSeedSequence() {
    std::array<int, 624> seed_data;
    std::random_device r;
    std::generate_n(seed_data.data(), seed_data.size(), std::ref(r));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    randomBuilder = std::mt19937_64(seq);
}

float RandomUtility::getFloat() {
    return float(randomBuilder()) / float(randomBuilder.max());
}

int RandomUtility::getIntInRange(int low, int high) {
    std::uniform_int_distribution<int> dice(low, high);
    //std::mt19937(seed));
    int res = dice(randomBuilder);
    return res;
}

double RandomUtility::getDoubleInRange(double low, double high) {
    std::uniform_real_distribution<double> dice(low, high);
    double res = dice(randomBuilder);
    return res;
}

std::vector<float> RandomUtility::getFloatVector(int count, float minVal, float maxVal) {
    std::vector<float> res;
    for (int ix = 0; ix < count; ix++) {
        res.push_back(RandomUtility::getDoubleInRange(minVal, maxVal));
    }
    return res;
}

std::vector<int> RandomUtility::getIntVector(int count, int minVal, int maxVal) {
    std::vector<int> res;
    for (int ix = 0; ix < count; ix++) {
        res.push_back(RandomUtility::getIntInRange(minVal, maxVal));
    }
    return res;
}

/* https://codereview.stackexchange.com/questions/118949/random-string-generator */
std::string RandomUtility::random_string(std::string const &allowed_chars, size_t len) {
    std::string charRangeSet;
    if (allowed_chars.length() <= 0)
        charRangeSet = default_chars;
    else
        charRangeSet = allowed_chars;
    std::mt19937_64 gen{ std::random_device()()};
    std::uniform_int_distribution<size_t> chars_distribution{ 0, charRangeSet.length() - 1};

    std::string ret;
    std::generate_n(std::back_inserter(ret), len, [&] {
        return charRangeSet[chars_distribution(gen)]; });
    return ret;
}

std::string RandomUtility::random_string_range(std::string const &allowed_chars/* = default_chars*/, size_t minlen, size_t maxlen) {
    int slen = RandomUtility::getIntInRange(minlen, maxlen);
    slen = slen <= minlen ? minlen : slen;
    return random_string(allowed_chars, slen);
}
