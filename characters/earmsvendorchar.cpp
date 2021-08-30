#include "earmsvendorchar.h"

eArmsVendorChar::eArmsVendorChar(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fArmsVendor,
                   eCharacterType::armsVendor) {}
