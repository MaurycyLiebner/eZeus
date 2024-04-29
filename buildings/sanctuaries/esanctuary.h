#ifndef ESANCTUARY_H
#define ESANCTUARY_H

#include "../eemployingbuilding.h"

#include "esanctuaryblueprint.h"
#include "esanctbuilding.h"
#include "characters/gods/egod.h"
#include "engine/edate.h"

class eBuildingTextures;

enum class eHelpDenialReason {
    tooSoon,
    noTarget,
    error
};

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

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    std::vector<eTile*> warriorTiles() const;
    void addWarriorTile(eTile* const t);

    bool askForHelp(eHelpDenialReason& reason);

    eGod* god() const { return mGod; }

    void registerElement(const stdsptr<eSanctBuilding>& e);

    int progress() const; // 0-100
    bool finished() const;

    eSanctCost cost() const;
    const eSanctCost& stored() const { return mStored; }

    void useResources(const eSanctCost& r);

    int altitude() const { return mAltitude; }
    void setAltitude(const int a) { mAltitude = a; }

    eGodType godType() const;

    eGod* spawnGod();
    void spawnPatrolingGod();

    void buildingProgressed();
private:
    eSanctCost mStored{0, 0, 0};
    eSanctCost mUsed{0, 0, 0};
    int mAltitude = 0;

    stdptr<eCartTransporter> mCart;

    std::vector<stdsptr<eSanctBuilding>> mElements;

    stdptr<eGod> mGod;
    int mSpawnWait = 0;

    int mHelpTimer = 100000;

    std::vector<eTile*> mWarriorTiles;
};

#endif // ESANCTUARY_H
