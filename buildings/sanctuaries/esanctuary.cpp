#include "esanctuary.h"

eSanctuary::eSanctuary(const eTexCollPtr statues,
                       const eTexCollPtr monuments,
                       eGameBoard& board,
                       const eBuildingType type,
                       const int sw, const int sh,
                       const int maxEmployees) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees),
    mStatues(statues), mMonuments(monuments) {}

void eSanctuary::registerElement(const stdsptr<eSanctBuilding>& e) {
    mElements.push_back(e);
}

eSanctCost eSanctuary::cost() const {
    eSanctCost c{0, 0, 0};
    for(const auto& e : mElements) {
        c += e->cost();
    }
    return c;
}

void eSanctuary::timeChanged(const int by) {
    const int t = time();
    if(!mCart && t > mCartSpawnTime) {
        mCartSpawnTime = t + mCartWaitTime;
        const auto c = cost();
        if(c.fMarble > 0) {
            spawnTakeCart(mCart, mCartSpawnTime,
                          mCartWaitTime, eResourceType::marble);
        } else if(c.fWood > 0) {
            spawnTakeCart(mCart, mCartSpawnTime,
                          mCartWaitTime, eResourceType::wood);
        } else if(c.fSculpture > 0) {
            spawnTakeCart(mCart, mCartSpawnTime,
                          mCartWaitTime, eResourceType::sculpture);
        }
    }
    eEmployingBuilding::timeChanged(by);
}
