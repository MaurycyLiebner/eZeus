#include "eoxhandler.h"

eOxHandler::eOxHandler(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fOxHandler,
                   eCharacterType::oxHandler) {}
