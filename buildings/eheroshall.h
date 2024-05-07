#ifndef EHEROSHALL_H
#define EHEROSHALL_H

#include "buildings/ebuilding.h"

#include "characters/heroes/ehero.h"

enum class eHeroRequirementType {
    // achilles
    armor, // 32
    hoplite, // 3
    sanctuary, // 1
    noUnrest,
    wine, // 16

    // hercules
    hallCultureAccess,
    panHellenicGameWin,
    cityGymnasiumAccess,
    people, // 1500
    // wine, // 32

    // jason
    // triremes, // 3
    horsemen, // 2
    horses, // 8
    food, // 64
    // wine, 16

    // odysseus
    popularity,
    health,
    eliteHouses, // 8
    oil, // 32
    // wine, 16

    // perseus
    // sanctuary, // 2
    drachmas, // 3000
    fleece, // 16
    sculpture, // 6

    // theseus
    nearPalace,
    appeal,
    walls,
    marble, // 32
    // wine, // 16

    // atalanta
    sanctuaryArtemis,
    stadium,
    meat, // 32
    wood, // 32
    soldiers, // 8

    // bellerophon
    // horses, // 15
    taxes,
    // drachmas, // 10000
    bronze, // 24
    // wine, // 24
};

struct eHeroRequirement {
    eHeroRequirementType fType;
    int fRequiredCount;
    int fStatusCount = 0;
};

enum class eHeroSummoningStage {
    none,
    summoned,
    arrived
};

class eHerosHall : public eBuilding {
public:
    eHerosHall(const eHeroType type, eGameBoard& board);
    ~eHerosHall();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    int provide(const eProvide p, const int n) override;

    static eBuildingType sHeroTypeToHallType(const eHeroType type);
    static eHeroType sHallTypeToHeroType(const eBuildingType type,
                                         bool* const valid = nullptr);

    static std::string sHeroRequirementText(const eHeroRequirement& hr);
    static std::string sHeroRequirementStatusText(const eHeroRequirement& hr);

    static std::string sTitle(const eHeroType ht);

    const std::vector<eHeroRequirement>& requirements() const
    { return mRequirements; }

    eHeroType heroType() const { return mType; }

    void summon();
    void arrive();
    void spawnHero();

    eHeroSummoningStage stage() const { return mStage; }

    bool heroOnQuest() const { return mHeroOnQuest; }
    void setHeroOnQuest(const bool b);
    void sendHeroOnQuest();

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void addRequirement(const eHeroRequirement& hr);
    void updateRequirementsStatus();
    void updateRequirementStatus(eHeroRequirement& hr);

    eHeroType mType;

    int mRequirementsUpdate = 0;
    std::vector<eHeroRequirement> mRequirements;

    int mUpdateCulture = 0;

    int mPhilosophers = 0;
    int mActors = 0;
    int mAthletes = 0;

    eHeroSummoningStage mStage = eHeroSummoningStage::none;
    int mArrivalCountdown = 15000;

    stdptr<eHero> mHero;
    int mSpawnWait = 0;
    bool mHeroOnQuest = false;
};

#endif // EHEROSHALL_H
