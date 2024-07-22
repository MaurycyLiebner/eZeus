#include "esettleraction.h"

#include "engine/etile.h"
#include "characters/echaracter.h"
#include "engine/ethreadpool.h"
#include "emovetoaction.h"
#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"
#include "engine/egameboard.h"
#include "ekillcharacterfinishfail.h"

eSettlerAction::eSettlerAction(eCharacter* const c) :
    eActionWithComeback(c, eCharActionType::settlerAction) {
    setFinishOnComeback(true);
}

eSettlerAction::~eSettlerAction() {
    setNumberPeople(0);
}

bool eSettlerAction::decide() {
    if(mNoHouses) {
        const auto c = character();
        const auto ct = c->type();
        if(ct == eCharacterType::settler) {
            goBack2();
        } else {
            leave();
        }
    } else {
        findHouse();
    }
    return true;
}

void eSettlerAction::read(eReadStream& src) {
    eActionWithComeback::read(src);
    int nPeople;
    src >> nPeople;
    setNumberPeople(nPeople);
    src >> mNoHouses;
}

void eSettlerAction::write(eWriteStream& dst) const {
    eActionWithComeback::write(dst);
    dst << mNPeople;
    dst << mNoHouses;
}

void eSettlerAction::setNumberPeople(const int p) {
    auto& board = this->board();
    auto& popData = board.populationData();
    popData.incSettlers(p - mNPeople);
    mNPeople = p;
}

void eSettlerAction::findHouse() {
    if(mNoHouses) return;
    const auto c = character();

    const auto finalTile = [](eThreadTile* const t) {
        const auto ut = t->underBuildingType();
        const bool h = ut == eBuildingType::commonHouse ||
                       ut == eBuildingType::eliteHousing;
        return h && t->houseVacancies() > 0;
    };
    const stdptr<eCharacterAction> tptr(this);
    const auto failFunc = std::make_shared<eSA_findHouseFail>(
                              board(), this);
    const auto finishAction = std::make_shared<eSA_findHouseFinish>(
                                  board(), this);

    c->setActionType(eCharacterActionType::walk);

    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFailAction(failFunc);
    a->setFinishAction(finishAction);
    a->setFindFailAction([tptr, this]() {
        if(!tptr) return;
        mNoHouses = true;
    });
    a->setFoundAction([tptr, this]() {
        if(!tptr) return;
        const auto c = character();
        if(!c) return;
        c->setVisible(true);
    });
    a->setRemoveLastTurn(true);
    a->start(finalTile);
    setCurrentAction(a);
}

void eSettlerAction::goBack2() {
    eActionWithComeback::goBack(eWalkableObject::sCreateDefault());
}

void eSettlerAction::leave() {
    auto& board = eSettlerAction::board();
    const auto c = character();
    const stdptr<eCharacter> cptr(c);
    const auto fail = std::make_shared<eKillCharacterFinishFail>(
                          board, c);
    const auto finish = std::make_shared<eKillCharacterFinishFail>(
                            board, c);

    const auto a = e::make_shared<eMoveToAction>(c);
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

bool eSettlerAction::enterHouse() {
    const auto c = character();
    const auto t = c->tile();
    if(!t) {
        setState(eCharacterActionState::failed);
        return false;
    }
    for(const auto n : {eOrientation::topRight,
                        eOrientation::right,
                        eOrientation::bottomRight,
                        eOrientation::bottom,
                        eOrientation::bottomLeft,
                        eOrientation::left,
                        eOrientation::topLeft,
                        eOrientation::top}) {
        const auto nn = t->neighbour<eTile>(n);
        if(!nn) continue;
        const auto b = nn->underBuilding();
        if(!b) continue;
        const auto t = b->type();
        if(t == eBuildingType::commonHouse) {
            const auto ch = static_cast<eSmallHouse*>(b);
            const int v = ch->vacancies();
            if(v <= 0) continue;
            const int nPeople = mNPeople - ch->moveIn(mNPeople);
            setNumberPeople(nPeople);
            return true;
        } else if(t == eBuildingType::eliteHousing) {
            const auto ch = static_cast<eEliteHousing*>(b);
            const int v = ch->vacancies();
            if(v <= 0) continue;
            const int nPeople = mNPeople - ch->moveIn(mNPeople);
            setNumberPeople(nPeople);
            return true;
        }
    }
    return false;
}
