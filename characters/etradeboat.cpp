#include "etradeboat.h"

#include "textures/egametextures.h"

eTradeBoat::eTradeBoat(eGameBoard& board) :
    eBoatBase(board, &eCharacterTextures::fTradeBoat,
              eCharacterType::tradeBoat) {
    eGameTextures::loadTradeBoat();
}
