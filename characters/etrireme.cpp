#include "etrireme.h"

#include "textures/egametextures.h"

eTrireme::eTrireme(eGameBoard& board) :
    eBoatBase(board, &eCharacterTextures::fTrireme,
              eCharacterType::trireme) {
    eGameTextures::loadTrireme();
    setHasSecondaryTexture(true);
}

eOverlay eTrireme::getSecondaryTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& texs = eGameTextures::characters();
    const auto& colls = texs[id];
    const auto a = actionType();
    const bool die = a == eCharacterActionType::die;
    const auto& charTexs = die ? colls.fTriremeDieOverlay :
                                 colls.fTriremeOverlay;
    const int oid = static_cast<int>(rotatedOrientation());
    const auto coll = &charTexs[oid];
    const bool wrap = !die;
    const bool disappear = die;
    const auto tex = eCharacter::getTexture(coll, wrap, disappear);
    return eOverlay{0., 0., tex, false};
}
