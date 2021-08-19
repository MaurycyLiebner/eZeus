#include "esmallhouse.h"

#include <algorithm>
#include "textures/egametextures.h"
#include "engine/egameboard.h"

const int gMaxPeople[] = {8, 16, 24, 32, 40, 48, 60};

eSmallHouse::eSmallHouse(eGameBoard& board) :
    eBuilding(board, eBuildingType::commonHouse, 2, 2),
    mTextures(eGameTextures::buildings()) {
    auto& popData = getBoard().populationData();
    popData.incVacancies(gMaxPeople[0]);
}

eSmallHouse::~eSmallHouse() {
    auto& popData = getBoard().populationData();
    popData.incPopulation(-mPeople);
    popData.incVacancies(-vacancies());
}

eTexture eSmallHouse::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    if(mPeople == 0) return mTextures[sizeId].fHouseSpace;
    const auto& coll = mTextures[sizeId].fCommonHouse[mLevel];
    const int texId = seed() % coll.size();
    return coll.getTexture(texId);
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

void eSmallHouse::setLevel(const int l) {
    mLevel = std::clamp(l, 0, 6);
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
