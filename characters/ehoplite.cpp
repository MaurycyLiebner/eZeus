#include "ehoplite.h"

#include "textures/egametextures.h"
#include "engine/egameboard.h"

eHoplite::eHoplite(eGameBoard& board) :
    eSoldier(board, &eCharacterTextures::fHoplite,
             eCharacterType::hoplite) {
    board.registerSoldier(this);
}

eHoplite::~eHoplite() {
    auto& brd = getBoard();
    brd.unregisterSoldier(this);
}
