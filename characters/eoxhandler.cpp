#include "eoxhandler.h"

eOxHandler::eOxHandler(eGameBoard& board) :
    eTransporterBase(board, &eCharacterTextures::fOxHandler,
                     eCharacterType::oxHandler) {}
