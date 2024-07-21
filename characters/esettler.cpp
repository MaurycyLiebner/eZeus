#include "esettler.h"

#include "textures/egametextures.h"

#include "erand.h"

eSettler::eSettler(eGameBoard& board) :
    eBasicPatroler(board,
                   eRand::rand() % 2 ? &eCharacterTextures::fSettlers1 :
                                &eCharacterTextures::fSettlers2,
                   eCharacterType::settler) {

    eGameTextures::loadSettlers();
}
