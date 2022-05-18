#ifndef ESANCTUARY_H
#define ESANCTUARY_H

#include "../eemployingbuilding.h"

#include "esanctuaryblueprint.h"
#include "esanctbuilding.h"

class eBuildingTextures;

class eSanctuary : public eEmployingBuilding {
public:
    eSanctuary(eGameBoard& board,
               const eBuildingType type,
               const int sw, const int sh,
               const int maxEmployees);
    ~eSanctuary();

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const
    { return nullptr; }

    void timeChanged(const int by);

    int spaceLeft(const eResourceType type) const;
    int add(const eResourceType type, const int count);

    std::vector<eCartTask> cartTasks() const;

    void registerElement(const stdsptr<eSanctBuilding>& e);

    eSanctCost cost() const;
    const eSanctCost& stored() const { return mStored; }

    void useResources(const eSanctCost& r);
private:
    eSanctCost mStored{0, 0, 0};
    eSanctCost mUsed{0, 0, 0};

    stdsptr<eCartTransporter> mCart;

    std::vector<stdsptr<eSanctBuilding>> mElements;
};

#endif // ESANCTUARY_H
