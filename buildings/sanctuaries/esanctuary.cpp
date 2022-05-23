#include "esanctuary.h"

#include "characters/ecarttransporter.h"

eSanctuary::eSanctuary(eGameBoard& board,
                       const eBuildingType type,
                       const int sw, const int sh,
                       const int maxEmployees) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees) {}

eSanctuary::~eSanctuary() {
    if(mCart) mCart->kill();
}

eSanctCost eSanctuary::cost() const {
    eSanctCost c{0, 0, 0};
    for(const auto& e : mElements) {
        c += e->cost();
    }
    return c;
}

void eSanctuary::useResources(const eSanctCost& r) {
    mStored.fMarble -= r.fMarble;
    mStored.fWood -= r.fWood;
    mStored.fSculpture -= r.fSculpture;

    mUsed.fMarble += r.fMarble;
    mUsed.fWood += r.fWood;
    mUsed.fSculpture += r.fSculpture;
}

void eSanctuary::timeChanged(const int by) {
    if(!mCart) spawnCart(mCart);
    eEmployingBuilding::timeChanged(by);
}

int eSanctuary::spaceLeft(const eResourceType type) const {
    const auto c = cost();
    if(type == eResourceType::marble) {
        return c.fMarble - mStored.fMarble - mUsed.fMarble;
    } else if(type == eResourceType::wood) {
        return c.fWood - mStored.fWood - mUsed.fWood;
    } else if(type == eResourceType::sculpture) {
        return c.fSculpture - mStored.fSculpture - mUsed.fSculpture;
    }
    return 0;
}

int eSanctuary::add(const eResourceType type, const int count) {
    const int space = spaceLeft(type);
    const int add = std::min(count, space);
    if(type == eResourceType::marble) {
        mStored.fMarble += add;
    } else if(type == eResourceType::wood) {
        mStored.fWood += add;
    } else if(type == eResourceType::sculpture) {
        mStored.fSculpture += add;
    }
    return add;
}


std::vector<eCartTask> eSanctuary::cartTasks() const {
    std::vector<eCartTask> tasks;

    const int m = spaceLeft(eResourceType::marble);
    const int w = spaceLeft(eResourceType::wood);
    const int s = spaceLeft(eResourceType::sculpture);

    if(m) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::marble;
        task.fMaxCount = m;
        tasks.push_back(task);
    }

    if(w) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::wood;
        task.fMaxCount = w;
        tasks.push_back(task);
    }

    if(s) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::sculpture;
        task.fMaxCount = s;
        tasks.push_back(task);
    }

    return tasks;
}

void eSanctuary::registerElement(const stdsptr<eSanctBuilding>& e) {
    mElements.push_back(e);
}