#include "earcherposeidon.h"

#include "textures/egametextures.h"

eArcherPoseidon::eArcherPoseidon(eGameBoard& board) :
    eArcherBase(board, &eCharacterTextures::fArcherPoseidon,
                eCharacterType::archerPoseidon) {
    eGameTextures::loadArcherPoseidon();
}
