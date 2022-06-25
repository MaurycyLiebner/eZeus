#include "ehousebase.h"

#include "engine/egameboard.h"

eHouseBase::eHouseBase(eGameBoard& board,
                       const eBuildingType type,
                       const int sw, const int sh,
                       const std::vector<int>& maxPeople) :
    eBuilding(board, type, sw, sh),
    mMaxPeople(maxPeople) {
    auto& popData = getBoard().populationData();
    popData.incVacancies(mMaxPeople[0]);
}

eHouseBase::~eHouseBase() {
    auto& popData = getBoard().populationData();
    popData.incPopulation(-mPeople);
    popData.incVacancies(-vacancies());
}

void eHouseBase::levelUp() {
    setLevel(mLevel + 1);
}

void eHouseBase::levelDown() {
    setLevel(mLevel - 1);
}

int eHouseBase::moveIn(int c) {
    c = std::clamp(c, 0, vacancies());
    setPeople(mPeople + c);
    return c;
}

void eHouseBase::setLevel(const int l) {
    if(mLevel == l) return;

    const int ov = vacancies();
    const int maxLevel = mMaxPeople.size();
    mLevel = std::clamp(l, 0, maxLevel);
    const int nv = vacancies();

    auto& popData = getBoard().populationData();
    popData.incVacancies(nv - ov);

    evict();
}

int eHouseBase::vacancies() const {
    return mMaxPeople[mLevel] - mPeople;
}

int eHouseBase::evict() {
    const int e = -vacancies();
    if(e <= 0) return 0;
    setPeople(mPeople - e);
    return e;
}

void eHouseBase::setPeople(const int p) {
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
