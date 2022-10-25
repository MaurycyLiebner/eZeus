#include "efirefighteraction.h"

#include "../echaracter.h"
#include "engine/egameboard.h"
#include "emovetoaction.h"
#include "ewaitaction.h"

void eFireFighterAction::increment(const int by) {
    if(mMoveToFireAction) {
        mFireFighting = true;
        setCurrentAction(mMoveToFireAction);
        mMoveToFireAction = nullptr;
        const auto c = character();
        c->setActionType(eCharacterActionType::carry);
    } else if(!mFireFighting) {
        const int fireCheckInc = 1000;
        mFireCheck += by;
        if(mFireCheck > fireCheckInc) {
            mFireCheck -= fireCheckInc;
            const auto c = character();
            auto& brd = c->getBoard();
            const auto ct = c->tile();
            const int tx = ct->x();
            const int ty = ct->y();
            const int range = 10;
            bool found = false;
            for(int i = -range; i <= range && !found; i++) {
                for(int j = -range; j <= range && !found; j++) {
                    const int ttx = tx + i;
                    const int tty = ty + j;
                    const auto t = brd.tile(ttx, tty);
                    if(!t) continue;
                    found = t->onFire();
                }
            }
            if(found) lookForFire();
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
    if(mFireFighting) {
        const auto tile = c->tile();
        eOrientation oo;
        const auto n = neighbourOnFire(tile, oo);
        if(n) {
            c->setOrientation(oo);
            putOutFire(n);
            mUsedWater++;
        } else {
            if(mUsedWater >= 5) {
                c->setActionType(eCharacterActionType::walk);
                goBackDecision(eWalkableHelpers::sDefaultWalkable);
            } else {
                c->setActionType(eCharacterActionType::stand);
                lookForFire();
            }
        }
        return true;
    } else {
        const bool r = ePatrolAction::decide();
        if(r) return r;
    }

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
            goBackDecision(eWalkableHelpers::sDefaultWalkable);
        }
    };

    const auto onFire = [](eTileBase* const tile) {
        return tile->onFire();
    };

    const auto a = e::make_shared<eMoveToAction>(
                       c, failFunc, [](){});
    a->setMaxDistance(50);
    a->setFoundAction([tptr, a, this]() {
        if(!tptr) return;
        mMoveToFireAction = a;
    });
    a->setRemoveLastTurn(true);

    a->setWait(mFireFighting);
    a->start(onFire);

    return true;
}

void eFireFighterAction::putOutFire(eTile* const tile) {
    const auto c = character();
    c->setActionType(eCharacterActionType::fight);
    const auto finish = [tile, c]() {
        c->setActionType(eCharacterActionType::stand);
        if(const auto b = tile->underBuilding()) {
            b->setOnFire(false);
        }
    };
    const auto a = e::make_shared<eWaitAction>(c, []() {}, finish);
    if(tile->underBuilding()) {
        a->setTime(1600);
    } else {
        a->setTime(800);
    }
    setCurrentAction(a);
}
