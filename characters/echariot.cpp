#include "echariot.h"

#include "textures/egametextures.h"

eChariot::eChariot(eGameBoard& board) :
    eCharacter(board, eCharacterType::chariot) {
    eGameTextures::loadChariot();
}

std::shared_ptr<eTexture>
eChariot::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& gTexs = eGameTextures::characters();
    const auto& charTexs = gTexs[id].fChariot;
    const int oid = static_cast<int>(rotatedOrientation());
    const auto& coll = &charTexs[oid];
    return eCharacter::getTexture(coll, true, false);
}
