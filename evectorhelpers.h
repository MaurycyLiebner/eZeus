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
    int index(const std::vector<T>& v, const T& t) {
        const auto it = std::find(v.begin(), v.end(), t);
        if(it == v.end()) return -1;
        return it - v.begin();
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

    template <typename T>
    bool same(const std::vector<T>& v1, const std::vector<T>& v2) {
        if(v1.size() == v2.size()) {
            const int iMax = v1.size();
            for(int i = 0; i < iMax; i++) {
                const auto& s1 = v1[i];
                const auto& s2 = v2[i];
                if(s1 != s2) return false;
            }
        } else {
            return false;
        }
        return true;
    }
};

#endif // EVECTORHELPERS_H
