#include "efleecevendorchar.h"

eFleeceVendorChar::eFleeceVendorChar(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fFleeceVendor,
                   eCharacterType::fleeceVendor) {}
