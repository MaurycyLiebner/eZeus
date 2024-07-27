#include "estoragebuilding.h"

#include "engine/egameboard.h"
#include "characters/ecarttransporter.h"

eStorageBuilding::eStorageBuilding(eGameBoard& board,
                                   const eBuildingType type,
                                   const int sw, const int sh,
                                   const int maxEmployees,
                                   const eResourceType canAccept,
                                   const int spaceCount) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees),
    mCanAccept(canAccept & board.supportedResources()),
    mSpaceCount(spaceCount) {
    const auto all = eResourceTypeHelpers::extractResourceTypes(mCanAccept);
    for(const auto a : all) {
        if(a == eResourceType::sculpture) {
            mMaxCount[a] = mSpaceCount;
        } else {
            mMaxCount[a] = 4*mSpaceCount;
        }
    }
    board.registerStorBuilding(this);
    setStashable(mCanAccept);
}

eStorageBuilding::~eStorageBuilding() {
    if(mCart1) mCart1->kill();
    if(mCart2) mCart2->kill();
    getBoard().unregisterStorBuilding(this);
}

void eStorageBuilding::timeChanged(const int by) {
    eEmployingBuilding::timeChanged(by);
    if(enabled()) {
        if(!mCart1) mCart1 = spawnCart();
        if(!mCart2) mCart2 = spawnCart();
    }
}

int eStorageBuilding::addNotAccept(const eResourceType type, const int count) {
    const bool sculpt = type == eResourceType::sculpture;
    const int sspace = sculpt ? 1 : 4;
    const int max = mMaxCount[type];
    const int ccount = this->count(type);
    int added = 0;
    const int maxRem = std::max(0, max - ccount);
    int rem = std::min(maxRem, count);
    for(int i = 0; i < mSpaceCount && rem > 0; i++) {
        const auto t = mResource[i];
        int& c = mResourceCount[i];
        if(t == type) {
            const int dep = std::min(sspace - c, rem);
            rem -= dep;
            c += dep;
            added += dep;
        }
    }
    for(int i = 0; i < mSpaceCount && rem > 0; i++) {
        auto& t = mResource[i];
        int& c = mResourceCount[i];
        if(t == eResourceType::none) {
            t = type;
            const int dep = std::min(sspace, rem);
            rem -= dep;
            c += dep;
            added += dep;
        }
    }
    return added;
}

int eStorageBuilding::add(const eResourceType type, const int count) {
    if(!static_cast<bool>(mAccept & type)) return 0;
    return addNotAccept(type, count);
}

int eStorageBuilding::take(const eResourceType type, const int count) {
    int rem = count;
    for(int i = 0; i < mSpaceCount && rem > 0; i++) {
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
    addFromStash();
    return count - rem;
}

int eStorageBuilding::count(const eResourceType type) const {
    return sCount(type, mResourceCount, mResource, mSpaceCount);
}

int eStorageBuilding::spaceLeft(const eResourceType type) const {
    return sSpaceLeft(type, mResourceCount, mResource,
                      mAccept, mMaxCount, mSpaceCount);
}


int eStorageBuilding::spaceLeftDontAccept(const eResourceType type) const {
    return sSpaceLeftDontAccept(type, mResourceCount, mResource,
                                mMaxCount, mSpaceCount);
}

std::vector<eCartTask> eStorageBuilding::cartTasks() const {
    std::vector<eCartTask> tasks;

    const auto gets = eResourceTypeHelpers::extractResourceTypes(mGet);
    const auto empties = eResourceTypeHelpers::extractResourceTypes(mEmpty);

    for(const auto g : gets) {
        const int space = spaceLeft(g);
        if(space > 0) {
            eCartTask task;
            task.fType = eCartActionType::take;
            task.fResource = g;
            task.fMaxCount = space;
            tasks.push_back(task);
        }
    }

    for(const auto e : empties) {
        const int c = count(e);
        if(c > 0) {
            eCartTask task;
            task.fType = eCartActionType::give;
            task.fResource = e;
            task.fMaxCount = c;
            tasks.push_back(task);
        }
    }

    return tasks;
}

int eStorageBuilding::sCount(const eResourceType type,
                             const int resourceCount[15],
                             const eResourceType resourceType[15],
                             const int spaceCount) {
    int result = 0;
    for(int i = 0; i < spaceCount; i++) {
        const auto t = resourceType[i];
        if(static_cast<bool>(t & type)) {
            result += resourceCount[i];
        }
    }
    return result;
}

int eStorageBuilding::sSpaceLeftDontAccept(
        const eResourceType type,
        const int resourceCount[15],
        const eResourceType resourceType[15],
        const std::map<eResourceType, int>& maxCounts,
        const int spaceCount) {
    const bool sculpt = type == eResourceType::sculpture;
    const int sspace = sculpt ? 1 : 4;
    int space = 0;
    int count = 0;
    for(int i = 0; i < spaceCount; i++) {
        const int c = resourceCount[i];
        const auto t = resourceType[i];
        if(c == 0) {
            space += sspace;
        } else if(static_cast<bool>(t & type)) {
            space += sspace - c;
            count += c;
        }
    }
    const int max = maxCounts.at(type);
    return std::min(std::max(0, max - count), space);
}

int eStorageBuilding::sSpaceLeft(
        const eResourceType type,
        const int resourceCount[15],
        const eResourceType resourceType[15],
        const eResourceType accepts,
        const std::map<eResourceType, int>& maxCounts,
        const int spaceCount) {
    if(!static_cast<bool>(accepts & type)) return 0;
    return sSpaceLeftDontAccept(type, resourceCount,
                                resourceType, maxCounts,
                                spaceCount);
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

void eStorageBuilding::read(eReadStream& src) {
    eEmployingBuilding::read(src);

    src >> mGet;
    src >> mEmpty;
    src >> mAccept;

    for(int i = 0; i < 15; i++) {
        src >> mResourceCount[i];
    }

    for(int i = 0; i < 15; i++) {
        src >> mResource[i];
    }

    int nc;
    src >> nc;
    for(int i = 0; i < nc; i++) {
        eResourceType rt;
        src >> rt;
        int c;
        src >> c;
        mMaxCount[rt] = c;
    }

    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mCart1 = static_cast<eCartTransporter*>(c);
    });
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mCart2 = static_cast<eCartTransporter*>(c);
    });
}

void eStorageBuilding::write(eWriteStream& dst) const {
    eEmployingBuilding::write(dst);

    dst << mGet;
    dst << mEmpty;
    dst << mAccept;

    for(int i = 0; i < 15; i++) {
        dst << mResourceCount[i];
    }

    for(int i = 0; i < 15; i++) {
        dst << mResource[i];
    }

    dst << mMaxCount.size();
    for(const auto& trc : mMaxCount) {
        dst << trc.first;
        dst << trc.second;
    }
    dst.writeCharacter(mCart1);
    dst.writeCharacter(mCart2);
}
