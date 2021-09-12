#include "egodvisitaction.h"

#include "characters/echaracter.h"

#include "engine/egameboard.h"

#include "ewaitaction.h"
#include "emovearoundaction.h"
#include "epatrolmoveaction.h"

#include "esounds.h"

void eGodVisitAction::appear() {
    const auto c = character();
    auto& board = c->getBoard();
    const int w = board.width();
    const int h = board.height();
    eTile* tile = nullptr;
    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            const auto t = board.tile(x, y);
            if(t->hasRoad()) {
                tile = t;
                break;
            }
        }
    }
    if(!tile) tile = board.tile(w/2, h/2);
    c->setActionType(eCharacterActionType::appear);
    c->changeTile(tile);
    const auto fail = [this]() { disappear(); };
    const auto finish = [this, tile]() {
        if(tile->hasRoad()) patrol();
        else moveAround();
    };
    const auto a = e::make_shared<eWaitAction>(c, fail, finish);
    a->setTime(300);
    setCurrentAction(a);
    board.ifVisible(tile, []() {
        eSounds::playDemeterAppearSound();
    });
}

void eGodVisitAction::disappear() {
    const auto c = character();
    auto& board = c->getBoard();
    c->setActionType(eCharacterActionType::die);
    const auto finish = [this]() {
        const auto c = character();
        c->changeTile(nullptr);
    };
    const auto a = e::make_shared<eWaitAction>(c, finish, finish);
    a->setTime(300);
    setCurrentAction(a);
    board.ifVisible(c->tile(), []() {
        eSounds::playDemeterDisappearSound();
    });
}

void eGodVisitAction::moveAround() {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto t = c->tile();
    const int tx = t->x();
    const int ty = t->y();
    const auto finish = [this]() {
        disappear();
    };
    const auto a = e::make_shared<eMoveAroundAction>(
                       c, finish, finish, tx, ty,
                       eMoveAroundAction::sDefaultWalkable);
    a->setTime(5000);
    setCurrentAction(a);
}

void eGodVisitAction::patrol() {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto finish = [this]() {
        disappear();
    };
    const auto a = e::make_shared<ePatrolMoveAction>(
                       c, finish, finish);
    setCurrentAction(a);
}
