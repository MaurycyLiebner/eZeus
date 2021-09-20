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

bool eFireFighterAction::lookForFire() {
    const auto c = character();

    const stdptr<eFireFighterAction> tptr(this);
    const auto failFunc = [tptr, this, c]() {
        if(tptr) {
            if(mFireFighting) {
                mFireFighting = false;
                c->setActionType(eCharacterActionType::walk);
                goBackNoRoad();
            }
        }
    };

    const auto finishAction = [tptr, this, c]() {
        if(!tptr) return;
        const auto tile = c->tile();
        eTile* n = nullptr;
        eOrientation oo;
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
        if(n && n->onFire()) {
            c->setOrientation(oo);
            putOutFire(n);
        } else {
            mFireFighting = false;
            c->setActionType(eCharacterActionType::walk);
            goBackNoRoad();
            lookForFire();
        }
    };

    const auto onFire = [](eTileBase* const tile) {
        return tile->onFire();
    };


    const auto a = e::make_shared<eMoveToAction>(
                       c, failFunc, finishAction);
    a->setFoundAction([tptr, c, a]() {
        if(!tptr) return;
        c->setActionType(eCharacterActionType::carry);
        tptr->setCurrentAction(a);
        tptr->mFireFighting = true;
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
