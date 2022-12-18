#include "egameboard.h"

#include <random>

#include "characters/echaracter.h"
#include "buildings/ebuilding.h"
#include "spawners/espawner.h"

#include "buildings/estoragebuilding.h"

#include "characters/esoldier.h"
#include "characters/esoldierbanner.h"

#include "buildings/sanctuaries/esanctbuilding.h"
#include "buildings/etradepost.h"

#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"

#include "buildings/epalace.h"
#include "buildings/epalacetile.h"

#include "buildings/ehorseranch.h"

#include "engine/boardData/eheatmaptask.h"

#include "missiles/emissile.h"

#include "etilehelper.h"

#include "emessages.h"

#include "spawners/elandinvasionpoint.h"

#include "buildings/eheatgetters.h"

#include "fileIO/ebuildingreader.h"
#include "fileIO/ebuildingwriter.h"

#include "eevent.h"
#include "emessageeventtype.h"

#include "gameEvents/egameeventcycle.h"
#include "gameEvents/egodvisitevent.h"
#include "gameEvents/egodattackevent.h"
#include "gameEvents/emonsterattackevent.h"
#include "gameEvents/einvasionevent.h"
#include "gameEvents/epaytributeevent.h"
#include "gameEvents/egrantrequestevent.h"
#include "gameEvents/egiftevent.h"
#include "gameEvents/egrantgeneralrequestevent.h"

#include "eeventdata.h"

#include "einvasionhandler.h"

#include "evectorhelpers.h"
#include "egifthelpers.h"

eGameBoard::eGameBoard() :
    mEmplData(mPopData, *this) {
    const int min = static_cast<int>(eBuildingMode::road);
    const int max = static_cast<int>(eBuildingMode::theseusHall);
    for(int i = min; i <= max; i++) {
        const auto bm = static_cast<eBuildingMode>(i);
        mSupportedBuildings.push_back(bm);
    }
    mSupportedResources = eResourceType::all;
}

eGameBoard::~eGameBoard() {
    clear();
}

void eGameBoard::initialize(const int w, const int h) {
    mThreadPool.initialize(w, h);

    clear();
    mTiles.reserve(w);
    for(int x = 0; x < w; x++) {
        std::vector<eTile*> yArr;
        yArr.reserve(h);
        for(int y = 0; y < h; y++) {
            int tx;
            int ty;
            eTileHelper::dtileIdToTileId(x, y, tx, ty);
            const auto tile = new eTile(tx, ty, x, y);
            yArr.push_back(tile);
        }
        mTiles.push_back(yArr);
    }
    mWidth = w;
    mHeight = h;

    mAppealMap.initialize(w, h);

    updateNeighbours();
}

void eGameBoard::clear() {
    for(const auto& x : mTiles) {
        for(const auto y : x) {
            delete y;
        }
    }
    mTiles.clear();
    mWidth = 0;
    mHeight = 0;
}

void eGameBoard::iterateOverAllTiles(const eTileAction& a) {
    for(int y = 0; y < mHeight; y++) {
        for(int x = 0; x < mWidth; x++) {
            const auto t = dtile(x, y);
            a(t);
        }
    }
}

void eGameBoard::scheduleAppealMapUpdate() {
    mUpdateAppeal = true;
}

void eGameBoard::updateAppealMapIfNeeded() {
    if(!mUpdateAppeal) return;
    mUpdateAppeal = false;
    const auto finish = [this](eHeatMap& map) {
        std::swap(appealMap(), map);
    };
    const auto task = new eHeatMapTask(eHeatGetters::appeal, finish);
    mThreadPool.queueTask(task);
}

void eGameBoard::clearBannerSelection() {
    for(const auto s : mSelectedBanners) {
        s->setSelected(false);
    }
    mSelectedBanners.clear();
}

void eGameBoard::deselectBanner(eSoldierBanner* const c) {
    eVectorHelpers::remove(mSelectedBanners, c);
    c->setSelected(false);
}

void eGameBoard::selectBanner(eSoldierBanner* const c) {
    mSelectedBanners.push_back(c);
    c->setSelected(true);
}

void eGameBoard::bannersGoHome() {
    for(const auto b : mSelectedBanners) {
        b->goHome();
    }
}

void eGameBoard::bannersBackFromHome() {
    for(const auto b : mSelectedBanners) {
        b->backFromHome();
    }
}

void eGameBoard::setRegisterBuildingsEnabled(const bool e) {
    mRegisterBuildingsEnabled = e;
}

void eGameBoard::setButtonsVisUpdater(const eAction& u) {
    mButtonVisUpdater = u;
}

void eGameBoard::addSupportedBuilding(const eBuildingMode t) {
    if(supportsBuilding(t)) return;
    mSupportedBuildings.push_back(t);
    if(mButtonVisUpdater) mButtonVisUpdater();
}

void eGameBoard::removeSupportedBuilding(const eBuildingMode t) {
    const bool r = eVectorHelpers::remove(mSupportedBuildings, t);
    if(r) mButtonVisUpdater();
}

bool eGameBoard::supportsBuilding(const eBuildingMode t) const {
    return eVectorHelpers::contains(mSupportedBuildings, t);
}

bool eGameBoard::supportsResource(const eResourceType rt) const {
    const auto s = mSupportedResources & rt;
    return static_cast<bool>(s);
}

eResourceType eGameBoard::supportedResources() const {
    return mSupportedResources;
}

eBuilding* eGameBoard::randomBuilding(const eBuildingValidator& v) const {
    auto blds = mTimedBuildings;
    std::random_shuffle(blds.begin(), blds.end());
    for(const auto b : blds) {
        const bool r = v(b);
        if(r) return b;
    }
    return nullptr;
}

int eGameBoard::horses() const {
    int h = 0;
    for(const auto b : mTimedBuildings) {
        if(b->type() != eBuildingType::horseRanch) continue;
        const auto r = static_cast<eHorseRanch*>(b);
        h += r->horseCount();
    }
    return h;
}

void eGameBoard::planAction(ePlannedAction* const a) {
    mPlannedActions.emplace_back(a);
}

void eGameBoard::restockMarbleTiles() {
    int maxLevel = 0;
    for(const auto t : mMarbleTiles) {
        if(t->resource() > 0) return;
        const int l = t->marbleLevel();
        if(l > maxLevel) {
            maxLevel = l;
        }
    }
    for(const auto t : mMarbleTiles) {
        const int l = t->marbleLevel();
        if(l == maxLevel) {
            t->setResource(10000);
        }
    }
}

void eGameBoard::updateMarbleTiles() {
    mMarbleTiles.clear();
    iterateOverAllTiles([&](eTile* const t) {
        if(t->terrain() != eTerrain::marble) return;
        mMarbleTiles.push_back(t);
    });
}
void eGameBoard::setFriendlyGods(const std::vector<eGodType>& gods) {
    mFriendlyGods = gods;

    const auto e = e::make_shared<eGodVisitEvent>(*this);
    e->setTypes(gods);
    eDate date = mDate;
    const int period = 450;
    date += period;
    const auto ec = e::make_shared<eGameEventCycle>(
                        e, date, period, 10000, *this);
    addGameEvent(ec);
}

void eGameBoard::setHostileGods(const std::vector<eGodType>& gods) {
    mHostileGods = gods;

    const auto e = e::make_shared<eGodAttackEvent>(*this);
    e->setTypes(gods);
    eDate date = mDate;
    const int period = 900;
    date += period;
    const auto ec = e::make_shared<eGameEventCycle>(
                        e, date, period, 10000, *this);
    addGameEvent(ec);
}

void eGameBoard::setHostileMonsters(const std::vector<eMonsterType>& monsters) {
    mHostileMonsters = monsters;

    const auto e = e::make_shared<eMonsterAttackEvent>(*this);
    e->setTypes(monsters);
    const int period = 150;
    const auto date = mDate + period;
    const auto ec = e::make_shared<eGameEventCycle>(
                        e, date, period, 2, *this);
    addGameEvent(ec);
}

void eGameBoard::planInvasion(int stage, int months,
                              const int infantry,
                              const int cavalry,
                              const int archers) {
    const auto e = e::make_shared<eInvasionEvent>(*this);
    const auto city = mWorldBoard.cities().front();
    const int totalMonths = months;
    if(stage == 0) {
        if(totalMonths > 24) {
            stage = 0;
            months -= 24;
        } else if(totalMonths > 12) {
            stage = 1;
            months -= 12;
        } else if(totalMonths > 6) {
            stage = 2;
            months -= 6;
        } else if(totalMonths > 1) {
            stage = 3;
            months -= 1;
        }
        eEventData ed;
        ed.fType = eMessageEventType::invasionMessage;
        ed.fCity = city;
        ed.fTime = totalMonths;
        event(eEvent::invasion36, ed);
    }
    e->initialize(stage + 1, city, infantry, cavalry, archers);
    const int days = months*31;
    const auto date = mDate + days;
    const auto ec = e::make_shared<eGameEventCycle>(
                        e, date, days, 1, *this);
    addGameEvent(ec);
}

void eGameBoard::read(eReadStream& src) {
    int w;
    src >> w;
    int h;
    src >> h;
    initialize(w, h);

    src >> mDrachmas;
    src >> mDifficulty;
    src >> mWageRate;
    src >> mTaxRate;

    mDate.read(src);
    src >> mTime;
    src >> mTotalTime;

    src >> mSoldiersUpdate;
    src >> mMaxRockThrowers;
    src >> mMaxHoplites;
    src >> mMaxHorsemen;

    src >> mCoverageUpdate;
    src >> mAthleticsCoverage;
    src >> mPhilosophyCoverage;
    src >> mDramaCoverage;
    src >> mAllDiscCoverage;
    src >> mTaxesCoverage;
    src >> mUnrest;
    src >> mPopularity;
    src >> mHealth;

    src >> mWonGames;

    mUpdateAppeal = true;

    for(const auto& ts : mTiles) {
        for(const auto& t : ts) {
            t->read(src);
            bool hasB;
            src >> hasB;
            if(!hasB) continue;
            eBannerTypeS type;
            src >> type;
            int id;
            src >> id;
            const auto b = eBanner::sCreate(id, t, *this, type);
            b->read(src);
        }
    }

    {
        int nbs;
        src >> nbs;
        for(int i = 0; i < nbs; i++) {
            eBuildingType type;
            src >> type;
            eBuildingReader::sRead(*this, type, src);
        }
    }


    {
        int ncs;
        src >> ncs;

        for(int i = 0; i < ncs; i++) {
            eCharacterType type;
            src >> type;
            const auto c = eCharacter::sCreate(type, *this);
            c->read(src);
        }
    }

    {
        int nb;
        src >> nb;

        for(int i = 0; i < nb; i++) {
            eBannerType type;
            src >> type;
            const auto b = e::make_shared<eSoldierBanner>(type, *this);
            b->read(src);
            registerSoldierBanner(b);
        }
    }

    {
        int ni;
        src >> ni;

        for(int i = 0; i < ni; i++) {
            const auto ii = new eInvasionHandler(*this, nullptr);
            ii->read(src);
        }
    }

    {
        int ncs;
        src >> ncs;

        for(int i = 0; i < ncs; i++) {
            eMissileType type;
            src >> type;
            const auto c = eMissile::sCreate(*this, type);
            c->read(src);
        }
    }

    int nfg;
    src >> nfg;
    for(int i = 0; i < nfg; i++) {
        eGodType type;
        src >> type;
        mFriendlyGods.push_back(type);
    }

    int nrg;
    src >> nrg;
    for(int i = 0; i < nrg; i++) {
        eGodType type;
        src >> type;
        mHostileGods.push_back(type);
    }

    int nevs;
    src >> nevs;
    for(int i = 0; i < nevs; i++) {
        const auto e = e::make_shared<eGameEventCycle>(*this);
        e->read(src);
        mGameEvents.push_back(e);
    }

    mWorldBoard.read(src);

    src.handlePostFuncs();
}

void eGameBoard::write(eWriteStream& dst) const {
    dst << mWidth;
    dst << mHeight;

    dst << mDrachmas;
    dst << mDifficulty;
    dst << mWageRate;
    dst << mTaxRate;

    mDate.write(dst);
    dst << mTime;
    dst << mTotalTime;

    dst << mSoldiersUpdate;
    dst << mMaxRockThrowers;
    dst << mMaxHoplites;
    dst << mMaxHorsemen;

    dst << mCoverageUpdate;
    dst << mAthleticsCoverage;
    dst << mPhilosophyCoverage;
    dst << mDramaCoverage;
    dst << mAllDiscCoverage;
    dst << mTaxesCoverage;
    dst << mUnrest;
    dst << mPopularity;
    dst << mHealth;

    dst << mWonGames;

    {
        int id = 0;
        for(const auto b : mAllBuildings) {
            b->setIOID(id++);
        }
    }
    {
        int id = 0;
        for(const auto c : mCharacters) {
            c->setIOID(id++);
        }
    }
    {
        int id = 0;
        for(const auto ca : mCharacterActions) {
            ca->setIOID(id++);
        }
    }
    {
        int id = 0;
        for(const auto b : mBanners) {
            b->setIOID(id++);
        }
    }

    mWorldBoard.setIOIDs();

    for(const auto& ts : mTiles) {
        for(const auto& t : ts) {
            t->write(dst);
            const auto b = t->banner();
            const bool has = b != nullptr;
            dst << has;
            if(!has) continue;
            dst << b->type();
            dst << b->id();
            b->write(dst);
        }
    }

    {
        const int nbs = mAllBuildings.size();
        dst << nbs;
        for(const auto b : mAllBuildings) {
            dst << b->type();
            eBuildingWriter::sWrite(b, dst);
        }
    }

    {
        const int ncs = mCharacters.size();
        dst << ncs;
        for(const auto c : mCharacters) {
            dst << c->type();
            c->write(dst);
        }
    }

    {
        const int nb = mSoldierBanners.size();
        dst << nb;
        for(const auto& b : mSoldierBanners) {
            dst << b->type();
            b->write(dst);
        }
    }

    {
        const int ni = mInvasions.size();
        dst << ni;
        for(const auto i : mInvasions) {
            i->write(dst);
        }
    }

    {
        const int ncs = mMissiles.size();
        dst << ncs;
        for(const auto c : mMissiles) {
            dst << c->type();
            c->write(dst);
        }
    }

    const int nfg = mFriendlyGods.size();
    dst << nfg;
    for(const auto g : mFriendlyGods) {
        dst << g;
    }

    const int nrg = mHostileGods.size();
    dst << nrg;
    for(const auto g : mHostileGods) {
        dst << g;
    }

    dst << mGameEvents.size();
    for(const auto& e : mGameEvents) {
        e->write(dst);
    }

    mWorldBoard.write(dst);
}

eBuilding* eGameBoard::buildingWithIOID(const int id) const {
    for(const auto b : mAllBuildings) {
        const int bio = b->ioID();
        if(bio == id) return b;
    }
    return nullptr;
}

eCharacter* eGameBoard::characterWithIOID(const int id) const {
    for(const auto c : mCharacters) {
        const int bio = c->ioID();
        if(bio == id) return c;
    }
    return nullptr;
}

eCharacterAction* eGameBoard::characterActionWithIOID(const int id) const {
    for(const auto ca : mCharacterActions) {
        const int bio = ca->ioID();
        if(bio == id) return ca;
    }
    return nullptr;
}

eBanner* eGameBoard::bannerWithIOID(const int id) const {
    for(const auto b : mBanners) {
        const int bio = b->ioID();
        if(bio == id) return b;
    }
    return nullptr;
}

eTile* eGameBoard::landInvasionTile(const int id) {
    const auto it = mLandInvasion.find(id);
    if(it == mLandInvasion.end()) return nullptr;
    return it->second->tile();
}

void eGameBoard::addLandInvasionPoint(eLandInvasionPoint* const p) {
    const int id = p->id();
    const auto it = mLandInvasion.find(id);
    if(it != mLandInvasion.end()) {
        delete it->second;
    }
    mLandInvasion[id] = p;
}

void eGameBoard::removeLandInvasionPoint(const int id) {
    mLandInvasion.erase(id);
}

void eGameBoard::addInvasion(eInvasionHandler* const i) {
    mInvasions.push_back(i);
}

void eGameBoard::removeInvasion(eInvasionHandler* const i) {
    eVectorHelpers::remove(mInvasions, i);
}

int eGameBoard::addResource(const eResourceType type,
                            const int count) {
    if(type == eResourceType::drachmas) {
        incDrachmas(count);
        return count;
    }
    int rem = count;
    for(const auto s : mStorBuildings) {
        const int c = s->add(type, rem);
        rem -= c;
        if(rem <= 0) break;
    }
    return count - rem;
}

int eGameBoard::spaceForResource(const eResourceType type) {
    int r = 0;
    for(const auto s : mStorBuildings) {
        r += s->spaceLeft(type);
    }
    return r;
}

void eGameBoard::grantGeneralRequest(const stdsptr<eWorldCity>& c,
                                     const eResourceType type,
                                     const int count,
                                     const int postpone) {
    eEventData ed;
    ed.fCity = c;
    ed.fResourceType = type;
    ed.fResourceCount = count < 0 ? -count : count;
    ed.fTime = 6;
    ed.fA0Key = "dispatch_now";
    ed.fA1Key = "postpone";
    ed.fA2Key = "refuse";

    if(count <= 0) {
        if(postpone > 1 && postpone < 5) {
            ed.fType = eMessageEventType::resourceGranted;
            event(eEvent::generalRequestTooLate, ed);
            c->incAttitude(-5);
        } else {
            ed.fType = eMessageEventType::resourceGranted;
            event(eEvent::generalRequestComply, ed);
            c->incAttitude(10);
        }
        return;
    }

    if(postpone > 3) {
        ed.fType = eMessageEventType::resourceGranted;
        event(eEvent::generalRequestRefuse, ed);
        c->incAttitude(-15);
        return;
    }

    const int avCount = resourceCount(type);
    ed.fSpaceCount = avCount;

    ed.fType = eMessageEventType::requestTributeGranted;
    if(avCount >= count) {
        ed.fA0 = [this, c, type, count, postpone]() { // dispatch now
            takeResource(type, count);
            const auto e = e::make_shared<eGrantGeneralRequestEvent>(
                        *this);
            e->initialize(postpone, type, -count, c);
            const auto date = mDate + 3*31;
            const auto ec = e::make_shared<eGameEventCycle>(
                                e, date, *this);
            addGameEvent(ec);
        };
    }

    if(postpone < 4) {
        ed.fA1 = [this, c, type, count, postpone]() { // postpone
            const auto e = e::make_shared<eGrantGeneralRequestEvent>(
                        *this);
            e->initialize(postpone + 1, type, count, c);
            const auto date = mDate + 6*31;
            const auto ec = e::make_shared<eGameEventCycle>(
                                e, date, *this);
            addGameEvent(ec);
        };
    }

    ed.fA2 = [this, c, type, count]() { // refuse
        const auto e = e::make_shared<eGrantGeneralRequestEvent>(
                    *this);
        e->initialize(5, type, count, c);
        const auto date = mDate + 31;
        const auto ec = e::make_shared<eGameEventCycle>(
                            e, date, *this);
        addGameEvent(ec);
    };


    ed.fType = eMessageEventType::generalRequestGranted;
    const auto rel = c->relationship();
    if(rel == eWorldCityRelationship::rival) {
        if(postpone == 0) { // initial
            event(eEvent::generalRequestRivalInitial, ed);
        } else if(postpone == 1) { // reminder
            event(eEvent::generalRequestRivalReminder, ed);
        } else if(postpone == 2) { // overdue
            event(eEvent::generalRequestRivalReminder, ed);
        } else if(postpone == 3) { // warning
            event(eEvent::generalRequestRivalWarning, ed);
        }
    } else {
        if(postpone == 0) { // initial
            event(eEvent::generalRequestInitial, ed);
        } else if(postpone == 1) { // reminder
            event(eEvent::generalRequestReminder, ed);
        } else if(postpone == 2) { // overdue
            event(eEvent::generalRequestReminder, ed);
        } else if(postpone == 3) { // warning
            event(eEvent::generalRequestWarning, ed);
        }
    }
}

void eGameBoard::request(const stdsptr<eWorldCity>& c,
                         const eResourceType type) {
    const auto e = e::make_shared<eGrantRequestEvent>(*this);
    e->initialize(true, type, c);
    const auto date = mDate + 90;
    const auto ec = e::make_shared<eGameEventCycle>(
                        e, date, *this);
    addGameEvent(ec);
}

void eGameBoard::grantRequest(const stdsptr<eWorldCity>& c,
                              const eResourceType type,
                              const bool postpone) {
    const int count = 2*eGiftHelpers::giftCount(type);

    const int space = spaceForResource(type);
    eEventData ed;
    ed.fCity = c;
    ed.fSpaceCount = space;
    ed.fResourceType = type;
    ed.fResourceCount = count;

    const auto rel = c->relationship();
    if(rel == eWorldCityRelationship::rival) {
        ed.fType = eMessageEventType::resourceGranted;
        const bool refuse = true;
        if(refuse) {
            event(eEvent::demandRefused, ed);
        }
        return;
    }

    if(space == 0) {
        ed.fType = eMessageEventType::resourceGranted;

        const auto e = e::make_shared<eGrantRequestEvent>(
                    *this);
        e->initialize(false, type, c);
        const auto date = mDate + 31;
        const auto ec = e::make_shared<eGameEventCycle>(
                            e, date, *this);
        addGameEvent(ec);
    } else {
        ed.fType = eMessageEventType::requestTributeGranted;
        if(space != 0) {
            ed.fA0 = [this, c, type, count]() { // accept
                const int a = addResource(type, count);
                if(a == count) return;
                eEventData ed;
                ed.fType = eMessageEventType::resourceGranted;
                ed.fCity = c;
                ed.fResourceType = type;
                ed.fResourceCount = a;
                event(eEvent::requestAccepted, ed);
            };
        }

        if(postpone) {
            ed.fA1 = [this, c, type, count]() { // postpone
                eEventData ed;
                ed.fType = eMessageEventType::resourceGranted;
                ed.fCity = c;
                ed.fResourceType = type;
                ed.fResourceCount = count;
                event(eEvent::requestPostponed, ed);

                const auto e = e::make_shared<eGrantRequestEvent>(
                            *this);
                e->initialize(false, type, c);
                const auto date = mDate + 31;
                const auto ec = e::make_shared<eGameEventCycle>(
                                    e, date, *this);
                addGameEvent(ec);
            };
        }

        ed.fA2 = [this, c, type, count]() { // decline
            eEventData ed;
            ed.fType = eMessageEventType::resourceGranted;
            ed.fCity = c;
            ed.fResourceType = type;
            ed.fResourceCount = count;
            event(eEvent::requestRefused, ed);
        };
    }
    if(!postpone) {
        if(space == 0) {
            event(eEvent::requestForfeited, ed);
        } else if(space >= count) {
            event(eEvent::requestGranted, ed);
        } else {
            event(eEvent::requestLastChance, ed);
        }
    } else if(space == 0) {
        event(eEvent::requestInsufficientSpace, ed);
    } else if(space >= count) {
        event(eEvent::requestGranted, ed);
    } else {
        event(eEvent::requestPartialSpace, ed);
    }
}

void eGameBoard::payTribute(const stdsptr<eWorldCity>& c,
                            const bool postpone) {
    const auto type = c->tributeType();
    const auto count = c->tributeCount();

    eEventData ed;
    ed.fType = eMessageEventType::requestTributeGranted;
    ed.fCity = c;
    ed.fSpaceCount = spaceForResource(type);
    ed.fResourceType = c->tributeType();
    ed.fResourceCount = c->tributeCount();
    ed.fA0 = [this, c, type, count]() { // accept
        const int a = addResource(type, count);
        if(a == count) return;
        eEventData ed;
        ed.fType = eMessageEventType::resourceGranted;
        ed.fCity = c;
        ed.fResourceType = type;
        ed.fResourceCount = a;
        event(eEvent::tributeAccepted, ed);
    };
    if(postpone) {
        ed.fA1 = [this, c, type, count]() { // postpone
            eEventData ed;
            ed.fType = eMessageEventType::resourceGranted;
            ed.fCity = c;
            ed.fResourceType = type;
            ed.fResourceCount = count;
            event(eEvent::tributePostponed, ed);

            const auto e = e::make_shared<ePayTributeEvent>(
                        *this);
            e->initialize(c);
            const auto date = mDate + 31;
            const auto ec = e::make_shared<eGameEventCycle>(
                                e, date, *this);
            addGameEvent(ec);
        };
    }
    ed.fA2 = [this, c, type, count]() { // decline
        eEventData ed;
        ed.fType = eMessageEventType::resourceGranted;
        ed.fCity = c;
        ed.fResourceType = type;
        ed.fResourceCount = count;
        event(eEvent::tributeDeclined, ed);
    };
    event(eEvent::tributePaid, ed);
}

void eGameBoard::gift(const stdsptr<eWorldCity>& c,
                      const eResourceType type,
                      const int count) {
    takeResource(type, count);
    const auto e = e::make_shared<eGiftEvent>(*this);
    e->initialize(c, type, count);
    const auto date = mDate + 90;
    const auto ec = e::make_shared<eGameEventCycle>(
                        e, date, *this);
    addGameEvent(ec);
}

void eGameBoard::giftReceived(const stdsptr<eWorldCity>& c,
                              const eResourceType type,
                              const int count) {
    const bool a = c->acceptsGift(type, count);
    eEventData ed;
    ed.fType = eMessageEventType::resourceGranted;
    ed.fCity = c;
    ed.fResourceType = type;
    ed.fResourceCount = count;
    if(a) {
        const bool b = c->buys(type);
        const bool s = c->sells(type);
        if(type == eResourceType::drachmas) {
            event(eEvent::giftReceivedDrachmas, ed);
            c->incAttitude(10);
        } else if(b) {
            event(eEvent::giftReceivedNeeded, ed);
            c->incAttitude(10);
        } else if(s) {
            event(eEvent::giftReceivedSells, ed);
            c->incAttitude(5);
        } else {
            event(eEvent::giftReceivedNotNeeded, ed);
            c->incAttitude(5);
        }
        c->gifted(type, count);
    } else {
        event(eEvent::giftReceivedRefuse, ed);
    }
}

void eGameBoard::waitUntilFinished() {
    while(!mThreadPool.finished()) {
        mThreadPool.waitFinished();
        mThreadPool.handleFinished();
    }
}

void eGameBoard::updateTileRenderingOrder() {
    std::vector<std::vector<std::pair<int, int>>> map;
    map.reserve(width());
    for(int x = 0; x < width(); x++) {
        auto& m = map.emplace_back();
        m.reserve(height());
        for(int y = 0; y < height(); y++) {
            m.push_back({0, 0});
        }
    }

    const auto updateRenderingOrder = [&](eTile* const tile) {
        tile->terrainTiles().clear();
        bool elev = false;
        const int a = tile->altitude();
        for(int x = 0; x < 2 && !elev; x++) {
            for(int y = 0; y < 2 && !elev; y++) {
                if(x == 0 && y == 0) continue;
                const auto t = tile->tileRel(x, y);
                if(!t) continue;
                const int ta = t->altitude();
                if(ta > a) elev = true;
            }
        }
        if(elev) {
            tile->addTerrainTile(tile);
            const int dx = tile->dx();
            const int dy = tile->dy();
            map[dx][dy] = {dx, dy};
            return;
        }
        const auto ubt = tile->underBuildingType();
        const auto ub = tile->underBuilding();
        const auto sc = dynamic_cast<eSanctBuilding*>(ub);
        const bool r = sc && sc->progress() == 0;
        if(r || eBuilding::sFlatBuilding(ubt)) {
            const int tx = tile->dx();
            const int ty = tile->dy();
            bool found = false;
            eTile* lastT = tile;
            int ttx;
            int tty;

            int mmx = 0;
            int mmy = 0;

            for(int i = 1; i < 3 && !found; i++) {
                tty = ty - i;
                const int w = i + 1;
                const int ddx = ty % 2 == 0 ? 1 : 0;
                const int dx = -(i + ddx)/2;
                ttx = tx + i + dx;
                for(int j = 0; j < w && !found; j++, ttx--) {
                    const auto t = eGameBoard::dtile(ttx, tty);
                    if(!t) continue;
                    {
                        const auto& coords = map[ttx][tty];
                        const int cx = coords.first;
                        const int cy = coords.second;
                        if(cy > mmy) {
                            mmy = cy;
                            mmx = cx;
                        } else if(cy == mmy) {
                            if(cx > mmx) {
                                mmx = cx;
                            }
                        }
                        if(tty < mmy || (tty == mmy && ttx < mmx)) {
                            found = true;
                            break;
                        }
                    }
                    lastT = t;
//                    if(t->altitude() < tile->altitude()) {
//                        found = true;
//                        break;
//                    }
                    const auto tubt = t->underBuildingType();
                    const auto ub = t->underBuilding();
                    const auto sc = dynamic_cast<eSanctBuilding*>(ub);
                    const bool r = sc && sc->progress() == 0;
                    if(!r && !eBuilding::sFlatBuilding(tubt)) {
//                        const auto b = t->underBuilding();
//                        const auto ct = b->centerTile();
                        lastT = t;
                        found = true;
                        break;
                    }
                }
            }

            if(lastT) {
                lastT->addTerrainTile(tile);
                const int dx = tile->dx();
                const int dy = tile->dy();
                const int ddx = lastT->dx();
                const int ddy = lastT->dy();
                map[dx][dy] = {ddx, ddy};
            }
        }
    };

    iterateOverAllTiles([&](eTile* const tile) {
        updateRenderingOrder(tile);
    });
}

void eGameBoard::updateMaxSoldiers() {
    mMaxRockThrowers = 0;
    mMaxHoplites = 0;
    mMaxHorsemen = 0;
    for(const auto b : mTimedBuildings) {
        const auto bt = b->type();
        if(bt == eBuildingType::commonHouse) {
            const auto ch = static_cast<eSmallHouse*>(b);
            const int l = ch->level();
            if(l < 2) continue;
            if(l == 2) mMaxRockThrowers += 5;
            else if(l == 3) mMaxRockThrowers += 6;
            else if(l == 4) mMaxRockThrowers += 10;
            else if(l == 5) mMaxRockThrowers += 12;
            else if(l == 6) mMaxRockThrowers += 15;
        } else if(bt == eBuildingType::eliteHousing) {
            const auto eh = static_cast<eEliteHousing*>(b);
            const int l = eh->level();
            if(l < 2) continue;
            const int a = eh->arms();
            if(l == 2) {
                mMaxHoplites += std::min(2, a);
            } else if(l == 3) {
                mMaxHoplites += std::min(4, a);
            } else if(l == 4) {
                const int h = eh->horses();
                const int hh = std::min(std::min(a, 4), h);
                mMaxHorsemen += hh;
                mMaxHoplites += std::min(4 - hh, a - hh);
            }
        }
    }
    mMaxRockThrowers /= 6;
}

void eGameBoard::addSoldier(const eCharacterType st) {
    bool found = false;
    for(const auto& b : mSoldierBanners) {
        const auto bt = b->type();
        const int c = b->count();
        if(c >= 8) continue;
        if(bt == eBannerType::rockThrower &&
           st == eCharacterType::rockThrower) {
            found = true;
        } else if(bt == eBannerType::hoplite &&
                  st == eCharacterType::hoplite) {
            found = true;
        } else if(bt == eBannerType::horseman &&
                  st == eCharacterType::horseman){
            found = true;
        }
        if(found) {
            b->incCount();
            break;
        }
    }
    if(found) return;
    eBannerType bt;
    if(st == eCharacterType::rockThrower) {
        bt = eBannerType::rockThrower;
    } else if(st == eCharacterType::hoplite) {
        bt = eBannerType::hoplite;
    } else { //horseman
        bt = eBannerType::horseman;
    }
    const auto b = e::make_shared<eSoldierBanner>(bt, *this);
    b->setPlayerId(1);
    registerSoldierBanner(b);
    b->incCount();
    const auto ts = mPalace->tiles();
    for(const auto& t : ts) {
        const auto tt = t->centerTile();
        if(!tt) continue;
        const auto bb = tt->banner();
        if(bb) continue;
        b->moveTo(tt->x(), tt->y());
        break;
    }
}

void eGameBoard::removeSoldier(const eCharacterType st) {
    for(const auto& b : mSoldierBanners) {
        const auto bt = b->type();
        const int c = b->count();
        if(c <= 0) continue;
        bool found = false;
        if(bt == eBannerType::rockThrower &&
           st == eCharacterType::rockThrower) {
            found = true;
        } else if(bt == eBannerType::hoplite &&
                  st == eCharacterType::hoplite) {
            found = true;
        } else if(bt == eBannerType::horseman &&
                  st == eCharacterType::horseman){
            found = true;
        }
        if(found) {
            b->decCount();
            if(b->count() <= 0) {
                unregisterSoldierBanner(b);
            }
            break;
        }
    }
}

void eGameBoard::distributeSoldiers() {
    if(!hasPalace()) return;
    int cRockThrowers = 0;
    int cHoplites = 0;
    int cHorsemen = 0;
    for(const auto& b : mSoldierBanners) {
        const auto bt = b->type();
        const int c = b->count();
        if(bt == eBannerType::rockThrower) {
            cRockThrowers += c;
        } else if(bt == eBannerType::hoplite) {
            cHoplites += c;
        } else { //horseman
            cHorsemen += c;
        }
    }
    const int remRockThrowers = mMaxRockThrowers - cRockThrowers;
    const int remHoplites = mMaxHoplites - cHoplites;
    const int remHorsemen = mMaxHorsemen - cHorsemen;

    for(int i = 0; i < remRockThrowers; i++) {
        addSoldier(eCharacterType::rockThrower);
    }
    for(int i = 0; i < -remRockThrowers; i++) {
        removeSoldier(eCharacterType::rockThrower);
    }
    for(int i = 0; i < remHoplites; i++) {
        addSoldier(eCharacterType::hoplite);
    }
    for(int i = 0; i < -remHoplites; i++) {
        removeSoldier(eCharacterType::hoplite);
    }
    for(int i = 0; i < remHorsemen; i++) {
        addSoldier(eCharacterType::horseman);
    }
    for(int i = 0; i < -remHorsemen; i++) {
        removeSoldier(eCharacterType::horseman);
    }
}

void eGameBoard::registerSoldierBanner(const stdsptr<eSoldierBanner>& b) {
    mSoldierBanners.push_back(b);
}

bool eGameBoard::unregisterSoldierBanner(const stdsptr<eSoldierBanner>& b) {
    eVectorHelpers::remove(mSelectedBanners, b.get());
    return eVectorHelpers::remove(mSoldierBanners, b);
}

void eGameBoard::addGameEvent(const stdsptr<eGameEventCycle>& e) {
    mGameEvents.push_back(e);
}

void eGameBoard::updateCoverage() {
    int people = 0;
    int sport = 0;
    int phil = 0;
    int drama = 0;
    int taxes = 0;
    for(const auto b : mTimedBuildings) {
        if(const auto h = dynamic_cast<eHouseBase*>(b)) {
            const int p = h->people();
            if(h->athletes() > 0) {
                sport += p;
            }
            if(h->philosophers() > 0) {
                phil += p;
            }
            if(h->actors() > 0) {
                drama += p;
            }
            if(h->paidTaxes()) {
                taxes += p;
            }
            people += p;
        }
    }
    if(people <= 0) {
        mAthleticsCoverage = 0;
        mPhilosophyCoverage = 0;
        mDramaCoverage = 0;
        mTaxesCoverage = 0;
    } else {
        mAthleticsCoverage = std::round(100.*sport/people);
        mPhilosophyCoverage = std::round(100.*phil/people);
        mDramaCoverage = std::round(100.*drama/people);
        mTaxesCoverage = std::round(100.*taxes/people);
    }
    mAllDiscCoverage = (mAthleticsCoverage + mPhilosophyCoverage + mDramaCoverage)/3;
}

double coverageMultiplier(const int pop) {
    if(pop < 250) return 0.125;
    else if(pop < 500) return 0.25;
    else if(pop < 1000) return 0.375;
    else return 0.5;
}

void eGameBoard::handleGamesBegin(const eGames game) {
    int coverage = 0;
    eGameMessages* msgs = nullptr;
    switch(game) {
    case eGames::isthmian:
        msgs = &eMessages::instance.fIsthmianGames;
        coverage = mPhilosophyCoverage;
        break;
    case eGames::nemean:
        msgs = &eMessages::instance.fNemeanGames;
        coverage = mAthleticsCoverage;
        break;
    case eGames::pythian:
        msgs = &eMessages::instance.fPythianGames;
        coverage = mDramaCoverage;
        break;
    case eGames::olympian:
        msgs = &eMessages::instance.fOlympianGames;
        coverage = mAllDiscCoverage;
        break;
    }
    const int pop = mPopData.population();
    const double mult = coverageMultiplier(pop);

    eEventData ed;
    if(mult*coverage > 15) {
        showMessage(ed, msgs->fBegin);
    } else {
        showMessage(ed, msgs->fNoPart);
    }
}

void eGameBoard::handleGamesEnd(const eGames game) {
    int coverage = 0;
    eGameMessages* msgs = nullptr;
    switch(game) {
    case eGames::isthmian:
        msgs = &eMessages::instance.fIsthmianGames;
        coverage = mPhilosophyCoverage;
        break;
    case eGames::nemean:
        msgs = &eMessages::instance.fNemeanGames;
        coverage = mAthleticsCoverage;
        break;
    case eGames::pythian:
        msgs = &eMessages::instance.fPythianGames;
        coverage = mDramaCoverage;
        break;
    case eGames::olympian:
        msgs = &eMessages::instance.fOlympianGames;
        coverage = mAllDiscCoverage;
        break;
    }

    const int pop = mPopData.population();
    const double mult = coverageMultiplier(pop);

    if(mult*coverage < 15) {
        return;
    } else {
        const double coveragef = coverage/100.;
        const double chance = mult*coveragef*coveragef;
        const bool won = rand() % 101 < 100*chance;

        eEventData ed;
        if(won) {
            showMessage(ed, msgs->fWon);
            mWonGames++;
        } else {
            const bool second = rand() % 101 < 200*chance;
            if(second) {
                showMessage(ed, msgs->fSecond);
            } else {
                showMessage(ed, msgs->fLost);
            }
        }
    }
}

void eGameBoard::updateTileRenderingOrderIfNeeded() {
    if(mTileRenderingOrderUpdateNeeded) {
        updateTileRenderingOrder();
        mTileRenderingOrderUpdateNeeded = false;
    }
}

eTile* eGameBoard::tile(const int x, const int y) const {
    int dtx;
    int dty;
    eTileHelper::tileIdToDTileId(x, y, dtx, dty);
    return dtile(dtx, dty);
}

eTile* eGameBoard::dtile(const int x, const int y) const {
    if(x < 0 || x >= mWidth) return nullptr;
    if(y < 0 || y >= mHeight) return nullptr;
    return mTiles[x][y];
}

void eGameBoard::registerCharacter(eCharacter* const c) {
    mCharacters.push_back(c);
}

bool eGameBoard::unregisterCharacter(eCharacter* const c) {
    return eVectorHelpers::remove(mCharacters, c);
}

void eGameBoard::registerCharacterAction(eCharacterAction* const ca) {
    mCharacterActions.push_back(ca);
}

bool eGameBoard::unregisterCharacterAction(eCharacterAction* const ca) {
    return eVectorHelpers::remove(mCharacterActions, ca);
}

void eGameBoard::registerSoldier(eSoldier* const c) {
    mSoldiers.push_back(c);
}

bool eGameBoard::unregisterSoldier(eSoldier* const c) {
    return eVectorHelpers::remove(mSoldiers, c);
}

void eGameBoard::registerBuilding(eBuilding* const b) {
    if(!mRegisterBuildingsEnabled) return;
    mAllBuildings.push_back(b);
    if(eBuilding::sTimedBuilding(b->type())) {
        mTimedBuildings.push_back(b);
    }
    mTileRenderingOrderUpdateNeeded = true;
    scheduleAppealMapUpdate();
}

bool eGameBoard::unregisterBuilding(eBuilding* const b) {
    if(!mRegisterBuildingsEnabled) return false;
    eVectorHelpers::remove(mAllBuildings, b);
    eVectorHelpers::remove(mTimedBuildings, b);
    mTileRenderingOrderUpdateNeeded = true;
    scheduleAppealMapUpdate();
    return true;
}

void eGameBoard::registerTradePost(eTradePost* const b) {
    if(!mRegisterBuildingsEnabled) return;
    mTradePosts.push_back(b);
    if(mButtonVisUpdater) mButtonVisUpdater();
}

bool eGameBoard::unregisterTradePost(eTradePost* const b) {
    if(!mRegisterBuildingsEnabled) return false;
    const bool r = eVectorHelpers::remove(mTradePosts, b);
    if(r) mButtonVisUpdater();
    return r;
}

bool eGameBoard::hasTradePost(const eWorldCity& city) {
    for(const auto t : mTradePosts) {
        const bool r = &t->city() == &city;
        if(r) return true;
    }
    return false;
}

void eGameBoard::registerSpawner(eSpawner* const s) {
    mSpawners.push_back(s);
}

bool eGameBoard::unregisterSpawner(eSpawner* const s) {
    return eVectorHelpers::remove(mSpawners, s);;
}

void eGameBoard::registerStadium(eBuilding* const s) {
    if(!mRegisterBuildingsEnabled) return;
    mStadium = s;
    if(mButtonVisUpdater) mButtonVisUpdater();
}

void eGameBoard::unregisterStadium() {
    if(!mRegisterBuildingsEnabled) return;
    mStadium = nullptr;
    if(mButtonVisUpdater) mButtonVisUpdater();
}

void eGameBoard::registerStorBuilding(eStorageBuilding* const b) {
    if(!mRegisterBuildingsEnabled) return;
    mStorBuildings.push_back(b);
}

bool eGameBoard::unregisterStorBuilding(eStorageBuilding* const b) {
    if(!mRegisterBuildingsEnabled) return false;
    return eVectorHelpers::remove(mStorBuildings, b);
    return true;
}

void eGameBoard::registerMissile(eMissile* const m) {
    mMissiles.push_back(m);
}

bool eGameBoard::unregisterMissile(eMissile* const m) {
    return eVectorHelpers::remove(mMissiles, m);
}

void eGameBoard::registerPalace(ePalace* const p) {
    if(!mRegisterBuildingsEnabled) return;
    mPalace = p;
    if(mButtonVisUpdater) mButtonVisUpdater();
}

void eGameBoard::unregisterPalace() {
    if(!mRegisterBuildingsEnabled) return;
    mPalace = nullptr;
    if(mButtonVisUpdater) mButtonVisUpdater();
}

void eGameBoard::registerMonster(eMonster* const m) {
    mMonsters.push_back(m);
}

void eGameBoard::unregisterMonster(eMonster* const m) {
    eVectorHelpers::remove(mMonsters, m);
}

void eGameBoard::registerBanner(eBanner* const b) {
    const int id = b->id();
    const auto type = b->type();
    for(const auto b : mBanners) {
        const int bid = b->id();
        if(bid != id) continue;
        const auto btype = b->type();
        if(btype != type) continue;
        delete b;
        break;
    }
    mBanners.push_back(b);
}

void eGameBoard::unregisterBanner(eBanner* const b) {
    eVectorHelpers::remove(mBanners, b);
}

void eGameBoard::incTime(const int by) {
    mThreadPool.handleFinished();
    mThreadPool.scheduleUpdate(*this);

    updateAppealMapIfNeeded();

    const int iMax = mPlannedActions.size() - 1;
    for(int i = iMax; i >= 0; i--) {
        const auto a = mPlannedActions[i];
        a->incTime(by);
        if(a->finished()) {
            mPlannedActions.erase(mPlannedActions.begin() + i);
            delete a;
        }
    }

    if(mTotalTime == 0) {
        grantGeneralRequest(mWorldBoard.cities()[0],
                            eResourceType::fleece, 9, 0);
    }

    mSoldiersUpdate += by;
    const int sup = 2000;
    if(mSoldiersUpdate > sup) {
        mSoldiersUpdate -= sup;
        updateMaxSoldiers();
        distributeSoldiers();
    }

    for(const auto i : mInvasions) {
        i->incTime(by);
    }

    mCoverageUpdate += by;
    const int cup = 2000;
    if(mCoverageUpdate > cup) {
        mCoverageUpdate -= cup;
        updateCoverage();
    }

    mTime += by;
    mTotalTime += by;
    bool nextMonth = false;
    bool nextYear = false;
    const int dayLen = 350;
    const int nd = mTime/dayLen;
    mDate.nextDays(nd, nextMonth, nextYear);
    mTime -= nd*dayLen;

    for(const auto& e : mGameEvents) {
        e->handleNewDate(mDate);
    }

    if(nextYear) {
        const int d = mEmplData.pensions();
        incDrachmas(-d);
    }
    if(nextMonth) {
        mPopData.nextMonth();

        const auto m = mDate.month();
        const int ng = std::abs(mDate.year() % 4);
        const auto game = static_cast<eGames>(ng);
        if(m == eMonth::june) {
            handleGamesBegin(game);
        } else if(m == eMonth::august) {
            handleGamesEnd(game);
        }
    }

    const int ect = 5000;
    mEmploymentCheckTime += by;
    if(mEmploymentCheckTime > ect) {
        mEmploymentCheckTime -= ect;
        const double employable = mEmplData.employable();
        const double jobVacs = mEmplData.totalJobVacancies();
        int emplState = 0;
        if(employable < jobVacs*0.75) {
            emplState = 1;
        } else if(employable > jobVacs*1.25) {
            emplState = -1;
        } else {
            emplState = 0;
        }
        if(mLastEmploymentState != emplState) {
            const auto& inst = eMessages::instance;
            eEventData ed;
            if(emplState == -1) { // unemployed
                showMessage(ed, inst.fUnemployment);
            } else if(emplState == 1) { // employed
                showMessage(ed, inst.fEmployees);
            }
        }
        mLastEmploymentState = emplState;
    }

    mWorldBoard.incTime(by);
    if(nextYear) {
        mWorldBoard.nextYear();
        const auto cs = mWorldBoard.getTribute();
        for(const auto& c : cs) {
            payTribute(c, true);
        }
    }
    const auto chars = mCharacters;
    for(const auto c : chars) {
        if(c->isSoldier()) continue;
        c->incTime(by);
    }
    const auto solds = mSoldiers;
    for(const auto c : solds) {
        c->incTime(by);
    }
    const auto build = mTimedBuildings;
    for(const auto b : build) {
        b->incTime(by);
        if(nextMonth) b->nextMonth();
    }
    for(const auto s : mSpawners) {
        s->incTime(by);
    }

    const auto missiles = mMissiles;
    for(const auto m : missiles) {
        m->incTime(by);
    }

    emptyRubbish();
}

void eGameBoard::incDrachmas(const int d) {
    mDrachmas += d;
}

double eGameBoard::appeal(const int tx, const int ty) const {
    return mAppealMap.heat(tx, ty);
}

double eGameBoard::taxRateF() const {
    return eTaxRateHelpers::getRate(mTaxRate);
}

void eGameBoard::setTaxRate(const eTaxRate tr) {
    mTaxRate = tr;
}

void eGameBoard::setWageRate(const eWageRate wr) {
    mWageRate = wr;
}

void eGameBoard::addRubbish(const stdsptr<eObject>& o) {
    mRubbish.push_back(o);
}

void eGameBoard::emptyRubbish() {
    while(!mRubbish.empty()) {
        std::vector<stdsptr<eObject>> r;
        std::swap(mRubbish, r);
    }
}

void eGameBoard::setEventHandler(const eEventHandler& eh) {
    mEventHandler = eh;
}

void eGameBoard::event(const eEvent e, eEventData& ed) {
    if(mEventHandler) mEventHandler(e, ed);
}

void eGameBoard::setVisibilityChecker(const eVisibilityChecker& vc) {
    mVisibilityChecker = vc;
}

void eGameBoard::setTipShower(const eTipShower& ts) {
    mTipShower = ts;
}

void eGameBoard::showTip(const std::string& tip) {
    if(mTipShower) mTipShower(tip);
}

bool eGameBoard::ifVisible(eTile* const tile, const eAction& func) const {
    if(!tile) return false;
    if(!mVisibilityChecker) return false;
    const bool r = mVisibilityChecker(tile);
    if(r) func();
    return r;
}

void eGameBoard::setMessageShower(const eMessageShower& msg) {
    mMsgShower = msg;
}

void eGameBoard::showMessage(eEventData& ed,
                             const eMessageType& msg) {
    mMsgShower(ed, msg);
}

void eGameBoard::requestTileRenderingOrderUpdate() {
    mTileRenderingOrderUpdateNeeded = true;
}

void eGameBoard::updateNeighbours() {
    for(int x = 0; x < mWidth; x++) {
        for(int y = 0; y < mHeight; y++) {
            const auto t = mTiles[x][y];
            {
                const int dx = y % 2 == 0 ? -1 : 0;
                t->setTopLeft(dtile(x + dx, y - 1));
                t->setBottomLeft(dtile(x + dx, y + 1));
            }
            {
                const int dx = y % 2 == 0 ? 0 : 1;
                t->setTopRight(dtile(x + dx, y - 1));
                t->setBottomRight(dtile(x + dx, y + 1));
            }
        }
    }
}

void eGameBoard::updateResources() {
    for(auto& r : mResources) {
        int& count = r.second;
        count = 0;
        const auto type = r.first;
        for(const auto s : mStorBuildings) {
            count += s->count(type);
        }
    }
}

int eGameBoard::resourceCount(const eResourceType type) const {
    if(type == eResourceType::drachmas) {
        return mDrachmas;
    }
    for(auto& r : mResources) {
        if(r.first == type) return r.second;
    }
    return 0;
}

int eGameBoard::takeResource(const eResourceType type, const int count) {
    if(type == eResourceType::drachmas) {
        mDrachmas -= count;
        return count;
    }
    int r = 0;
    for(const auto s : mStorBuildings) {
        if(r >= count) return count;
        r += s->take(type, count - r);
    }
    return count - r;
}

int eGameBoard::eliteHouses() const {
    int r = 0;
    for(const auto b : mTimedBuildings) {
        const auto bt = b->type();
        if(bt == eBuildingType::eliteHousing) r++;
    }
    return r;
}

eSanctuary* eGameBoard::sanctuary(const eGodType god) const {
    for(const auto s : mSanctuaries) {
        if(s->godType() == god) return s;
    }
    return nullptr;
}

int eGameBoard::countBanners(const eBannerType bt) const {
    int c = 0;
    for(const auto& bn : mSoldierBanners) {
        const int pid = bn->playerId();
        if(pid != 1) continue;
        if(bn->type() != bt) continue;
        c++;
    }
    return c;
}
