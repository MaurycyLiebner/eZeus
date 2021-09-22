#include "eelitehousing.h"

#include "engine/egameboard.h"

#include "textures/egametextures.h"

const int gMaxPeople[] = {6, 6, 10, 16, 20};

eEliteHousing::eEliteHousing(eGameBoard& board) :
    eBuilding(board, eBuildingType::eliteHousing, 4, 4) {
    auto& popData = getBoard().populationData();
    popData.incVacancies(gMaxPeople[0]);
}

eEliteHousing::~eEliteHousing() {
    auto& popData = getBoard().populationData();
    popData.incPopulation(-mPeople);
    popData.incVacancies(-vacancies());
}

std::shared_ptr<eTexture>
eEliteHousing::getLeftTexture(const eTileSize size) const {
    const auto& coll = getTextureCollection(size);
    const int id = seed() % 2;
    return coll.getTexture(id);
}

std::shared_ptr<eTexture>
eEliteHousing::getBottomTexture(const eTileSize size) const {
    const auto& coll = getTextureCollection(size);
    return coll.getTexture(2);
}

std::shared_ptr<eTexture>
eEliteHousing::getTopTexture(const eTileSize size) const {
    const auto& coll = getTextureCollection(size);
    return coll.getTexture(3);
}

std::shared_ptr<eTexture>
eEliteHousing::getRightTexture(const eTileSize size) const {
    const auto& coll = getTextureCollection(size);
    return coll.getTexture(4);
}

std::vector<eOverlay>
eEliteHousing::getHorseOverlays(const eTileSize size) const {
    if(mLevel < 3 || mHorses < 1) return {};
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];

    const auto& coll = texs.fEliteHouseHorses;
    eOverlay h;
    h.fX = -2.0;
    h.fY = -2.5;
    h.fTex = coll.getTexture(mHorses - 1);
    return {h};
}

int eEliteHousing::provide(const eProvide p, const int n) {
    if(mPeople <= 0) return 0;
    int max = 8;
    int* value = nullptr;
    switch(p) {
    case eProvide::food:
        value = &mFood;
        max = 2*(16 + mPeople + mHorses);
        break;
    case eProvide::fleece:
        value = &mFleece;
        break;
    case eProvide::oil:
        value = &mOil;
        break;
    case eProvide::wine:
        value = &mWine;
        break;
    case eProvide::arms:
        max = 4;
        value = &mArms;
        break;
    case eProvide::horses:
        max = 4;
        value = &mHorses;
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
        const double tax = mPeople * taxMult * b.taxRateF();
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

void eEliteHousing::timeChanged(const int by) {
    const int t = time();
    const bool ul = t % 1000 < by;
    if(ul) updateLevel();
    eBuilding::timeChanged(by);
}

void eEliteHousing::nextMonth() {
    mPaidTaxes = false;
    const int cfood = round((mPeople + mHorses)*0.25);
    const int cfleece = 2;
    const int coil = 2;
    const int cwine = mLevel > 1 ? 2 : 0;
    mFood = std::max(0, mFood - cfood);
    mFleece = std::max(0, mFleece - cfleece);
    mOil = std::max(0, mOil - coil);
    if(mLevel > 2) mWine = std::max(0, mWine - cwine);
}

void eEliteHousing::levelUp() {
    setLevel(mLevel + 1);
}

void eEliteHousing::levelDown() {
    setLevel(mLevel - 1);
}

int eEliteHousing::vacancies() const {
    return gMaxPeople[mLevel] - mPeople;
}

int eEliteHousing::moveIn(int c) {
    c = std::clamp(c, 0, vacancies());
    setPeople(mPeople + c);
    return c;
}

bool eEliteHousing::lowFood() const {
    if(!mFood) return true;
    const int cfood = round((mPeople + mHorses)*0.25);
    return mFood < cfood;
}

const eTextureCollection& eEliteHousing::getTextureCollection(
        const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    if(mPeople <= 0) return blds.fEliteHouse[0];
    return blds.fEliteHouse[mLevel + 1];
}

void eEliteHousing::updateLevel() {
    const auto& b = getBoard();
    const auto t = centerTile();
    const int tx = t->x();
    const int ty = t->y();
    const double appeal = b.appeal(tx ,ty);
    const int stadium = b.hasStadium() ? 1 : 0;
    const int nVenues = mPhilosophers + mActors +
                        mAthletes + stadium;
    if(mFood > 0 && mFleece > 0 && mOil > 0 && nVenues > 2 && appeal > 5.0) {
        if(mArms > 0 && appeal > 7.0) {
            if(mWine > 0 && appeal > 9.0) {
                if(mHorses > 0 && nVenues > 3 && appeal > 10.0) {
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

void eEliteHousing::setLevel(const int l) {
    if(mLevel == l) return;

    const int ov = vacancies();
    mLevel = std::clamp(l, 0, 4);
    const int nv = vacancies();

    auto& popData = getBoard().populationData();
    popData.incVacancies(nv - ov);

    evict();
}

int eEliteHousing::evict() {
    const int e = -vacancies();
    if(e <= 0) return 0;
    setPeople(mPeople - e);
    return e;
}

void eEliteHousing::setPeople(const int p) {
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
