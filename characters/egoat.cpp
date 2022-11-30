#include "egoat.h"

#include "textures/egametextures.h"

eGoat::eGoat(eGameBoard& board) :
    eDomesticatedAnimal(board, &eCharacterTextures::fGoat,
                        eCharacterType::goat) {
    eGameTextures::loadGoat();
}
