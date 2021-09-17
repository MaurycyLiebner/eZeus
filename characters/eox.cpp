#include "eox.h"

eOx::eOx(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fOx,
                   eCharacterType::ox) {}
