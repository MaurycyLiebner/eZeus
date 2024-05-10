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

void eHouseBase::timeChanged(const int by) {
    if(mPeople <= 0) return;
    const int cupdate = 5000;
    mUpdateCulture += by;
    if(mUpdateCulture > cupdate) {
        mUpdateCulture -= cupdate;
        mPhilosophers = std::max(0, mPhilosophers - 1);
        mActors = std::max(0, mActors - 1);
        mAthletes = std::max(0, mAthletes - 1);
    }
    eBuilding::timeChanged(by);
}

void eHouseBase::levelUp() {
    setLevel(mLevel + 1);
}

void eHouseBase::levelDown() {
    setLevel(mLevel - 1);
}

int eHouseBase::kill(int k) {
    k = std::clamp(k, 0, mPeople);
    setPeople(mPeople - k);
    return k;
}

int eHouseBase::moveIn(int c) {
    c = std::clamp(c, 0, vacancies());
    setPeople(mPeople + c);
    return c;
}

int eHouseBase::vacancies() const {
    return mMaxPeople[mLevel] - mPeople;
}

void eHouseBase::read(eReadStream& src) {
    eBuilding::read(src);

    src >> mPaidTaxes;

    int level;
    src >> level;
    setLevel(level);
    int people;
    src >> people;
    setPeople(people);

    src >> mFood;
    src >> mFleece;
    src >> mOil;

    src >> mPhilosophers;
    src >> mActors;
    src >> mAthletes;

    src >> mUpdateCulture;
}

void eHouseBase::write(eWriteStream& dst) const {
    eBuilding::write(dst);

    dst << mPaidTaxes;

    dst << mLevel;
    dst << mPeople;

    dst << mFood;
    dst << mFleece;
    dst << mOil;

    dst << mPhilosophers;
    dst << mActors;
    dst << mAthletes;

    dst << mUpdateCulture;
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
