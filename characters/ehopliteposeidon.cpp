#include "ehopliteposeidon.h"

#include "textures/egametextures.h"

eHoplitePoseidon::eHoplitePoseidon(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fHoplitePoseidon,
                 eCharacterType::hoplitePoseidon) {
    eGameTextures::loadHoplitePoseidon();
}
