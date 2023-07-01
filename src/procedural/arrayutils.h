#ifndef ARRAY_UTILS_CLASS_H
#define ARRAY_UTILS_CLASS_H

#include <vector>

/*template <typename T>*/
class ArrayUtils {
    public:

    template <typename T>
    static void swap(std::vector<T> array, int i, int j) {
        T h = array[i];
        array[i] = array[j];
        array[j] = h;
    }
    
    static int findFirstIndexWithLess(std::vector<int> &a, std::vector<int> &b) {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] < b[i]) {
                return i;
            }
        }
        return -1;
    }
};

#endif