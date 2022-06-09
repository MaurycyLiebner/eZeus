#include "edonkey.h"

eDonkey::eDonkey(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fDonkey,
                   eCharacterType::donkey) {}
