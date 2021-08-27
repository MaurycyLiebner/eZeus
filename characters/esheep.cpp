#include "esheep.h"

eSheep::eSheep(eGameBoard& board) :
    eDomesticatedAnimal(board, &eCharacterTextures::fNudeSheep,
                        eCharacterType::sheep) {}

void eSheep::setNakedTexture() {
    setTextures(&eCharacterTextures::fNudeSheep);
}

void eSheep::setFleecedTexture() {
    setTextures(&eCharacterTextures::fFleecedSheep);
}
