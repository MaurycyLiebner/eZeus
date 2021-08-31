#include "estoragebuilding.h"

eStorageBuilding::eStorageBuilding(eGameBoard& board,
                                   const eBuildingType type,
                                   const int sw, const int sh,
                                   const int maxEmployees,
                                   const eResourceType canAccept) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees),
    mCanAccept(canAccept) {

}

int eStorageBuilding::add(const eResourceType type, const int count) {
    if(!static_cast<bool>(mAccept & type)) return 0;
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
        if(static_cast<bool>(t & type)) {
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

int eStorageBuilding::count(const eResourceType type) const {
    return sCount(type, mResourceCount, mResource);
}

int eStorageBuilding::spaceLeft(const eResourceType type) const {
    return sSpaceLeft(type, mResourceCount, mResource, mAccept);
}

int eStorageBuilding::sCount(const eResourceType type,
                             const int resourceCount[8],
                             const eResourceType resourceType[8]) {
    int result = 0;
    for(int i = 0; i < 8; i++) {
        const auto t = resourceType[i];
        if(static_cast<bool>(t & type)) {
            result += resourceCount[i];
        }
    }
    return result;
}

int eStorageBuilding::sSpaceLeft(const eResourceType type,
                                 const int resourceCount[8],
                                 const eResourceType resourceType[8],
                                 const eResourceType accepts) {
    if(!static_cast<bool>(accepts & type)) return 0;
    int space = 0;
    for(int i = 0; i < 8; i++) {
        const int c = resourceCount[i];
        const auto t = resourceType[i];
        if(c == 0) {
            space += 4;
        } else if(static_cast<bool>(t & type)) {
            space += 4 - c;
        }
    }
    return space;
}

void eStorageBuilding::setOrders(const eResourceType get,
                                 const eResourceType empty,
                                 const eResourceType accept) {
    mGet = get;
    mEmpty = empty;
    mAccept = accept | get;
}

void eStorageBuilding::getOrders(eResourceType& get,
                                 eResourceType& empty,
                                 eResourceType& accept) const {
    get = mGet;
    empty = mEmpty;
    accept = mAccept;
}
