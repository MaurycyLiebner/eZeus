#include "esheep.h"

#include "textures/egametextures.h"

eSheep::eSheep(eGameBoard& board) :
    eDomesticatedAnimal(board, &eCharacterTextures::fNudeSheep,
                        eCharacterType::sheep) {
    eGameTextures::loadSheep();
}

void eSheep::setNakedTexture() {
    setTextures(&eCharacterTextures::fNudeSheep);
}

void eSheep::setFleecedTexture() {
    setTextures(&eCharacterTextures::fFleecedSheep);
}
