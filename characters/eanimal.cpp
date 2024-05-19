#include "eanimal.h"

#include "textures/egametextures.h"

#include "spawners/eboarspawner.h"

eAnimal::eAnimal(eGameBoard& board,
                 const eCharTexs charTexs,
                 const eCharacterType type) :
    eCharacter(board, type),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs) {

}

void eAnimal::setTextures(const eCharTexs& texs) {
    mCharTexs = texs;
}

std::shared_ptr<eTexture> eAnimal::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return charTexs.fWalk[oid].getTexture(0);
    case eCharacterActionType::lay:
        coll = &charTexs.fLayDown[oid];
        break;
    case eCharacterActionType::collect:
    case eCharacterActionType::fight: {
        coll = &charTexs.fFight[oid];
    } break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk: {
        coll = &charTexs.fWalk[oid];
    } break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
        break;
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, false);
}
