#ifndef COLLECTION_ALGORITHMS_H
#define COLLECTION_ALGORITHMS_H

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class CollectionAlgoritms
{
public:
    template <typename StringType>
    static size_t levenshtein_distance(const StringType &s1, const StringType &s2)
    {
        const size_t m = s1.size();
        const size_t n = s2.size();
        if (m == 0)
            return n;
        if (n == 0)
            return m;
        std::vector<size_t> costs(n + 1);
        std::iota(costs.begin(), costs.end(), 0);
        size_t i = 0;
        for (auto c1 : s1)
        {
            costs[0] = i + 1;
            size_t corner = i;
            size_t j = 0;
            for (auto c2 : s2)
            {
                size_t upper = costs[j + 1];
                costs[j + 1] = (c1 == c2) ? corner
                                          : 1 + std::min(std::min(upper, corner), costs[j]);
                corner = upper;
                ++j;
            }
            ++i;
        }
        return costs[n];
    }
};

#endif