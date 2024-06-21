#include "eartisan.h"

#include "textures/egametextures.h"

eArtisan::eArtisan(eGameBoard& board) :
    eCharacter(board, eCharacterType::artisan) {
    eGameTextures::loadArtisan();
}

std::shared_ptr<eTexture> eArtisan::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& texs = eGameTextures::characters();
    const auto& colls = texs[id];
    const auto& charTexs = colls.fArtisan;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return charTexs.fWalk[oid].getTexture(0);
    case eCharacterActionType::fight:
    case eCharacterActionType::buildStanding:
        coll = &charTexs.fBuildStanding[oid];
        break;
    case eCharacterActionType::build:
        coll = &charTexs.fBuild[oid];
        break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk:
        coll = &charTexs.fWalk[oid];
        break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
        break;
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, false);
}
