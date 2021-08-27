#include "egoat.h"

eGoat::eGoat(eGameBoard& board) :
    eDomesticatedAnimal(board, &eCharacterTextures::fGoat,
                        eCharacterType::goat) {}
