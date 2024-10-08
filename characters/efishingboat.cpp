#include "efishingboat.h"

#include "textures/egametextures.h"

eFishingBoat::eFishingBoat(eGameBoard& board) :
    eResourceCollectorBase(board, eCharacterType::fishingBoat) {
    eGameTextures::loadFishingBoat();
}

std::shared_ptr<eTexture> eFishingBoat::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& texs = eGameTextures::characters();
    const auto& colls = texs[id];
    const auto& charTexs = colls.fFishingBoat;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(rotatedOrientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return charTexs.fStand.getTexture(oid);
    case eCharacterActionType::collect:
        coll = &charTexs.fCollect[oid];
        break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk:
        coll = &charTexs.fSwim[oid];
        break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie[oid];
        break;
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, false);
}
