#include "egameboard.h"

#include <random>

#include "characters/echaracter.h"
#include "buildings/ebuilding.h"
#include "spawners/espawner.h"

#include "buildings/estoragebuilding.h"

#include "characters/gods/eathena.h"
#include "characters/gods/edemeter.h"
#include "characters/gods/edionysus.h"
#include "characters/actions/egodvisitaction.h"

eGameBoard::eGameBoard(eThreadPool* const tpool) :
    mThreadPool(tpool), mEmplData(mPopData, *this) {}

eGameBoard::~eGameBoard() {
    clear();
}

void eGameBoard::initialize(const int w, const int h) {
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

eTile* eGameBoard::tile(const int x, const int y) const {
    if(x < 0 || x >= mWidth) return nullptr;
    if(y < 0 || y >= mHeight) return nullptr;
    return mTiles[x][y];
}

void eGameBoard::registerCharacter(eCharacter* const c) {
    mCharacters.push_back(c);
}

bool eGameBoard::unregisterCharacter(eCharacter* const c) {
    const auto it = std::find(mCharacters.begin(), mCharacters.end(), c);
    if(it == mCharacters.end()) return false;
    mCharacters.erase(it);
    return true;
}

void eGameBoard::registerBuilding(eBuilding* const b) {
    mBuildings.push_back(b);
}

bool eGameBoard::unregisterBuilding(eBuilding* const b) {
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

void eGameBoard::registerPalace() {
    mPalaceCount++;
}

void eGameBoard::unregisterPalace() {
    mPalaceCount--;
}

void eGameBoard::incTime(const int by) {
    mTime += by;
    bool nextMonth = false;
    bool nextYear = false;
    if(mTime > 250) {
        mDate.nextDay(nextMonth, nextYear);
        mTime = 0;
    }
    const auto chars = mCharacters;
    for(const auto c : chars) {
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
        a->appear();
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

void eGameBoard::addRubbish(const stdsptr<eObject>& o) {
    mRubbish.push_back(o);
}

void eGameBoard::emptyRubbish() {
    mRubbish.clear();
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
