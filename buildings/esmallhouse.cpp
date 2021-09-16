#include "esmallhouse.h"

#include <algorithm>
#include "textures/egametextures.h"
#include "engine/egameboard.h"

const int gMaxPeople[] = {8, 16, 24, 32, 40, 48, 60};

eSmallHouse::eSmallHouse(eGameBoard& board) :
    eBuilding(board, eBuildingType::commonHouse, 2, 2) {
    auto& popData = getBoard().populationData();
    popData.incVacancies(gMaxPeople[0]);
}

eSmallHouse::~eSmallHouse() {
    auto& popData = getBoard().populationData();
    popData.incPopulation(-mPeople);
    popData.incVacancies(-vacancies());
}

std::shared_ptr<eTexture> eSmallHouse::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    if(mPeople == 0) return blds[sizeId].fHouseSpace;
    const auto& coll = blds[sizeId].fCommonHouse[mLevel];
    const int texId = seed() % coll.size();
    return coll.getTexture(texId);
}

int eSmallHouse::provide(const eProvide p, const int n) {
    if(mPeople <= 0) return 0;
    int max = 8;
    int* value = nullptr;
    switch(p) {
    case eProvide::water:
        value = &mWater;
        break;
    case eProvide::food:
        value = &mFood;
        max = 2*mPeople;
        break;
    case eProvide::fleece:
        value = &mFleece;
        break;
    case eProvide::oil:
        value = &mOil;
        break;

    case eProvide::philosopher:
        value = &mPhilosophers;
        break;
    case eProvide::actor:
        value = &mActors;
        break;
    case eProvide::gymnast:
        value = &mAthletes;
        break;

    case eProvide::taxes: {
        if(mPaidTaxes) return 0;
        mPaidTaxes = true;
        auto& b = getBoard();
        const auto diff = b.difficulty();
        const int taxMult = eDifficultyHelpers::taxMultiplier(
                                diff, type(), mLevel);
        const double tax = mPeople * taxMult * b.taxRate();
        const int iTax = std::round(tax);
        b.incDrachmas(iTax);
        return iTax;
    }
    default:
        return eBuilding::provide(p, n);
    }
    const int add = std::clamp(n, 0, max - *value);
    *value += add;
    updateLevel();
    return add;
}

void eSmallHouse::timeChanged(const int by) {
    const int t = time();
    const bool decw = t % 5000 < by;
    if(decw) mWater = std::max(0, mWater - 1);
    const bool ul = t % 1000 < by;
    if(ul) updateLevel();
    eBuilding::timeChanged(by);
}

void eSmallHouse::nextMonth() {
    mPaidTaxes = false;
    const int cfood = round(mPeople*0.25);
    const int cfleece = mLevel > 2 ? 2 : 0;
    const int coil = mLevel > 4 ? 2 : 0;
    mFood = std::max(0, mFood - cfood);
    mFleece = std::max(0, mFleece - cfleece);
    mOil = std::max(0, mOil - coil);
}

void eSmallHouse::levelUp() {
    setLevel(mLevel + 1);
}

void eSmallHouse::levelDown() {
    setLevel(mLevel - 1);
}

int eSmallHouse::vacancies() const {
    return gMaxPeople[mLevel] - mPeople;
}

int eSmallHouse::moveIn(int c) {
    c = std::clamp(c, 0, vacancies());
    setPeople(mPeople + c);
    return c;
}

void eSmallHouse::updateLevel() {
    const auto& b = getBoard();
    const auto t = centerTile();
    const int tx = t->x();
    const int ty = t->y();
    const double appeal = b.appeal(tx ,ty);
    const int stadium = b.hasStadium() ? 1 : 0;
    const int nVenues = mPhilosophers + mActors +
                        mAthletes + stadium;
    if(mFood > 0) {
        if(mWater > 0 && nVenues > 0) {
            if(mFleece > 0 && appeal > 2.0) {
                if(nVenues > 1) {
                    if(mOil > 0 && appeal > 5.0) {
                        if(nVenues > 2 && appeal > 8.0) {
                            return setLevel(6);
                        }
                        return setLevel(5);
                    }
                    return setLevel(4);
                }
                return setLevel(3);
            }
            return setLevel(2);
        }
        return setLevel(1);
    }
    setLevel(0);
}

void eSmallHouse::setLevel(const int l) {
    if(mLevel == l) return;

    const int ov = vacancies();
    mLevel = std::clamp(l, 0, 6);
    const int nv = vacancies();

    auto& popData = getBoard().populationData();
    popData.incVacancies(nv - ov);

    evict();
}

int eSmallHouse::evict() {
    const int e = -vacancies();
    if(e <= 0) return 0;
    setPeople(mPeople - e);
    return e;
}

void eSmallHouse::setPeople(const int p) {
    if(p == mPeople) return;

    auto& popData = getBoard().populationData();

    const int pc = p - mPeople;
    popData.incPopulation(pc);

    const int vb = vacancies();
    mPeople = p;
    const int va = vacancies();

    const int vc = va - vb;
    popData.incVacancies(vc);
}
