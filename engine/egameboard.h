#ifndef EGAMEBOARD_H
#define EGAMEBOARD_H

#include <vector>
#include "elimits.h"
#include "etile.h"

#include "boardData/epopulationdata.h"
#include "boardData/ehusbandrydata.h"
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

#include "buildings/eavailablebuildings.h"

#include "characters/eenlistedforces.h"

#include "engine/egodquest.h"
#include "ecityrequest.h"
#include "gameEvents/egodquestevent.h"
#include "eepisodegoal.h"
#include "eemploymentdistributor.h"

class eGameEvent;

class eSpawner;
enum class eBannerTypeS;
class eCharacter;
class eBuilding;
class eTradePost;
class eStorageBuilding;
class eSoldierBanner;
class ePalace;
class eLandInvasionPoint;
class eReceiveRequestEvent;
class eInvasionEvent;
class eAgoraBase;
class eHerosHall;

class eThreadPool;

class eSoldier;
class eInvasionHandler;
class eMonsterPoint;
class ePlayerConquestEventBase;
class eArmyEventBase;
class eTroopsRequestEvent;
enum class eMessageEventType;

struct eMessageType;
struct eEventData;
enum class eEvent;
class ePlague;
class eSmallHouse;
class eMuseum;
class eStadium;
struct eEpisode;

using eAction = std::function<void()>;

enum class eGames {
    isthmian,
    nemean,
    pythian,
    olympian
};

struct eMilitaryAid {
    bool count() const {
        int c = 0;
        for(const auto& s : fSoldiers) {
            c += s->count();
        }
        return c;
    }

    bool allDead() const {
        return count() == 0;
    }

    void goBack() {
        for(const auto& s : fSoldiers) {
            s->goAbroad();
        }
        fSoldiers.clear();
    }

    void write(eWriteStream& dst) {
        dst.writeCity(fCity.get());
        dst << fSoldiers.size();
        for(const auto& s : fSoldiers) {
            dst << s->type();
            s->write(dst);
        }
    }

    void read(eReadStream& src, eGameBoard* const board) {
        src.readCity(board, [this](const stdsptr<eWorldCity>& c) {
            fCity = c;
        });
        int ns;
        src >> ns;
        for(int i = 0; i < ns; i++) {
            eBannerType type;
            src >> type;
            const auto b = e::make_shared<eSoldierBanner>(type, *board);
            b->read(src);
            fSoldiers.push_back(b);
        }
    }

    stdsptr<eWorldCity> fCity;
    std::vector<stdsptr<eSoldierBanner>> fSoldiers;
};

enum class eImmigrationLimitedBy {
    none,
    lackOfVacancies,
    lowWages,
    unemployment,
    lackOfFood,
    highTaxes,
    prolongedDebt,
    excessiveMilitaryService
};

class eGameBoard : public eStdSelfRef {
public:
    eGameBoard();
    ~eGameBoard();

    void initialize(const int w, const int h);
    void resize(const int w, const int h);
    void clear();

    void setWorldDirection(const eWorldDirection dir);

    eTile* rotateddtile(const int x, const int y) const;

    eWorldDirection direction() const { return mDirection; }

    int rotatedWidth() const;
    int rotatedHeight() const;

    eTile* tile(const int x, const int y) const;
    eTile* dtile(const int x, const int y) const;

    int width() const { return mWidth; }
    int height() const { return mHeight; }

    void registerCharacter(eCharacter* const c);
    bool unregisterCharacter(eCharacter* const c);
    const std::vector<eCharacter*>& characters() const
    { return mCharacters; }

    void registerCharacterAction(eCharacterAction* const ca);
    bool unregisterCharacterAction(eCharacterAction* const ca);

    void registerSoldier(eSoldier* const c);
    bool unregisterSoldier(eSoldier* const c);

    void registerBuilding(eBuilding* const b);
    bool unregisterBuilding(eBuilding* const b);

    bool unregisterCommonHouse(eSmallHouse* const ch);

    void registerEmplBuilding(eEmployingBuilding* const b);
    bool unregisterEmplBuilding(eEmployingBuilding* const b);

    void registerTradePost(eTradePost* const b);
    bool unregisterTradePost(eTradePost* const b);
    bool hasTradePost(const eWorldCity& city);

    void registerSpawner(eSpawner* const s);
    bool unregisterSpawner(eSpawner* const s);

    void registerStadium(eBuilding* const s);
    void unregisterStadium();

    void registerMuseum(eBuilding* const s);
    void unregisterMuseum();

    void registerStorBuilding(eStorageBuilding* const b);
    bool unregisterStorBuilding(eStorageBuilding* const b);

    void registerSanctuary(eSanctuary* const b);
    bool unregisterSanctuary(eSanctuary* const b);

    void registerHeroHall(eHerosHall* const b);
    bool unregisterHeroHall(eHerosHall* const b);

    void registerMissile(eMissile* const m);
    bool unregisterMissile(eMissile* const m);

    bool hasStadium() const { return mStadium; }
    bool hasMuseum() const { return mMuseum; }
    eStadium* stadium() const;
    eMuseum* museum() const;

    void registerPalace(ePalace* const p);
    void unregisterPalace();

    void registerMonster(eMonster* const m);
    void unregisterMonster(eMonster* const m);

    eBanner* banner(const eBannerTypeS type, const int id = 0) const;
    void registerBanner(eBanner* const b);
    void unregisterBanner(eBanner* const b);

    void registerAllSoldierBanner(eSoldierBanner* const b);
    void unregisterAllSoldierBanner(eSoldierBanner* const b);

    const std::vector<eMonster*>& monsters() const { return mMonsters; }

    std::vector<eAgoraBase*> agoras() const;

    void updateResources();
    using eResources = std::vector<std::pair<eResourceType, int>>;
    const eResources& resources() const { return mResources; }

    ePalace* palace() const { return mPalace; }
    bool hasPalace() const { return mPalace; }

    int eliteHouses() const;

    const std::vector<eSanctuary*>& sanctuaries() const
    { return mSanctuaries; }
    eSanctuary* sanctuary(const eGodType god) const;

    const std::vector<eHerosHall*>& heroHalls() const
    { return mHeroHalls; }
    eHerosHall* heroHall(const eHeroType hero) const;

    const std::vector<stdsptr<eSoldierBanner>>& banners() const
    { return mSoldierBanners; }
    int countBanners(const eBannerType bt) const;
    int countSoldiers(const eBannerType bt) const;

    void incTime(const int by);
    void incFrame();
    int frame() const { return mFrame; }
    void handleFinishedTasks();
    void scheduleDataUpdate();
    int totalTime() const { return mTotalTime; }

    eThreadPool& threadPool() { return mThreadPool; }

    int population() const { return mPopData.population(); }

    ePopulationData& populationData() { return mPopData; }
    eHusbandryData& husbandryData() { return mHusbData; }
    eEmploymentData& employmentData() { return mEmplData; }
    eHeatMap& appealMap() { return mAppealMap; }

    void payTaxes(const int d, const int people);
    void incDrachmas(const int d);
    int drachmas() const { return mDrachmas; }
    void setDifficulty(const eDifficulty d) { mDifficulty = d; }
    eDifficulty difficulty() const { return mDifficulty; }
    const eDate& date() const { return mDate; }
    void setDate(const eDate& d);

    double appeal(const int tx, const int ty) const;

    double taxRateF() const;
    eTaxRate taxRate() const { return mTaxRate; }
    eWageRate wageRate() const { return mWageRate; }

    void setTaxRate(const eTaxRate tr);
    void setWageRate(const eWageRate wr);

    int taxesPaidThisYear() const { return mTaxesPaidThisYear; }
    int taxesPaidLastYear() const { return mTaxesPaidLastYear; }
    int peoplePaidTaxesThisYear() const { return mPeoplePaidTaxesThisYear; }
    int peoplePaidTaxesLastYear() const { return mPeoplePaidTaxesLastYear; }

    void addRubbish(const stdsptr<eObject>& o);
    void emptyRubbish();

    using eEventHandler = std::function<void(eEvent, eEventData&)>;
    void setEventHandler(const eEventHandler& eh);
    void event(const eEvent e, eEventData& ed);
    void setEpisodeFinishedHandler(const eAction& a);
    void setAutosaver(const eAction& a);

    void setRequestUpdateHandler(const eAction& ru);

    using eVisibilityChecker = std::function<bool(eTile*)>;
    void setVisibilityChecker(const eVisibilityChecker& vc);

    using eTipShower = std::function<void(const std::string&)>;
    void setTipShower(const eTipShower& ts);
    void showTip(const std::string& tip) const;

    using eEnlistAction = std::function<void(const eEnlistedForces&, eResourceType)>;
    using eEnlistRequest = std::function<void(const eEnlistedForces& enlistable,
                                              const std::vector<bool>& heroesAbroad,
                                              const eEnlistAction& action,
                                              const std::vector<eResourceType>& plunderResources)>;
    void setEnlistForcesRequest(const eEnlistRequest& req);
    void requestForces(const eEnlistAction& action,
                       const std::vector<eResourceType>& plunderResources = {},
                       const std::vector<stdsptr<eWorldCity>>& exclude = {});

    using eAction = std::function<void()>;
    bool ifVisible(eTile* const tile, const eAction& func) const;

    using eMessageShower = std::function<void(
                eEventData&, const eMessageType&)>;
    void setMessageShower(const eMessageShower& msg);

    void showMessage(eEventData& ed, const eMessageType& msg);

    using eTileAction = std::function<void(eTile* const)>;
    void iterateOverAllTiles(const eTileAction& a);

    void scheduleAppealMapUpdate();
    void updateAppealMapIfNeeded();

    eWorldBoard* getWorldBoard() const { return mWorldBoard; }

    void enlistForces(const eEnlistedForces& forces);
    void clearBannerSelection();
    void deselectBanner(eSoldierBanner* const c);
    void selectBanner(eSoldierBanner* const c);
    const std::vector<eSoldierBanner*>& selectedSoldiers() const
    { return mSelectedBanners; }

    void bannersGoHome();
    void bannersBackFromHome();

    void setRegisterBuildingsEnabled(const bool e);

    void setButtonsVisUpdater(const eAction& u);

    bool supportsBuilding(const eBuildingMode mode) const;
    bool availableBuilding(const eBuildingType type,
                           const int id = -1) const;
    void built(const eBuildingType type,
               const int id = -1);
    void destroyed(const eBuildingType type,
                   const int id = -1);
    void allow(const eBuildingType type,
               const int id = -1);
    void disallow(const eBuildingType type,
                  const int id = -1);

    bool supportsResource(const eResourceType rt) const;
    eResourceType supportedResources() const;

    using eBuildingValidator = std::function<bool(eBuilding*)>;
    std::vector<eBuilding*> buildings(const eBuildingValidator& v) const;
    std::vector<eBuilding*> buildings(const eBuildingType type) const;
    int countBuildings(const eBuildingValidator& v) const;
    int countBuildings(const eBuildingType t) const;
    int countAllowed(const eBuildingType t) const;
    eBuilding* randomBuilding(const eBuildingValidator& v) const;
    const std::vector<eBuilding*>& commemorativeBuildings() const
    { return mCommemorativeBuildings; }

    int philosophyResearchCoverage() const { return mPhilosophyCoverage; }
    int athleticsLearningCoverage() const { return mAthleticsCoverage; }
    int dramaAstronomyCoverage() const { return mDramaCoverage; }
    int allCultureScienceCoverage() const { return mAllDiscCoverage; }
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

    void allowHero(const eHeroType heroType, const std::string& reason = "");

    using eGameEvents = std::vector<stdsptr<eGameEvent>>;
    const eGameEvents& gameEvents() const { return mGameEvents; }

    using eGoals = std::vector<stdsptr<eEpisodeGoal>>;
    const eGoals& goals() const { return mGoals; }

    void addRootGameEvent(const stdsptr<eGameEvent>& e);
    void removeRootGameEvent(const stdsptr<eGameEvent>& e);

    void addGameEvent(eGameEvent* const e);
    void removeGameEvent(eGameEvent* const e);

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
    eSoldierBanner* soldierBannerWithIOID(const int id) const;
    eGameEvent* eventWithIOID(const int id) const;

    eTile* monsterTile(const int id) const;
    eTile* landInvasionTile(const int id) const;
    eTile* disasterTile(const int id) const;

    using eIV = std::vector<eInvasionHandler*>;
    const eIV& invasionHandlers() const;
    void addInvasionHandler(eInvasionHandler* const i);
    void removeInvasionHandler(eInvasionHandler* const i);

    int addResource(const eResourceType type,
                    const int count);
    int spaceForResource(const eResourceType type) const;
    int maxSanctuarySpaceForResource(eSanctuary** b) const;
    int maxSingleSpaceForResource(const eResourceType type,
                                  eStorageBuilding** b) const;
    int resourceCount(const eResourceType type) const;
    int takeResource(const eResourceType type,
                     const int count);
    void request(const stdsptr<eWorldCity>& c,
                 const eResourceType type);
    void requestAid(const stdsptr<eWorldCity>& c);
    void planGiftFrom(const stdsptr<eWorldCity>& c,
                      const eResourceType type,
                      const int count,
                      const int delay);
    void tributeFrom(const stdsptr<eWorldCity>& c,
                    const bool postpone);
    void giftTo(const stdsptr<eWorldCity>& c,
              const eResourceType type,
              const int count);
    void giftToReceived(const stdsptr<eWorldCity>& c,
                      const eResourceType type,
                      const int count);

    void waitUntilFinished();

    void registerSoldierBanner(const stdsptr<eSoldierBanner>& b);
    bool unregisterSoldierBanner(const stdsptr<eSoldierBanner>& b);

    void killCommonFolks(int toKill);
    void walkerKilled();
    void rockThrowerKilled();
    void hopliteKilled();
    void horsemanKilled();

    eEnlistedForces getEnlistableForces() const;

    using eQuests = std::vector<eGodQuestEvent*>;
    const eQuests& godQuests() const { return mGodQuests; }
    void addGodQuest(eGodQuestEvent* const q);
    void removeGodQuest(eGodQuestEvent* const q);

    using eRequests = std::vector<eReceiveRequestEvent*>;
    const eRequests& cityRequests() const { return mCityRequests; }
    void addCityRequest(eReceiveRequestEvent* const q);
    void removeCityRequest(eReceiveRequestEvent* const q);

    using eTroopsRequests = std::vector<eTroopsRequestEvent*>;
    const eTroopsRequests& cityTroopsRequests() const { return mCityTroopsRequests; }
    void addCityTroopsRequest(eTroopsRequestEvent* const q);
    void removeCityTroopsRequest(eTroopsRequestEvent* const q);

    using eConquests = std::vector<ePlayerConquestEventBase*>;
    const eConquests& conquests() const { return mConquests; }
    void addConquest(ePlayerConquestEventBase* const q);
    void removeConquest(ePlayerConquestEventBase* const q);

    using eInvasions = std::vector<eInvasionEvent*>;
    const eInvasions& invasions() const { return mInvasions; }
    eInvasionEvent* invasionToDefend() const;
    void addInvasion(eInvasionEvent* const i);
    void removeInvasion(eInvasionEvent* const i);

    using eArmyEvents = std::vector<eArmyEventBase*>;
    const eArmyEvents& armyEvents() const { return mArmyEvents; }
    void addArmyEvent(eArmyEventBase* const q);
    void removeArmyEvent(eArmyEventBase* const q);

    using eChars = std::vector<eCharacter*>;
    const eChars& attackingGods() const { return mAttackingGods; }
    void registerAttackingGod(eCharacter* const c);

    void startPlague(eSmallHouse* const h);
    stdsptr<ePlague> plagueForHouse(eSmallHouse* const h);
    void healPlague(const stdsptr<ePlague>& p);
    void healHouse(eSmallHouse* const h);
    using ePlagues = std::vector<stdsptr<ePlague>>;
    const ePlagues& plagues() const { return mPlagues; }
    stdsptr<ePlague> nearestPlague(const int tx, const int ty,
                                   int& dist) const;

    void updateMusic();

    eTile* entryPoint() const;
    eTile* exitPoint() const;

    bool editorMode() const { return mEditorMode; }
    void setEditorMode(const bool m) { mEditorMode = m; }
    bool poseidonMode() const { return mPoseidonMode; }
    void setPoseidonMode(const bool p);

    void scheduleTerrainUpdate() { mUpdateTerrain = true; }
    bool terrainUpdateScheduled() const { return mUpdateTerrain; }
    void afterTerrainUpdated() { mUpdateTerrain = false; }

    void setWorldBoard(eWorldBoard* const wb);

    const std::vector<eGodQuest>& fulfilledQuests() const
    { return mFulfilledQuests; }
    void addFulfilledQuest(const eGodQuest q);
    const std::vector<eMonsterType>& slayedMonsters() const
    { return mSlayedMonsters; }
    void addSlayedMonster(const eMonsterType m);

    using eWC = stdsptr<eWorldCity>;
    void startEpisode(eEpisode* const e,
                      const eWC& lastPlayedColony);

    bool checkGoalsFulfilled() const;

    bool manTowers() const { return mManTowers; }
    void setManTowers(const bool m);

    void musterAllSoldiers();
    void sendAllSoldiersHome();

    eEmploymentDistributor& employmentDistributor()
    { return mEmplDistributor; }

    void addShutDown(const eResourceType type);
    void removeShutDown(const eResourceType type);
    bool isShutDown(const eResourceType type) const;
    bool isShutDown(const eBuildingType type) const;
    int industryJobVacancies(const eResourceType type) const;
    void distributeEmployees(const eSector s);
    void distributeEmployees();
    void scheduleDistributeEmployees();

    void incPopulation(const int by);

    void topElevationExtremas(int& min, int& max) const;
    void rightElevationExtremas(int& min, int& max) const;
    void bottomElevationExtremas(int& min, int& max) const;
    void leftElevationExtremas(int& min, int& max) const;

    void minMaxAltitude(int& min, int& max) const;

    bool landTradeShutdown() const { return mShutdownLandTrade; }
    void setLandTradeShutdown(const bool s) { mShutdownLandTrade = s; }

    bool seaTradeShutdown() const { return mShutdownSeaTrade; }
    void setSeaTradeShutdown(const bool s) { mShutdownSeaTrade = s; }

    eMilitaryAid* militaryAid(const stdsptr<eWorldCity>& c) const;
    void removeMilitaryAid(const stdsptr<eWorldCity>& c);
    void addMilitaryAid(const stdsptr<eMilitaryAid>& a);

    void setEpisodeLost() const;
    bool episodeLost() const { return mEpisodeLost; }
    int tradingPartners() const;

    void earthquake(eTile* const startTile, const int size);
    bool duringEarthquake() const;

    void defeatedBy(const stdsptr<eWorldCity>& c);

    eImmigrationLimitedBy immigrationLimit() const
    { return mImmigrationLimit; }

    void updateMaxSoldiers();
    void distributeSoldiers();
    void consolidateSoldiers();

    bool wasHeroSummoned(const eHeroType hero) const;
    void heroSummoned(const eHeroType hero);
private:
    void updateNeighbours();

    void addSoldier(const eCharacterType st);
    void removeSoldier(const eCharacterType st,
                       const bool skipNotHome = true);

    void updateCoverage();

    void handleGamesBegin(const eGames game);
    void handleGamesEnd(const eGames game);

    void progressEarthquakes();

    bool mEditorMode = false;
    bool mPoseidonMode = true;
    mutable bool mEpisodeLost = false;
    eWorldBoard* mWorldBoard = nullptr;
    eWorldDirection mDirection{eWorldDirection::N};

    bool mUpdateTerrain = true;

    eEventHandler mEventHandler;
    eAction mRequestUpdateHandler;
    eVisibilityChecker mVisibilityChecker;
    eTipShower mTipShower;
    eEnlistRequest mEnlistRequester;
    eAction mEpisodeFinishedHandler;
    eAction mAutosaver;

    int mDrachmas = 2500;
    eDate mInDebtSince;
    eDifficulty mDifficulty{eDifficulty::beginner};
    eWageRate mWageRate{eWageRate::normal};
    eTaxRate mTaxRate{eTaxRate::normal};

    using eILB = eImmigrationLimitedBy;
    eILB mImmigrationLimit{eILB::lackOfVacancies};
    bool mNoFood = false;
    eDate mNoFoodSince;

    int mTaxesPaidLastYear = 0;
    int mTaxesPaidThisYear = 0;

    int mPeoplePaidTaxesLastYear = 0;
    int mPeoplePaidTaxesThisYear = 0;

    int mFrame = 0;
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

    std::vector<eGodQuestEvent*> mGodQuests;
    std::vector<ePlayerConquestEventBase*> mConquests;
    std::vector<eArmyEventBase*> mArmyEvents;
    std::vector<eReceiveRequestEvent*> mCityRequests;
    std::vector<eInvasionEvent*> mInvasions;
    std::vector<eTroopsRequestEvent*> mCityTroopsRequests;

    std::vector<eSanctuary*> mSanctuaries;
    std::vector<eHerosHall*> mHeroHalls;
    std::vector<eStorageBuilding*> mStorBuildings;
    std::vector<eCharacter*> mCharacters;
    std::vector<eCharacterAction*> mCharacterActions;
    std::vector<eSoldier*> mSoldiers;
    std::vector<eBuilding*> mTimedBuildings;
    std::vector<eEmployingBuilding*> mEmployingBuildings;
    std::vector<eBuilding*> mAllBuildings;
    std::vector<eBuilding*> mCommemorativeBuildings;
    std::vector<eTradePost*> mTradePosts;
    std::vector<eSpawner*> mSpawners;
    std::vector<eMissile*> mMissiles;
    std::vector<eMonster*> mMonsters;
    std::vector<eBanner*> mBanners;

    std::vector<eSoldierBanner*> mAllSoldierBanners;
    std::vector<stdsptr<eSoldierBanner>> mSoldierBanners;
    std::vector<stdsptr<eSoldierBanner>> mPalaceSoldierBanners;

    std::vector<eSoldierBanner*> mSelectedBanners;

    std::vector<eInvasionHandler*> mInvasionHandlers;

    std::vector<ePlannedAction*> mPlannedActions;

    struct eMarbleTiles {
        bool contains(eTile* const tile) const;
        void add(eTile* const tile);
        void addWithNeighbours(eTile* const tile);
        void restock() const;

        std::vector<eTile*> fTiles;
    };

    std::vector<eMarbleTiles> mMarbleTiles;

    std::vector<stdsptr<eMilitaryAid>> mMilitaryAid;

    bool mManTowers = true;

    bool mShutdownLandTrade = false;
    bool mShutdownSeaTrade = false;

    int mSoldiersUpdate = 10000;
    int mMaxRabble = 0;
    int mMaxHoplites = 0;
    int mMaxHorsemen = 0;

    int mCoverageUpdate = 10000;
    int mAthleticsCoverage = 0;
    int mPhilosophyCoverage = 0;
    int mDramaCoverage = 0;
    int mAllDiscCoverage = 0;
    int mTaxesCoverage = 0;
    int mUnrest = 0; // percent
    int mPopularity = 0;
    int mHealth = 0;

    int mWonGames = 0;

    eBuilding* mStadium = nullptr;
    eBuilding* mMuseum = nullptr;
    ePalace* mPalace = nullptr;

    ePopulationData mPopData;
    eHusbandryData mHusbData;
    eEmploymentData mEmplData;

    bool mUpdateAppeal = false;
    eHeatMap mAppealMap;

    eAction mButtonVisUpdater;
    eMessageShower mMsgShower;

    eAvailableBuildings mAvailableBuildings;
    eResourceType mSupportedResources;

    std::vector<eGameEvent*> mAllGameEvents;
    std::vector<stdsptr<eGameEvent>> mGameEvents;
    int mGoalsCheckTime = 0;
    std::vector<stdsptr<eEpisodeGoal>> mGoals;

    std::vector<eMonsterType> mHostileMonsters;
    std::vector<eGodType> mFriendlyGods;
    std::vector<eGodType> mHostileGods;
    std::vector<eHeroType> mSummonedHeroes;

    std::vector<eCharacter*> mAttackingGods;

    std::vector<stdsptr<ePlague>> mPlagues;

    std::vector<eGodQuest> mFulfilledQuests;
    std::vector<eMonsterType> mSlayedMonsters;

    eEmploymentDistributor mEmplDistributor;
    std::vector<eResourceType> mShutDown;
    std::map<eSector, std::vector<eEmployingBuilding*>> mSectorBuildings;
    bool mEmploymentUpdateScheduled = true;
    int mEmploymentUpdateWait = __INT_MAX__/10;

    struct eEarthquake {
        eTile* fStartTile = nullptr;
        std::vector<eTile*> fTiles;
        int fLastDim = 0;

        void read(eReadStream& src, eGameBoard& board) {
            fStartTile = src.readTile(board);
            int nt;
            src >> nt;
            for(int i = 0; i < nt; i++) {
                const auto t = src.readTile(board);
                fTiles.push_back(t);
            }
            src >> fLastDim;
        }

        void write(eWriteStream& dst) {
            dst.writeTile(fStartTile);
            dst << fTiles.size();
            for(const auto t : fTiles) {
                dst.writeTile(t);
            }
            dst << fLastDim;
        }
    };

    int mProgressEarthquakes = 0;
    std::vector<stdsptr<eEarthquake>> mEarthquakes;

    std::vector<stdsptr<eWorldCity>> mDefeatedBy;

    bool mPop100 = false;
    bool mPop500 = false;
    bool mPop1000 = false;
    bool mPop2000 = false;
    bool mPop3000 = false;
    bool mPop5000 = false;
    bool mPop10000 = false;
    bool mPop15000 = false;
    bool mPop20000 = false;
    bool mPop25000 = false;

    int mUpdateResources = 999999;
};

#endif // EGAMEBOARD_H
