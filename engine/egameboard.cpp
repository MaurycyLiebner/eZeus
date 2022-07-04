#include "egameboard.h"

#include <random>

#include "characters/echaracter.h"
#include "buildings/ebuilding.h"
#include "spawners/espawner.h"

#include "buildings/estoragebuilding.h"

#include "characters/gods/eathena.h"
#include "characters/gods/edemeter.h"
#include "characters/gods/edionysus.h"
#include "characters/gods/ehermes.h"
#include "characters/actions/egodvisitaction.h"

#include "characters/esoldier.h"
#include "characters/actions/esoldieraction.h"
#include "characters/erockthrower.h"
#include "characters/ehoplite.h"
#include "characters/ehorseman.h"
#include "characters/esoldierbanner.h"

#include "buildings/sanctuaries/esanctbuilding.h"
#include "buildings/etradepost.h"

#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"

#include "buildings/epalace.h"
#include "buildings/epalacetile.h"

#include "engine/boardData/eappealupdatetask.h"

#include "missiles/emissile.h"

#include "etilehelper.h"

#include "emessages.h"

eGameBoard::eGameBoard() :
    mEmplData(mPopData, *this) {
    const int min = static_cast<int>(eBuildingMode::road);
    const int max = static_cast<int>(eBuildingMode::templeZeus);
    for(int i = min; i <= max; i++) {
        const auto bm = static_cast<eBuildingMode>(i);
        mSupportedBuildings.push_back(bm);
    }
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
    const auto task = new eAppealUpdateTask([this](eAppealMap& map) {
        std::swap(appealMap(), map);
    });
    mThreadPool.queueTask(task);
}

void eGameBoard::clearSoldierSelection() {
    for(const auto s : mSelectedBanners) {
        s->setSelected(false);
    }
    mSelectedBanners.clear();
}

void eGameBoard::deselectSoldier(eSoldierBanner* const c) {
    const auto it = std::find(mSelectedBanners.begin(),
                              mSelectedBanners.end(), c);
    if(it != mSelectedBanners.end()) {
        mSelectedBanners.erase(it);
    }
    c->setSelected(false);
}

void eGameBoard::selectSoldier(eSoldierBanner* const c) {
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
    mButtonVisUpdater();
}

void eGameBoard::removeSupportedBuilding(const eBuildingMode t) {
    const auto it = std::find(mSupportedBuildings.begin(),
                              mSupportedBuildings.end(), t);
    if(it == mSupportedBuildings.end()) return;
    mSupportedBuildings.erase(it);
    mButtonVisUpdater();
}

bool eGameBoard::supportsBuilding(const eBuildingMode t) const {
    const auto it = std::find(mSupportedBuildings.begin(),
                              mSupportedBuildings.end(), t);
    const bool s = it != mSupportedBuildings.end();
    return s;
}

eBuilding* eGameBoard::randomBuilding(const eBuildingValidator& v) const {
    auto blds = mBuildings;
    std::random_shuffle(blds.begin(), blds.end());
    for(const auto b : blds) {
        const bool r = v(b);
        if(r) return b;
    }
    return nullptr;
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
    for(const auto b : mBuildings) {
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
            if(l < 1) continue;
            const int a = eh->arms();
            if(l == 1) {
                mMaxHoplites += std::min(2, a);
            } else if(l == 2) {
                mMaxHoplites += std::min(4, a);
            } else if(l == 3) {
                const int h = eh->horses();
                const int hh = std::min(std::min(a, 4), h);
                mMaxHorsemen += hh;
                mMaxHoplites += std::min(4 - hh, a - hh);
            }
            else if(l == 3) mMaxRockThrowers += 6;
            else if(l == 4) mMaxRockThrowers += 10;
            else if(l == 5) mMaxRockThrowers += 12;
            else if(l == 6) mMaxRockThrowers += 15;
        }
    }
    mMaxRockThrowers /= 6;
}

void eGameBoard::addSoldier(const eCharacterType st) {
    bool found = false;
    for(const auto& b : mBanners) {
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
    registerBanner(b);
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
    for(const auto& b : mBanners) {
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
                unregisterBanner(b);
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
    for(const auto& b : mBanners) {
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

void eGameBoard::registerBanner(const stdsptr<eSoldierBanner>& b) {
    mBanners.push_back(b);
}

bool eGameBoard::unregisterBanner(const stdsptr<eSoldierBanner>& b) {
    const auto it = std::find(mBanners.begin(), mBanners.end(), b);
    if(it == mBanners.end()) return false;
    mBanners.erase(it);
    return true;
}

void eGameBoard::updateCoverage() {
    int people = 0;
    int sport = 0;
    int phil = 0;
    int drama = 0;
    for(const auto b : mBuildings) {
        if(const auto h = dynamic_cast<eHouseBase*>(b)) {
            const int p = h->people();
            if(h->athletes() > 0) {
                sport += p;
            } else if(h->philosophers() > 0) {
                phil += p;
            } else if(h->actors() > 0) {
                drama += p;
            }
            people += p;
        }
    }
    if(people <= 0) {
        mSportCoverage = 0;
        mPhilosophyCoverage = 0;
        mDramaCoverage = 0;
    } else {
        mSportCoverage = 100*sport/people;
        mPhilosophyCoverage = 100*phil/people;
        mDramaCoverage = 100*drama/people;
    }
    mAllDiscCoverage = (mSportCoverage + mPhilosophyCoverage + mDramaCoverage)/3;
}

void eGameBoard::handleGamesBegin(const eGames game) {
    switch(game) {
    case eGames::isthmian:
        showMessage(nullptr, eMessages::instance.fIsthmianGames.fBegin);
        break;
    case eGames::nemean:
        showMessage(nullptr, eMessages::instance.fNemeanGames.fBegin);
        break;
    case eGames::pythian:
        showMessage(nullptr, eMessages::instance.fPythianGames.fBegin);
        break;
    case eGames::olympian:
        showMessage(nullptr, eMessages::instance.fOlympianGames.fBegin);
        break;
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
        coverage = mSportCoverage;
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

    double mult;
    const int pop = mPopData.population();

    if(pop < 250) mult = 0.25;
    else if(pop < 500) mult = 0.5;
    else if(pop < 1000) mult = 0.75;
    else mult = 1.;

    if(mult*coverage < 35) {
        showMessage(nullptr, msgs->fNoPart);
    } else {
        const double coveragef = coverage/100.;
        const double chance = mult*coveragef*coveragef;
        const bool won = rand() % 101 < 100*chance;
        if(won) {
            showMessage(nullptr, msgs->fWon);
        } else {
            const bool second = rand() % 101 < 100*chance;
            if(second) {
                showMessage(nullptr, msgs->fSecond);
            } else {
                showMessage(nullptr, msgs->fLost);
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
    const auto it = std::find(mCharacters.begin(),
                              mCharacters.end(), c);
    if(it == mCharacters.end()) return false;
    mCharacters.erase(it);
    return true;
}

void eGameBoard::registerSoldier(eSoldier* const c) {
    mSoldiers.push_back(c);
}

bool eGameBoard::unregisterSoldier(eSoldier* const c) {
    const auto it = std::find(mSoldiers.begin(), mSoldiers.end(), c);
    if(it == mSoldiers.end()) return false;
    mSoldiers.erase(it);
    return true;
}

void eGameBoard::registerBuilding(eBuilding* const b) {
    if(!mRegisterBuildingsEnabled) return;
    mTileRenderingOrderUpdateNeeded = true;
    mBuildings.push_back(b);
    scheduleAppealMapUpdate();
}

bool eGameBoard::unregisterBuilding(eBuilding* const b) {
    if(!mRegisterBuildingsEnabled) return false;
    mTileRenderingOrderUpdateNeeded = true;
    const auto it = std::find(mBuildings.begin(), mBuildings.end(), b);
    if(it == mBuildings.end()) return false;
    mBuildings.erase(it);
    scheduleAppealMapUpdate();
    return true;
}

void eGameBoard::registerTradePost(eTradePost* const b) {
    if(!mRegisterBuildingsEnabled) return;
    mTradePosts.push_back(b);
    mButtonVisUpdater();
}

bool eGameBoard::unregisterTradePost(eTradePost* const b) {
    if(!mRegisterBuildingsEnabled) return false;
    const auto it = std::find(mTradePosts.begin(), mTradePosts.end(), b);
    if(it == mTradePosts.end()) return false;
    mTradePosts.erase(it);
    mButtonVisUpdater();
    return true;
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
    const auto it = std::find(mSpawners.begin(), mSpawners.end(), s);
    if(it == mSpawners.end()) return false;
    mSpawners.erase(it);
    return true;
}

void eGameBoard::registerStadium(eBuilding* const s) {
    if(!mRegisterBuildingsEnabled) return;
    mStadium = s;
    mButtonVisUpdater();
}

void eGameBoard::unregisterStadium() {
    if(!mRegisterBuildingsEnabled) return;
    mStadium = nullptr;
    mButtonVisUpdater();
}

void eGameBoard::registerStorBuilding(eStorageBuilding* const b) {
    if(!mRegisterBuildingsEnabled) return;
    mStorBuildings.push_back(b);
}

bool eGameBoard::unregisterStorBuilding(eStorageBuilding* const b) {
    if(!mRegisterBuildingsEnabled) return false;
    const auto it = std::find(mStorBuildings.begin(), mStorBuildings.end(), b);
    if(it == mStorBuildings.end()) return false;
    mStorBuildings.erase(it);
    return true;
}

void eGameBoard::registerMissile(eMissile* const m) {
    mMissiles.push_back(m);
}

bool eGameBoard::unregisterMissile(eMissile* const m) {
    const auto it = std::find(mMissiles.begin(), mMissiles.end(), m);
    if(it == mMissiles.end()) return false;
    mMissiles.erase(it);
    return true;
}

void eGameBoard::registerPalace(ePalace* const p) {
    if(!mRegisterBuildingsEnabled) return;
    mPalace = p;
    mButtonVisUpdater();
}

void eGameBoard::unregisterPalace() {
    if(!mRegisterBuildingsEnabled) return;
    mPalace = nullptr;
    mButtonVisUpdater();
}

void eGameBoard::incTime(const int by) {
    mThreadPool.handleFinished();
    mThreadPool.scheduleUpdate(*this);

    updateAppealMapIfNeeded();

    mSoldiersUpdate += by;
    const int sup = 2000;
    if(mSoldiersUpdate > sup) {
        mSoldiersUpdate -= sup;
        updateMaxSoldiers();
        distributeSoldiers();
    }

    mCoverageUpdate += by;
    const int cup = 2000;
    if(mCoverageUpdate > cup) {
        mCoverageUpdate -= cup;
        updateCoverage();
    }

    mTime += by;
    bool nextMonth = false;
    bool nextYear = false;
    const int dayLen = 350;
    while(mTime > dayLen) {
        bool nm;
        bool ny;
        mDate.nextDay(nm, ny);
        nextMonth = nm || nextMonth;
        nextYear = ny || nextYear;
        mTime -= dayLen;
    }
    if(nextYear) {
        const int d = mEmplData.pensions();
        incDrachmas(-d);
    }
    if(nextMonth) {
        const auto m = mDate.month();
        const int ng = std::abs(mDate.year() % 4);
        const auto game = static_cast<eGames>(ng);
        if(m == eMonth::june) {
            handleGamesBegin(game);
        } else if(m == eMonth::august) {
            handleGamesEnd(game);
        }
    }
    mWorldBoard.incTime(by);
    if(nextYear) mWorldBoard.nextYear();
    const auto chars = mCharacters;
    for(const auto c : chars) {
        if(c->isSoldier()) continue;
        c->incTime(by);
    }
    const auto solds = mSoldiers;
    for(const auto c : solds) {
        c->incTime(by);
    }
    const auto build = mBuildings;
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

    if(rand() % 100000 < by) {
        stdsptr<eCharacter> god;
        eEvent e;
        const int r = rand() % 14;
        if(r == 0) {
            god = e::make_shared<eAphrodite>(*this);
            e = eEvent::aphroditeVisit;
        } else if(r == 1) {
            god = e::make_shared<eApollo>(*this);
            e = eEvent::apolloVisit;
        } else if(r == 2) {
            god = e::make_shared<eAres>(*this);
            e = eEvent::aresVisit;
        } else if(r == 3) {
            god = e::make_shared<eArtemis>(*this);
            e = eEvent::artemisVisit;
        } else if(r == 4) {
            god = e::make_shared<eAthena>(*this);
            e = eEvent::athenaVisit;
        } else if(r == 5) {
            god = e::make_shared<eAtlas>(*this);
            e = eEvent::atlasVisit;
        } else if(r == 6) {
            god = e::make_shared<eDemeter>(*this);
            e = eEvent::demeterVisit;
        } else if(r == 7) {
            god = e::make_shared<eDionysus>(*this);
            e = eEvent::dionysusVisit;
        } else if(r == 8) {
            god = e::make_shared<eHades>(*this);
            e = eEvent::hadesVisit;
        } else if(r == 9) {
            god = e::make_shared<eHephaestus>(*this);
            e = eEvent::hephaestusVisit;
        } else if(r == 10) {
            god = e::make_shared<eHera>(*this);
            e = eEvent::heraVisit;
        } else if(r == 11) {
            god = e::make_shared<eHermes>(*this);
            e = eEvent::hermesVisit;
        } else if(r == 12) {
            god = e::make_shared<ePoseidon>(*this);
            e = eEvent::poseidonVisit;
        } else {
            god = e::make_shared<eZeus>(*this);
            e = eEvent::zeusVisit;
        }
        const auto a = e::make_shared<eGodVisitAction>(
                           god.get(), []() {}, []() {});
        god->setAction(a);
        a->increment(1);
        event(e, god->tile());
    }

    emptyRubbish();
}

void eGameBoard::incDrachmas(const int d) {
    mDrachmas += d;
}

double eGameBoard::appeal(const int tx, const int ty) const {
    return mAppealMap.appeal(tx, ty);
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

void eGameBoard::event(const eEvent e, eTile* const tile) {
    if(mEventHandler) mEventHandler(e, tile);
}

void eGameBoard::setVisibilityChecker(const eVisibilityChecker& vc) {
    mVisibilityChecker = vc;
}

bool eGameBoard::ifVisible(eTile* const tile, const eAction& func) const {
    if(!tile) return false;
    if(!mVisibilityChecker) return false;
    const bool r = mVisibilityChecker(tile);
    if(r) func();
    return r;
}

void eGameBoard::showMessage(eTile* const t, const eMessageType& msg) {
    mMsgShower(t, msg);
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
