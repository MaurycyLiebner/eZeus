#include "elumberjack.h"

eLumberjack::eLumberjack(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fLumberjack) {}
