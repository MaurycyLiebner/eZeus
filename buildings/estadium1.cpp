#include "estadium1.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"
#include "engine/egameboard.h"

eStadium1Base::eStadium1Base(eGameBoard& board,
                             const eBaseTex baseTex) :
    ePatrolTarget(board, eBuildingType::gymnasium,
                  baseTex, 0, 0, eOverlays(),
                  [this]() { return e::make_shared<eGymnast>(getBoard()); },
                  eBuildingType::stadium1, 5, 5, 45) {
    board.registerStadium();
}

eStadium1Base::~eStadium1Base() {
    auto& b = getBoard();
    b.unregisterStadium();
}

eStadium1W::eStadium1W(eGameBoard& board) :
    eStadium1Base(board, &eBuildingTextures::fStadium1W) {}

eStadium1H::eStadium1H(eGameBoard& board) :
    eStadium1Base(board, &eBuildingTextures::fStadium1H) {}
