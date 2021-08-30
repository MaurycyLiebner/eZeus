#include "eoilvendorchar.h"

eOilVendorChar::eOilVendorChar(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fOilVendor,
                   eCharacterType::oilVendor) {}
