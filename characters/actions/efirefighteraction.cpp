#include "efirefighteraction.h"

#include "../echaracter.h"
#include "engine/egameboard.h"
#include "emovetoaction.h"
#include "ewaitaction.h"

void eFireFighterAction::increment(const int by) {
    if(!mFireFighting) {
        const int fireCheckInc = 1000;
        mFireCheck += by;
        if(mFireCheck > fireCheckInc) {
            mFireCheck = 0;
            lookForFire();
        }
    }
    ePatrolAction::increment(by);
}

eTile* neighbourOnFire(eTile* const tile, eOrientation& oo) {
    eTile* n = nullptr;
    for(const auto o : {eOrientation::topRight,
                        eOrientation::right,
                        eOrientation::bottomRight,
                        eOrientation::bottom,
                        eOrientation::bottomLeft,
                        eOrientation::left,
                        eOrientation::topLeft,
                        eOrientation::top}) {
        const auto nt = tile->neighbour<eTile>(o);
        if(!nt) continue;
        if(nt->onFire()) {
            oo = o;
            n = nt;
            break;
        }
    }
    return n;
}

bool eFireFighterAction::decide() {
    const auto c = character();
    if(mMoveToFireAction) {
        mFireFighting = true;
        setCurrentAction(mMoveToFireAction);
        mMoveToFireAction = nullptr;
        c->setActionType(eCharacterActionType::carry);
    } else if(mFireFighting) {
        const auto tile = c->tile();
        eOrientation oo;
        eTile* const n = neighbourOnFire(tile, oo);
        if(n && n->onFire()) {
            c->setOrientation(oo);
            putOutFire(n);
        } else {
            mFireFighting = false;
            c->setActionType(eCharacterActionType::walk);
            lookForFire();
        }
    }
    const bool r = ePatrolAction::decide();
    if(r) return r;

    return true;
}

bool eFireFighterAction::lookForFire() {
    const auto c = character();

    const stdptr<eFireFighterAction> tptr(this);
    const auto failFunc = [tptr, this, c]() {
        if(!tptr) return;
        if(mFireFighting) {
            mFireFighting = false;
            c->setActionType(eCharacterActionType::walk);
        }
    };

    const auto onFire = [](eTileBase* const tile) {
        return tile->onFire();
    };

    const auto a = e::make_shared<eMoveToAction>(
                       c, failFunc, [](){});
    a->setFoundAction([tptr, a, this]() {
        if(!tptr) return;
        mMoveToFireAction = a;
    });
    a->setRemoveLastTurn(true);
    a->setWait(false);
    a->start(onFire);

    return true;
}

void eFireFighterAction::putOutFire(eTile* const tile) {
    const auto c = character();
    c->setActionType(eCharacterActionType::fight);
    const auto finish = [this, tile, c]() {
        c->setActionType(eCharacterActionType::stand);
        if(const auto b = tile->underBuilding()) {
            const auto& u = b->tilesUnder();
            for(const auto t : u) {
                t->setOnFire(false);
            }
        } else {
            tile->setOnFire(false);
        }
        lookForFire();
    };
    const auto a = e::make_shared<eWaitAction>(c, []() {}, finish);
    if(tile->underBuilding()) {
        a->setTime(1600);
    } else {
        a->setTime(800);
    }
    setCurrentAction(a);
}
