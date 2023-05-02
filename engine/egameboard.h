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

#include "characters/gods/egod.h"
#include "characters/monsters/emonster.h"
#include "buildings/sanctuaries/esanctuary.h"

class eGameEvent;

class eSpawner;
class eCharacter;
class eBuilding;
class eTradePost;
class eStorageBuilding;
class eSoldierBanner;
class ePalace;
class eLandInvasionPoint;
class eReceiveRequestEvent;

class eThreadPool;

class eSoldier;
class eInvasionHandler;
enum class eMessageEventType;

struct eMessageType;
struct eEventData;
enum class eEvent;

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

    void registerCharacterAction(eCharacterAction* const ca);
    bool unregisterCharacterAction(eCharacterAction* const ca);

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

    void registerMonster(eMonster* const m);
    void unregisterMonster(eMonster* const m);

    void registerBanner(eBanner* const b);
    void unregisterBanner(eBanner* const b);

    const std::vector<eMonster*>& monsters() const { return mMonsters; }

    void updateResources();
    using eResources = std::vector<std::pair<eResourceType, int>>;
    const eResources& resources() const { return mResources; }

    ePalace* palace() const { return mPalace; }
    bool hasPalace() const { return mPalace; }

    int eliteHouses() const;

    const std::vector<eSanctuary*>& sanctuaries() const
    { return mSanctuaries; }
    eSanctuary* sanctuary(const eGodType god) const;

    const std::vector<stdsptr<eSoldierBanner>>& banners() const
    { return mSoldierBanners; }
    int countBanners(const eBannerType bt) const;

    void incTime(const int by);
    int totalTime() const { return mTotalTime; }

    eThreadPool& threadPool() { return mThreadPool; }

    int population() const { return mPopData.population(); }

    ePopulationData& populationData() { return mPopData; }
    eEmploymentData& employmentData() { return mEmplData; }
    eHeatMap& appealMap() { return mAppealMap; }

    void incDrachmas(const int d);
    int drachmas() const { return mDrachmas; }
    eDifficulty difficulty() const { return mDifficulty; }
    const eDate& date() const { return mDate; }
    void setDate(const eDate& d);

    double appeal(const int tx, const int ty) const;

    double taxRateF() const;
    eTaxRate taxRate() const { return mTaxRate; }
    eWageRate wageRate() const { return mWageRate; }

    void setTaxRate(const eTaxRate tr);
    void setWageRate(const eWageRate wr);

    void addRubbish(const stdsptr<eObject>& o);
    void emptyRubbish();

    using eEventHandler = std::function<void(eEvent, eEventData&)>;
    void setEventHandler(const eEventHandler& eh);
    void event(const eEvent e, eEventData& ed);

    using eVisibilityChecker = std::function<bool(eTile*)>;
    void setVisibilityChecker(const eVisibilityChecker& vc);

    using eTipShower = std::function<void(const std::string&)>;
    void setTipShower(const eTipShower& ts);
    void showTip(const std::string& tip);

    using eAction = std::function<void()>;
    bool ifVisible(eTile* const tile, const eAction& func) const;

    using eMessageShower = std::function<void(
                eEventData&, const eMessageType&)>;
    void setMessageShower(const eMessageShower& msg);

    void showMessage(eEventData& ed, const eMessageType& msg);

    const std::string& playerName() const
    { return mPlayerName; }

    using eTileAction = std::function<void(eTile* const)>;
    void iterateOverAllTiles(const eTileAction& a);

    void scheduleAppealMapUpdate();
    void updateAppealMapIfNeeded();

    eWorldBoard& getWorldBoard() { return mWorldBoard; }

    void clearBannerSelection();
    void deselectBanner(eSoldierBanner* const c);
    void selectBanner(eSoldierBanner* const c);
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
    int allCultureCoverage() const { return mAllDiscCoverage; }
    int taxesCoverage() const { return mTaxesCoverage; }
    int unrest() const { return mUnrest; }
    int popularity() const { return mPopularity; }
    int health() const { return mHealth; }

    int wonGames() const { return mWonGames; }

    int horses() const;

    void planAction(ePlannedAction* const a);

    void restockMarbleTiles();
    void updateMarbleTiles();

    void setFriendlyGods(const std::vector<eGodType>& gods);
    void setHostileGods(const std::vector<eGodType>& gods);
    void setHostileMonsters(const std::vector<eMonsterType>& monsters);

    const std::vector<eGodType>& friendlyGods() { return mFriendlyGods; }
    const std::vector<eGodType>& hostileGods() { return mHostileGods; }
    const std::vector<eMonsterType>& hostileMonsters() { return mHostileMonsters; }

    using eGameEvents = std::vector<stdsptr<eGameEvent>>;
    const eGameEvents& gameEvents() const { return mGameEvents; }

    void addGameEvent(const stdsptr<eGameEvent>& e);

    void planInvasion(const eDate& date,
                      const int infantry,
                      const int cavalry,
                      const int archers);

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;

    eBuilding* buildingWithIOID(const int id) const;
    eCharacter* characterWithIOID(const int id) const;
    eCharacterAction* characterActionWithIOID(const int id) const;
    eBanner* bannerWithIOID(const int id) const;

    eTile* landInvasionTile(const int id);
    void addLandInvasionPoint(eLandInvasionPoint* const p);
    void removeLandInvasionPoint(const int id);

    void addInvasion(eInvasionHandler* const i);
    void removeInvasion(eInvasionHandler* const i);

    int addResource(const eResourceType type,
                    const int count);
    int spaceForResource(const eResourceType type);
    int resourceCount(const eResourceType type) const;
    int takeResource(const eResourceType type,
                     const int count);
    void request(const stdsptr<eWorldCity>& c,
                 const eResourceType type);
    void planGiftFrom(const stdsptr<eWorldCity>& c,
                      const eResourceType type,
                      const int count);
    void giftFrom(const stdsptr<eWorldCity>& c,
                  const eResourceType type,
                  const int count,
                  const bool postpone);
    void tributeFrom(const stdsptr<eWorldCity>& c,
                    const bool postpone);
    void giftTo(const stdsptr<eWorldCity>& c,
              const eResourceType type,
              const int count);
    void giftToReceived(const stdsptr<eWorldCity>& c,
                      const eResourceType type,
                      const int count);

    void waitUntilFinished();
private:
    void updateNeighbours();

    void updateMaxSoldiers();
    void addSoldier(const eCharacterType st);
    void removeSoldier(const eCharacterType st);
    void distributeSoldiers();

    void registerSoldierBanner(const stdsptr<eSoldierBanner>& b);
    bool unregisterSoldierBanner(const stdsptr<eSoldierBanner>& b);

    void updateCoverage();

    void handleGamesBegin(const eGames game);
    void handleGamesEnd(const eGames game);

    eWorldBoard mWorldBoard;

    eEventHandler mEventHandler;
    eVisibilityChecker mVisibilityChecker;
    eTipShower mTipShower;

    std::string mPlayerName = "Ailuropoda";

    int mDrachmas = 2500;
    eDifficulty mDifficulty{eDifficulty::beginner};
    eWageRate mWageRate{eWageRate::normal};
    eTaxRate mTaxRate{eTaxRate::normal};

    int mTotalTime = 0;
    int mTime = 0;
    int mEmploymentCheckTime = 0;
    int mLastEmploymentState = 0;
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

    std::vector<eSanctuary*> mSanctuaries;
    std::vector<eStorageBuilding*> mStorBuildings;
    std::vector<eCharacter*> mCharacters;
    std::vector<eCharacterAction*> mCharacterActions;
    std::vector<eSoldier*> mSoldiers;
    std::vector<eBuilding*> mTimedBuildings;
    std::vector<eBuilding*> mAllBuildings;
    std::vector<eTradePost*> mTradePosts;
    std::vector<eSpawner*> mSpawners;
    std::vector<eMissile*> mMissiles;
    std::vector<eMonster*> mMonsters;
    std::vector<eBanner*> mBanners;

    std::vector<stdsptr<eSoldierBanner>> mSoldierBanners;

    std::vector<eSoldierBanner*> mSelectedBanners;

    std::vector<eInvasionHandler*> mInvasions;

    std::map<int, eLandInvasionPoint*> mLandInvasion;

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
    int mTaxesCoverage = 0;
    int mUnrest = 0;
    int mPopularity = 0;
    int mHealth = 0;

    int mWonGames = 0;

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

    std::vector<stdsptr<eGameEvent>> mGameEvents;

    std::vector<eMonsterType> mHostileMonsters;
    std::vector<eGodType> mFriendlyGods;
    std::vector<eGodType> mHostileGods;
};

#endif // EGAMEBOARD_H
