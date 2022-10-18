#include "egodvisitaction.h"

#include "characters/echaracter.h"

#include "engine/egameboard.h"

#include "esounds.h"

#include "characters/echaracter.h"
#include "eiteratesquare.h"

bool eGodVisitAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eGodVisitStage::none:
        mStage = eGodVisitStage::appear;
        placeOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            if(type() == eGodType::hermes) {
                hermesRun(true);
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
        if(type() == eGodType::hermes) {
            hermesRun(false);
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
}
