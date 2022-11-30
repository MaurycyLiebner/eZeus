#include "elumberjack.h"

#include "textures/egametextures.h"

eLumberjack::eLumberjack(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fLumberjack,
                       eCharacterType::lumberjack) {
    eGameTextures::loadLumberjack();
}
