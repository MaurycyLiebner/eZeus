#include "ewinevendorchar.h"

eWineVendorChar::eWineVendorChar(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fWineVendor,
                   eCharacterType::wineVendor) {}
