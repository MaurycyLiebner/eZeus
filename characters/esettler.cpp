#include "esettler.h"

#include "textures/egametextures.h"

eSettler::eSettler(eGameBoard& board) :
    eBasicPatroler(board,
                   rand() % 2 ? &eCharacterTextures::fSettlers1 :
                                &eCharacterTextures::fSettlers2,
                   eCharacterType::settler) {

    eGameTextures::loadSettlers();
}
