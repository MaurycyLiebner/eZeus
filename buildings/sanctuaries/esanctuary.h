#ifndef ESANCTUARY_H
#define ESANCTUARY_H

#include "../eemployingbuilding.h"

#include "esanctuaryblueprint.h"
#include "esanctbuilding.h"

class eBuildingTextures;

class eSanctuary : public eEmployingBuilding {
public:
    using eTexCollPtr = eTextureCollection eBuildingTextures::*;
    eSanctuary(const eTexCollPtr statues,
               const eTexCollPtr monuments,
               eGameBoard& board,
               const eBuildingType type,
               const int sw, const int sh,
               const int maxEmployees);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const
    { return nullptr; }

    void timeChanged(const int by);

    int spaceLeft(const eResourceType type) const;
    int add(const eResourceType type, const int count);

    std::vector<eCartTask> cartTasks() const;

    eTexCollPtr statues() const { return mStatues; }
    eTexCollPtr monuments() const { return mMonuments; }

    void registerElement(const stdsptr<eSanctBuilding>& e);

    eSanctCost cost() const;
private:
    const eTexCollPtr mStatues;
    const eTexCollPtr mMonuments;

    eSanctCost mStored{0, 0, 0};

    stdsptr<eCartTransporter> mCart;

    std::vector<stdsptr<eSanctBuilding>> mElements;
};

#endif // ESANCTUARY_H
