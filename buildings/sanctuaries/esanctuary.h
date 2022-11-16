#ifndef ESANCTUARY_H
#define ESANCTUARY_H

#include "../eemployingbuilding.h"

#include "esanctuaryblueprint.h"
#include "esanctbuilding.h"

class eGod;
class eBuildingTextures;
enum class eGodType;

class eSanctuary : public eEmployingBuilding {
public:
    eSanctuary(eGameBoard& board,
               const eBuildingType type,
               const int sw, const int sh,
               const int maxEmployees);
    ~eSanctuary();

    void erase() override;

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const override
    { return nullptr; }

    void timeChanged(const int by) override;

    int spaceLeft(const eResourceType type) const override;
    int add(const eResourceType type, const int count) override;

    std::vector<eCartTask> cartTasks() const override;

    void registerElement(const stdsptr<eSanctBuilding>& e);

    int progress() const; // 0-100

    eSanctCost cost() const;
    const eSanctCost& stored() const { return mStored; }

    void useResources(const eSanctCost& r);

    int altitude() const { return mAltitude; }
    void setAltitude(const int a) { mAltitude = a; }

    eGodType godType() const;

    void spawnGod();

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    eSanctCost mStored{0, 0, 0};
    eSanctCost mUsed{0, 0, 0};
    int mAltitude = 0;

    stdptr<eCartTransporter> mCart;

    std::vector<stdsptr<eSanctBuilding>> mElements;

    stdptr<eGod> mGod;
    int mSpawnWait = 0;
};

#endif // ESANCTUARY_H
