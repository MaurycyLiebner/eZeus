#include "eresourcebuildingbase.h"

#include "characters/actions/ecarttransporteraction.h"

eResourceBuildingBase::eResourceBuildingBase(
        eGameBoard& board,
        const eBuildingType type,
        const int sw, const int sh,
        const int maxEmployees,
        const eResourceType resType) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees),
    mResType(resType) {

}

eResourceBuildingBase::~eResourceBuildingBase() {
    if(mCart) mCart->kill();
}

void eResourceBuildingBase::timeChanged(const int by) {
    if(enabled()) {
        if(!mCart) {
            spawnCart(mCart, eCartActionTypeSupport::give);
        } else if(mCart && mCart->waiting() && mResource > 0) {
            const int a = mCart->add(mResType, mResource);
            mResource -= a;
        }
    }
    eEmployingBuilding::timeChanged(by);
}

int eResourceBuildingBase::add(const eResourceType type,
                               const int count) {
    if(type != mResType) return 0;

    const int r = std::clamp(mResource + count, 0, mMaxResource);
    const int result = r - mResource;
    mResource = r;
    return result;
}

int eResourceBuildingBase::take(const eResourceType type,
                                const int count) {
    if(type != mResType) return 0;

    const int result = std::clamp(count, 0, mResource);
    mResource -= result;
    return result;
}

int eResourceBuildingBase::count(const eResourceType type) const {
    if(type != mResType) return 0;
    return mResource;
}

int eResourceBuildingBase::spaceLeft(const eResourceType type) const {
    if(type != mResType) return 0;
    return mMaxResource - mResource;
}

std::vector<eCartTask> eResourceBuildingBase::cartTasks() const {
    std::vector<eCartTask> tasks;

    if(mResource > 0) {
        eCartTask task;
        task.fType = eCartActionType::give;
        task.fResource = mResType;
        task.fMaxCount = mResource;
        tasks.push_back(task);
    }

    return tasks;
}
