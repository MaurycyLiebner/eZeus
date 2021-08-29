#include "efoodvendorchar.h"

eFoodVendorChar::eFoodVendorChar(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fFoodVendor,
                   eCharacterType::foodVendor) {
    setProvide(eProvide::food, 1000);
}
