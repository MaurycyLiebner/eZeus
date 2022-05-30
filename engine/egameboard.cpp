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

#include "buildings/sanctuaries/esanctbuilding.h"

#include "engine/boardData/eappealupdatetask.h"

#include "missiles/emissile.h"

eGameBoard::eGameBoard() :
    mEmplData(mPopData, *this) {}

eGameBoard::~eGameBoard() {
    clear();
}

void eGameBoard::initialize(const int w, const int h) {
    mThreadPool.initialize(w, h);

    const int dim = 25;
    for(int x = 0; x < w; x += dim) {
        const int ww = std::clamp(w - x, 0, dim);
        for(int y = 0; y < h; y += dim) {
            const int hh = std::clamp(h - y, 0, dim);
            mUpdateRects.emplace_back(SDL_Rect{x, y, ww, hh});
        }
    }

    clear();
    mTiles.reserve(w);
    for(int x = 0; x < w; x++) {
        std::vector<eTile*> yArr;
        yArr.reserve(h);
        for(int y = 0; y < h; y++) {
            const auto tile = new eTile(x, y);
            yArr.push_back(tile);
        }
        mTiles.push_back(yArr);
    }
    mWidth = w;
    mHeight = h;

    mAppealMap.initialize(w, h);

    updateDiagonalArray();
    updateNeighbours();
}

void eGameBoard::clear() {
    for(const auto& x : mTiles) {
        for(const auto y : x) {
            delete y;
        }
    }
    mTiles.clear();
    mDiagTiles.clear();
    mWidth = 0;
    mHeight = 0;
}

void eGameBoard::iterateOverAllTiles(const eTileAction& a) {
    const auto iniIt = eGameBoardDiagonalIterator(0, 0, this);
    for(auto it = iniIt; it != dEnd(); ++it) {
        a(*it);
    }
}

void eGameBoard::updateAppealMap() {
    const auto task = new eAppealUpdateTask([this](eAppealMap& map) {
        std::swap(appealMap(), map);
    });
    mThreadPool.queueTask(task);
}

void eGameBoard::clearSoldierSelection() {
    for(const auto s : mSelectedSoldiers) {
        s->setSelected(false);
    }
    mSelectedSoldiers.clear();
}

void eGameBoard::deselectSoldier(eSoldier* const c) {
    const auto it = std::find(mSelectedSoldiers.begin(),
                              mSelectedSoldiers.end(), c);
    if(it != mSelectedSoldiers.end()) {
        mSelectedSoldiers.erase(it);
    }
    c->setSelected(false);
}

void eGameBoard::selectSoldier(eSoldier* const c) {
    mSelectedSoldiers.push_back(c);
    c->setSelected(true);
}

void eGameBoard::updateTileRenderingOrder() {
    const auto updateRenderingOrder = [&](eTile* const tile) {
        tile->terrainTiles().clear();
        int fx = 0;
        int fy = 0;
        const auto ubt = tile->underBuildingType();
        const auto ub = tile->underBuilding();
        const auto sc = dynamic_cast<eSanctBuilding*>(ub);
        const bool r = sc && sc->progress() == 0;
        if(r || eBuilding::sFlatBuilding(ubt)) {
            const int tx = tile->x();
            const int ty = tile->y();

            int tty = ty;
            bool found = false;
            eTile* lastT = nullptr;
            for(int i = 0; i < 3 && !found; i++) {
                tty--;
                const int w = ty - tty + 1;
                int tttx = tx;
                int ttty = tty;
                for(int j = 0; j < w && !found; j++) {
                    const auto t = eGameBoard::tile(tttx, ttty);
                    tttx--;
                    ttty++;
                    if(!t) continue;
                    lastT = t;
                    if(t->x() + t->y() <= fx + fy) {
                        if(t->x() <= fx) found = true;
                    }
                    const auto tubt = t->underBuildingType();
                    if(!eBuilding::sFlatBuilding(tubt)) {
                        found = true;
                    }
                }
            }

            if(lastT) {
                lastT->addTerrainTile(tile);
                fx = lastT->x();
                fy = lastT->y();
            }
        }
    };

    iterateOverAllTiles([&](eTile* const tile) {
        updateRenderingOrder(tile);
    });
}

void eGameBoard::updateTileRenderingOrderIfNeeded() {
    if(mTileRenderingOrderUpdateNeeded) {
        updateTileRenderingOrder();
        mTileRenderingOrderUpdateNeeded = false;
    }
}

eTile* eGameBoard::tile(const int x, const int y) const {
    if(x < 0 || x >= mWidth) return nullptr;
    if(y < 0 || y >= mHeight) return nullptr;
    return mTiles[x][y];
}

void eGameBoard::registerCharacter(eCharacter* const c) {
    mCharacters.push_back(c);
}

bool eGameBoard::unregisterCharacter(eCharacter* const c) {
    {
        const auto it = std::find(mSelectedSoldiers.begin(),
                                  mSelectedSoldiers.end(), c);
        if(it != mSelectedSoldiers.end()) {
            mSelectedSoldiers.erase(it);
        }
    }
    const auto it = std::find(mCharacters.begin(),
                              mCharacters.end(), c);
    if(it == mCharacters.end()) return false;
    mCharacters.erase(it);
    return true;
}

void eGameBoard::registerSoldier(eCharacter* const c) {
    mSoldiers.push_back(c);
}

bool eGameBoard::unregisterSoldier(eCharacter* const c) {
    const auto it = std::find(mSoldiers.begin(), mSoldiers.end(), c);
    if(it == mSoldiers.end()) return false;
    mSoldiers.erase(it);
    return true;
}

void eGameBoard::registerBuilding(eBuilding* const b) {
    mTileRenderingOrderUpdateNeeded = true;
    mBuildings.push_back(b);
}

bool eGameBoard::unregisterBuilding(eBuilding* const b) {
    mTileRenderingOrderUpdateNeeded = true;
    const auto it = std::find(mBuildings.begin(), mBuildings.end(), b);
    if(it == mBuildings.end()) return false;
    mBuildings.erase(it);
    return true;
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

void eGameBoard::registerStadium() {
    mStadiumCount++;
}

void eGameBoard::unregisterStadium() {
    mStadiumCount--;
}

void eGameBoard::registerStorBuilding(eStorageBuilding* const b) {
    mStorBuildings.push_back(b);
}

bool eGameBoard::unregisterStorBuilding(eStorageBuilding* const b) {
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

void eGameBoard::registerPalace() {
    mPalaceCount++;
}

void eGameBoard::unregisterPalace() {
    mPalaceCount--;
}

void eGameBoard::incTime(const int by) {
    mThreadPool.handleFinished();
    if(mUpdateRects.empty()) {
        const int w = width();
        const int h = height();
        mThreadPool.scheduleUpdate(*this, 0, 0, w, h);
    } else {
        const int i = (mUpdateRect++) % mUpdateRects.size();
        const auto& rect = mUpdateRects[i];
        mThreadPool.scheduleUpdate(*this, rect.x, rect.y, rect.w, rect.h);
    }

    mTime += by;
    bool nextMonth = false;
    bool nextYear = false;
    if(mTime > 250) {
        mDate.nextDay(nextMonth, nextYear);
        mTime = 0;
    }
    if(nextYear) {
        mDrachmas -= mEmplData.pensions();
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

void eGameBoard::updateDiagonalArray() {
    for(int k = 0 ; k <= mWidth + mHeight - 2; k++) {
        std::vector<eTile*> diag;
        for(int j = k ; j >= 0 ; j--) {
            const int i = k - j;
            if(i < mWidth && j < mHeight) {
                diag.push_back(mTiles[i][j]);
            }
        }
        mDiagTiles.push_back(diag);
    }
}

void eGameBoard::updateNeighbours() {
    for(int x = 0; x < mWidth; x++) {
        for(int y = 0; y < mHeight; y++) {
            const auto t = mTiles[x][y];
            t->setTopLeft(tile(x - 1, y));
            t->setTopRight(tile(x, y - 1));
            t->setBottomRight(tile(x + 1, y));
            t->setBottomLeft(tile(x, y + 1));
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
