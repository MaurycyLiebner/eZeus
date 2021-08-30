#include "ehorsevendorchar.h"

eHorseVendorChar::eHorseVendorChar(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fHorseVendor,
                   eCharacterType::horseTrainer) {}
