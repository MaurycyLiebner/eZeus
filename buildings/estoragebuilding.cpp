#include "estoragebuilding.h"

int eStorageBuilding::add(const eResourceType type, const int count) {
    int rem = count;
    for(int i = 0; i < 8 && rem > 0; i++) {
        const auto t = mResource[i];
        int& c = mResourceCount[i];
        if(t == type) {
            const int dep = std::min(4 - c, rem);
            rem -= dep;
            c += dep;
        }
    }
    for(int i = 0; i < 8 && rem > 0; i++) {
        auto& t = mResource[i];
        int& c = mResourceCount[i];
        if(t == eResourceType::none) {
            t = type;
            const int dep = std::min(4, rem);
            rem -= dep;
            c += dep;
        }
    }
    return count - rem;
}

int eStorageBuilding::take(const eResourceType type, const int count) {
    int rem = count;
    for(int i = 0; i < 8 && rem > 0; i++) {
        auto& t = mResource[i];
        int& c = mResourceCount[i];
        if(t == type) {
            const int dep = std::min(c, rem);
            rem -= dep;
            c -= dep;
            if(c == 0) {
                t = eResourceType::none;
            }
        }
    }
    return count - rem;
}
