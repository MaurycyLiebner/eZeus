#include "echariotposeidon.h"

#include "textures/echaractertextures.h"
#include "textures/egametextures.h"

eChariotPoseidon::eChariotPoseidon(eGameBoard& board) :
    eChariotBase(board, &eCharacterTextures::fChariotPoseidon,
                 eCharacterType::chariotPoseidon) {
    eGameTextures::loadChariotPoseidon();
}
