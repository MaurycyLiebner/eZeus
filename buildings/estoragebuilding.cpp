#include "estoragebuilding.h"

eStorageBuilding::eStorageBuilding(eGameBoard& board,
                                   const eBuildingType type,
                                   const int sw, const int sh,
                                   const int maxEmployees,
                                   const eResourceType canAccept) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees),
    mCanAccept(canAccept) {
    const auto all = eResourceTypeHelpers::extractResourceTypes(mCanAccept);
    for(const auto a : all) {
        if(a == eResourceType::sculpture) {
            mMaxCount[a] = 8;
        } else {
            mMaxCount[a] = 32;
        }
    }
}

int eStorageBuilding::add(const eResourceType type, const int count) {
    if(!static_cast<bool>(mAccept & type)) return 0;
    const bool sculpt = type == eResourceType::sculpture;
    const int sspace = sculpt ? 1 : 4;
    int rem = count;
    for(int i = 0; i < 8 && rem > 0; i++) {
        const auto t = mResource[i];
        int& c = mResourceCount[i];
        if(t == type) {
            const int dep = std::min(sspace - c, rem);
            rem -= dep;
            c += dep;
        }
    }
    for(int i = 0; i < 8 && rem > 0; i++) {
        auto& t = mResource[i];
        int& c = mResourceCount[i];
        if(t == eResourceType::none) {
            t = type;
            const int dep = std::min(sspace, rem);
            rem -= dep;
            c += dep;
        }
    }
    const int max = mMaxCount[type];
    return std::min(max, count - rem);
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
    return sSpaceLeft(type, mResourceCount, mResource, mAccept, mMaxCount);
}

void eStorageBuilding::timeChanged(const int by) {
    eEmployingBuilding::timeChanged(by);
    if(mCartTime <= time() && (!mCart1 || !mCart2)) {
        struct eResTask {
            eResTask(const bool get, const eResourceType res) :
                fGet(get), fRes(res) {}

            bool fGet;
            eResourceType fRes;
        };

        std::vector<eResTask> tasks;
        const auto get = eResourceTypeHelpers::extractResourceTypes(mGet);
        const auto empty = eResourceTypeHelpers::extractResourceTypes(mEmpty);
        tasks.reserve(get.size() + empty.size());
        for(const auto g : get) {
            tasks.emplace_back(true, g);
        }
        for(const auto e : empty) {
            tasks.emplace_back(false, e);
        }

        if(!tasks.empty()) {
            if(!mCart1) {
                const int id = rand() % tasks.size();
                const auto& task = tasks[id];
                if(task.fGet) {
                    spawnTakeCart(mCart1, mCartTime, mCartWaitTime, task.fRes);
                } else {
                    spawnGiveCart(mCart1, mCartTime, mCartWaitTime, task.fRes);
                }
            }
            if(!mCart2) {
                const int id = rand() % tasks.size();
                const auto& task = tasks[id];
                if(task.fGet) {
                    spawnTakeCart(mCart2, mCartTime, mCartWaitTime, task.fRes);
                } else {
                    spawnGiveCart(mCart2, mCartTime, mCartWaitTime, task.fRes);
                }
            }
        }
        mCartTime += mCartWaitTime;
    }
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

int eStorageBuilding::sSpaceLeft(
        const eResourceType type,
        const int resourceCount[8],
        const eResourceType resourceType[8],
        const eResourceType accepts,
        const std::map<eResourceType, int>& maxCounts) {
    if(!static_cast<bool>(accepts & type)) return 0;
    const bool sculpt = type == eResourceType::sculpture;
    const int sspace = sculpt ? 1 : 4;
    int space = 0;
    for(int i = 0; i < 8; i++) {
        const int c = resourceCount[i];
        const auto t = resourceType[i];
        if(c == 0) {
            space += sspace;
        } else if(static_cast<bool>(t & type)) {
            space += sspace - c;
        }
    }
    const int max = maxCounts.at(type);
    return std::min(max, space);
}

void eStorageBuilding::setMaxCount(const std::map<eResourceType, int>& m) {
    mMaxCount = m;
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
