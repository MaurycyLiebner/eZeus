#ifndef EGAMEBOARD_H
#define EGAMEBOARD_H

#include <vector>

#include "etile.h"

#include "boardData/epopulationdata.h"
#include "boardData/eemploymentdata.h"
#include "boardData/eheatmap.h"

#include "edifficulty.h"
#include "edate.h"

#include "eresourcetype.h"

#include "pointers/eobject.h"

#include "ethreadpool.h"
#include "eplannedaction.h"

#include "eworldboard.h"
#include "widgets/ebuildingmode.h"

#include "fileIO/estreams.h"

#include "characters/gods/egod.h"
#include "characters/monsters/emonster.h"

class eGameEventCycle;

class eSpawner;
class eCharacter;
class eBuilding;
class eTradePost;
class eStorageBuilding;
class eSoldierBanner;
class ePalace;

class eThreadPool;

class eSoldier;

struct eMessageType;

enum class eEvent {
    fire,
    collapse,

    aphroditeVisit,
    aphroditeInvasion,

    apolloVisit,
    apolloInvasion,

    aresVisit,
    aresInvasion,

    artemisVisit,
    artemisInvasion,

    athenaVisit,
    athenaInvasion,

    atlasVisit,
    atlasInvasion,

    demeterVisit,
    demeterInvasion,

    dionysusVisit,
    dionysusInvasion,

    hadesVisit,
    hadesInvasion,

    hephaestusVisit,
    hephaestusInvasion,

    heraVisit,
    heraInvasion,

    hermesVisit,
    hermesInvasion,

    poseidonVisit,
    poseidonInvasion,

    zeusVisit,
    zeusInvasion,

    calydonianBoarInvasion,
    cerberusInvasion,
    chimeraInvasion,
    cyclopsInvasion,
    dragonInvasion,
    echidnaInvasion,
    harpiesInvasion,
    hectorInvasion,
    hydraInvasion,
    krakenInvasion,
    maenadsInvasion,
    medusaInvasion,
    minotaurInvasion,
    scyllaInvasion,
    sphinxInvasion,
    talosInvasion
};

enum class eGames {
    isthmian,
    nemean,
    pythian,
    olympian
};

class eGameBoard {
public:
    eGameBoard();
    ~eGameBoard();

    void initialize(const int w, const int h);
    void clear();

    eTile* tile(const int x, const int y) const;
    eTile* dtile(const int x, const int y) const;

    int width() const { return mWidth; }
    int height() const { return mHeight; }

    void registerCharacter(eCharacter* const c);
    bool unregisterCharacter(eCharacter* const c);

    void registerSoldier(eSoldier* const c);
    bool unregisterSoldier(eSoldier* const c);

    void registerBuilding(eBuilding* const b);
    bool unregisterBuilding(eBuilding* const b);

    void registerTradePost(eTradePost* const b);
    bool unregisterTradePost(eTradePost* const b);
    bool hasTradePost(const eWorldCity& city);

    void registerSpawner(eSpawner* const s);
    bool unregisterSpawner(eSpawner* const s);

    void registerStadium(eBuilding* const s);
    void unregisterStadium();

    void registerStorBuilding(eStorageBuilding* const b);
    bool unregisterStorBuilding(eStorageBuilding* const b);

    void registerMissile(eMissile* const m);
    bool unregisterMissile(eMissile* const m);

    bool hasStadium() const { return mStadium; }

    void registerPalace(ePalace* const p);
    void unregisterPalace();

    void updateResources();
    using eResources = std::vector<std::pair<eResourceType, int>>;
    const eResources& resources() const { return mResources; }

    bool hasPalace() const { return mPalace; }

    void incTime(const int by);

    eThreadPool& threadPool() { return mThreadPool; }

    ePopulationData& populationData() { return mPopData; }
    eEmploymentData& employmentData() { return mEmplData; }
    eHeatMap& appealMap() { return mAppealMap; }

    void incDrachmas(const int d);
    int drachmas() const { return mDrachmas; }
    eDifficulty difficulty() const { return mDifficulty; }
    const eDate& date() const { return mDate; }

    double appeal(const int tx, const int ty) const;

    double taxRateF() const;
    eTaxRate taxRate() const { return mTaxRate; }
    eWageRate wageRate() const { return mWageRate; }

    void setTaxRate(const eTaxRate tr);
    void setWageRate(const eWageRate wr);

    void addRubbish(const stdsptr<eObject>& o);
    void emptyRubbish();

    using eEventHandler = std::function<void(eEvent, eTile*)>;
    void setEventHandler(const eEventHandler& eh);
    void event(const eEvent e, eTile* const tile);

    using eVisibilityChecker = std::function<bool(eTile*)>;
    void setVisibilityChecker(const eVisibilityChecker& vc);

    using eTipShower = std::function<void(const std::string&)>;
    void setTipShower(const eTipShower& ts);
    void showTip(const std::string& tip);

    using eAction = std::function<void()>;
    bool ifVisible(eTile* const tile, const eAction& func) const;

    using eMessageShower = std::function<void(eTile* const, const eMessageType&)>;
    void setMessageShower(const eMessageShower& msg);

    void showMessage(eTile* const t, const eMessageType& msg);

    const std::string& playerName() const
    { return mPlayerName; }

    void requestTileRenderingOrderUpdate();
    void updateTileRenderingOrderIfNeeded();
    using eTileAction = std::function<void(eTile* const)>;
    void iterateOverAllTiles(const eTileAction& a);

    void scheduleAppealMapUpdate();
    void updateAppealMapIfNeeded();

    eWorldBoard& getWorldBoard() { return mWorldBoard; }

    void clearSoldierSelection();
    void deselectSoldier(eSoldierBanner* const c);
    void selectSoldier(eSoldierBanner* const c);
    const std::vector<eSoldierBanner*>& selectedSoldiers() const
    { return mSelectedBanners; }

    void bannersGoHome();
    void bannersBackFromHome();

    void setRegisterBuildingsEnabled(const bool e);

    void setButtonsVisUpdater(const eAction& u);

    void addSupportedBuilding(const eBuildingMode t);
    void removeSupportedBuilding(const eBuildingMode t);
    bool supportsBuilding(const eBuildingMode t) const;

    bool supportsResource(const eResourceType rt) const;
    eResourceType supportedResources() const;

    using eBuildingValidator = std::function<bool(eBuilding*)>;
    eBuilding* randomBuilding(const eBuildingValidator& v) const;

    int philosophyCoverage() const { return mPhilosophyCoverage; }
    int athleticsCoverage() const { return mAthleticsCoverage; }
    int dramaCoverage() const { return mDramaCoverage; }
    int allCoverage() const { return mAllDiscCoverage; }

    void planAction(ePlannedAction* const a);

    void restockMarbleTiles();
    void updateMarbleTiles();

    void setFriendlyGods(const std::vector<eGodType>& gods);
    void setHostileGods(const std::vector<eGodType>& gods);
    void setMonsters(const std::vector<eMonsterType>& monsters);

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;

    eBuilding* buildingWithIOID(const int id) const;
private:
    void updateNeighbours();
    void updateTileRenderingOrder();

    void updateMaxSoldiers();
    void addSoldier(const eCharacterType st);
    void removeSoldier(const eCharacterType st);
    void distributeSoldiers();

    void registerBanner(const stdsptr<eSoldierBanner>& b);
    bool unregisterBanner(const stdsptr<eSoldierBanner>& b);

    void addGameEvent(const stdsptr<eGameEventCycle>& e);

    void updateCoverage();

    void handleGamesBegin(const eGames game);
    void handleGamesEnd(const eGames game);

    eWorldBoard mWorldBoard;

    bool mTileRenderingOrderUpdateNeeded = true;

    eEventHandler mEventHandler;
    eVisibilityChecker mVisibilityChecker;
    eTipShower mTipShower;

    std::string mPlayerName = "Ailuropoda";

    int mDrachmas = 2500;
    eDifficulty mDifficulty{eDifficulty::beginner};
    eWageRate mWageRate{eWageRate::normal};
    eTaxRate mTaxRate{eTaxRate::normal};

    int mTime = 0;
    eDate mDate = eDate(1, eMonth::january, -1500);

    eThreadPool mThreadPool;

    int mWidth = 0;
    int mHeight = 0;
    std::vector<std::vector<eTile*>> mTiles;

    eResources mResources = {{eResourceType::urchin, 0},
                             {eResourceType::fish, 0},
                             {eResourceType::meat, 0},
                             {eResourceType::cheese, 0},
                             {eResourceType::carrots, 0},
                             {eResourceType::onions, 0},
                             {eResourceType::wheat, 0},
                             {eResourceType::oranges, 0},

                             {eResourceType::grapes, 0},
                             {eResourceType::olives, 0},
                             {eResourceType::wine, 0},
                             {eResourceType::oliveOil, 0},
                             {eResourceType::fleece, 0},

                             {eResourceType::wood, 0},
                             {eResourceType::bronze, 0},
                             {eResourceType::marble, 0},

                             {eResourceType::armor, 0},
                             {eResourceType::sculpture, 0}};

    std::vector<stdsptr<eObject>> mRubbish;

    bool mRegisterBuildingsEnabled = true;

    std::vector<eStorageBuilding*> mStorBuildings;
    std::vector<eCharacter*> mCharacters;
    std::vector<eSoldier*> mSoldiers;
    std::vector<eBuilding*> mTimedBuildings;
    std::vector<eBuilding*> mAllBuildings;
    std::vector<eTradePost*> mTradePosts;
    std::vector<eSpawner*> mSpawners;
    std::vector<eMissile*> mMissiles;

    std::vector<stdsptr<eSoldierBanner>> mBanners;

    std::vector<eSoldierBanner*> mSelectedBanners;

    std::vector<ePlannedAction*> mPlannedActions;

    std::vector<eTile*> mMarbleTiles;

    int mSoldiersUpdate = 10000;
    int mMaxRockThrowers = 0;
    int mMaxHoplites = 0;
    int mMaxHorsemen = 0;

    int mCoverageUpdate = 10000;
    int mAthleticsCoverage = 0;
    int mPhilosophyCoverage = 0;
    int mDramaCoverage = 0;
    int mAllDiscCoverage = 0;

    eBuilding* mStadium = nullptr;
    ePalace* mPalace = nullptr;

    ePopulationData mPopData;

    eEmploymentData mEmplData;

    bool mUpdateAppeal = false;
    eHeatMap mAppealMap;

    eAction mButtonVisUpdater;
    eMessageShower mMsgShower;

    std::vector<eBuildingMode> mSupportedBuildings;
    eResourceType mSupportedResources;

    std::vector<stdsptr<eGameEventCycle>> mGameEvents;

    std::vector<eMonsterType> mMonsters;
    std::vector<eGodType> mFriendlyGods;
    std::vector<eGodType> mHostileGods;
};

#endif // EGAMEBOARD_H
