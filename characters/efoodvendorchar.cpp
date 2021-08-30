#include "efoodvendorchar.h"

eFoodVendorChar::eFoodVendorChar(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fFoodVendor,
                   eCharacterType::foodVendor) {}
