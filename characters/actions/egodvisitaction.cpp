#include "egodvisitaction.h"

#include "characters/echaracter.h"

#include "engine/egameboard.h"

#include "ewaitaction.h"
#include "emovearoundaction.h"
#include "epatrolmoveaction.h"

#include "esounds.h"

#include "characters/echaracter.h"
#include "eiteratesquare.h"

eGodVisitAction::eGodVisitAction(eCharacter* const c,
                                 const eAction& failAction,
                                 const eAction& finishAction) :
    eComplexAction(c, failAction, finishAction),
    mType(eGod::sCharacterToGodType(c->type())) {

}

bool eGodVisitAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eGodVisitStage::none:
        mStage = eGodVisitStage::appear;
        placeOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            if(mType == eGodType::hermes) {
                run();
            } else {
                appear();
            }
        }
        break;
    case eGodVisitStage::appear: {
        mStage = eGodVisitStage::patrol;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodVisitStage::patrol:
        mStage = eGodVisitStage::disappear;
        if(mType == eGodType::hermes) {
            run();
        } else {
            disappear();
        }
        break;
    case eGodVisitStage::disappear:
        c->kill();
        break;
    }
    return true;
}

void eGodVisitAction::placeOnBoard() {
    const auto c = character();
    auto& board = c->getBoard();
    const int w = board.width();
    const int h = board.height();
    const int rdx = rand() % w;
    const int rdy = rand() % h;
    eTile* roadTile = nullptr;
    eTile* plainTile = nullptr;
    const auto prcsTile = [&](const int i, const int j) {
        const int tx = rdx + i;
        const int ty = rdy + j;
        const auto tt = board.dtile(tx, ty);
        if(!tt) return false;
        if(tt->hasRoad()) {
            roadTile = tt;
            return true;
        } else if(!plainTile && tt->walkable()) {
            plainTile = tt;
        }
        return false;
    };

    for(int k = 0; k < 1000; k++) {
        eIterateSquare::iterateSquare(k, prcsTile, 1);
        if(roadTile) break;
    }

    const auto tile = roadTile ? roadTile : plainTile;
    if(!tile) return;
    c->changeTile(tile);
    board.ifVisible(tile, [this]() {
        eSounds::playGodSound(mType, eGodSound::appear);
    });
}

void eGodVisitAction::appear() {
    const auto c = character();
    c->setActionType(eCharacterActionType::appear);
    const auto a = e::make_shared<eWaitAction>(c, [](){}, [](){});
    a->setTime(500);
    setCurrentAction(a);
}

void eGodVisitAction::run() {
    const auto c = character();
    c->setActionType(eCharacterActionType::appear);
    c->setSpeed(2.0);
    const auto tile = c->tile();
    const auto finish = [c](){ c->setSpeed(1.); };
    if(tile->hasRoad()) {
        patrol(finish, 20);
    } else {
        moveAround(finish, 1000);
    }
}

void eGodVisitAction::disappear() {
    const auto c = character();
    auto& board = c->getBoard();
    c->setActionType(eCharacterActionType::disappear);
    const auto a = e::make_shared<eWaitAction>(c, [](){}, [](){});
    a->setTime(500);
    setCurrentAction(a);
    board.ifVisible(c->tile(), [this]() {
        eSounds::playGodSound(mType, eGodSound::disappear);
    });
}

void eGodVisitAction::moveAround(const eAction& finishAct,
                                 const int time) {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto t = c->tile();
    const int tx = t->x();
    const int ty = t->y();
    const auto a = e::make_shared<eMoveAroundAction>(
                       c, finishAct, finishAct, tx, ty,
                       eMoveAroundAction::sDefaultWalkable);
    a->setTime(time);
    setCurrentAction(a);
}

void eGodVisitAction::patrol(const eAction& finishAct,
                             const int dist) {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto a = e::make_shared<ePatrolMoveAction>(
                       c, finishAct, finishAct);
    a->setMaxDistance(dist);
    setCurrentAction(a);
}
