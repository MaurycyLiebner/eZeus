#include "ehousebase.h"

#include "engine/egameboard.h"

#include "characters/esettler.h"
#include "characters/actions/emovetoaction.h"
#include "characters/actions/ekillcharacterfinishfail.h"

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
    auto& board = getBoard();
    auto& popData = board.populationData();
    board.incPopulation(-mPeople);
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
        mCompetitors = std::max(0, mCompetitors - 1);
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

void eHouseBase::leave() {
    if(mPeople <= 0) return;
    auto& board = getBoard();
    auto& popData = board.populationData();
    popData.incLeft(mPeople);
    setPeople(0);

    const auto c = e::make_shared<eSettler>(getBoard());
    c->changeTile(centerTile());
    const stdptr<eSettler> cptr(c.get());
    const auto fail = std::make_shared<eKillCharacterFinishFail>(
                          board, c.get());
    const auto finish = std::make_shared<eKillCharacterFinishFail>(
                            board, c.get());

    const auto a = e::make_shared<eMoveToAction>(c.get());
    a->setFailAction(fail);
    a->setFinishAction(finish);
    a->setFindFailAction([cptr]() {
        if(cptr) cptr->kill();
    });
    c->setAction(a);
    c->setActionType(eCharacterActionType::walk);
    const int bw = board.width();
    const int bh = board.height();
    const auto edgeTile = [bw, bh](eTileBase* const tile) {
        const int tx = tile->dx();
        if(tx == 0 || tx >= bw) return true;
        const int ty = tile->dy();
        if(ty == 0 || ty >= bh) return true;
        return false;
    };
    a->start(edgeTile);
}

int eHouseBase::vacancies() const {
    return mMaxPeople[mLevel] - mPeople;
}

void eHouseBase::read(eReadStream& src) {
    eBuilding::read(src);

    src >> mPaidTaxes;
    src >> mPaidTaxesLastMonth;

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
    src >> mCompetitors;

    src >> mUpdateCulture;
}

void eHouseBase::write(eWriteStream& dst) const {
    eBuilding::write(dst);

    dst << mPaidTaxes;
    dst << mPaidTaxesLastMonth;

    dst << mLevel;
    dst << mPeople;

    dst << mFood;
    dst << mFleece;
    dst << mOil;

    dst << mPhilosophers;
    dst << mActors;
    dst << mAthletes;
    dst << mCompetitors;

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
    if(p == 0) setOnFire(false);
    if(p == mPeople) return;

    auto& board = getBoard();
    auto& popData = board.populationData();

    const int pc = p - mPeople;
    board.incPopulation(pc);

    const int vb = vacancies();
    mPeople = p;
    const int va = vacancies();

    const int vc = va - vb;
    popData.incVacancies(vc);
}
