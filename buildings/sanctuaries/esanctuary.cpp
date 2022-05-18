#include "esanctuary.h"

#include "characters/ecarttransporter.h"

eSanctuary::eSanctuary(const eTexCollPtr statues,
                       const eTexCollPtr monuments,
                       eGameBoard& board,
                       const eBuildingType type,
                       const int sw, const int sh,
                       const int maxEmployees) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees),
    mStatues(statues), mMonuments(monuments) {}

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

void eSanctuary::timeChanged(const int by) {
    if(!mCart) spawnCart(mCart);
    eEmployingBuilding::timeChanged(by);
}

int eSanctuary::spaceLeft(const eResourceType type) const {
    const auto c = cost();
    if(type == eResourceType::marble) {
        return c.fMarble;
    } else if(type == eResourceType::wood) {
        return c.fWood;
    } else if(type == eResourceType::sculpture) {
        return c.fSculpture;
    }
    return 0;
}

int eSanctuary::add(const eResourceType type, const int count) {
    if(type == eResourceType::marble) {
        mStored.fMarble += count;
    } else if(type == eResourceType::wood) {
        mStored.fWood += count;
    } else if(type == eResourceType::sculpture) {
        mStored.fSculpture += count;
    }
    return count;
}


std::vector<eCartTask> eSanctuary::cartTasks() const {
    std::vector<eCartTask> tasks;

    const auto c = cost();

    if(c.fMarble > 0) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::marble;
        task.fMaxCount = c.fMarble;
        tasks.push_back(task);
    }

    if(c.fWood > 0) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::wood;
        task.fMaxCount = c.fWood;
        tasks.push_back(task);
    }

    if(c.fSculpture > 0) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::sculpture;
        task.fMaxCount = c.fSculpture;
        tasks.push_back(task);
    }

    return tasks;
}

void eSanctuary::registerElement(const stdsptr<eSanctBuilding>& e) {
    mElements.push_back(e);
}
