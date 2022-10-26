#ifndef EVECTORHELPERS_H
#define EVECTORHELPERS_H

#include <vector>
#include <algorithm>

namespace eVectorHelpers {
    template <typename T>
    bool contains(const std::vector<T>& v, const T& t) {
        const auto it = std::find(v.begin(), v.end(), t);
        return it != v.end();
    }

    template <typename T>
    bool remove(std::vector<T>& v, const T& t) {
        const auto it = std::find(v.begin(), v.end(), t);
        if(it != v.end()) {
            v.erase(it);
            return true;
        } else {
            return false;
        }
    }
};

#endif // EVECTORHELPERS_H
