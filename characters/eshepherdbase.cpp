#include "eshepherdbase.h"

#include "textures/egametextures.h"

eShepherdBase::eShepherdBase(
        eGameBoard& board, const eCharTexs charTexs,
        const eCharacterType type) :
    eResourceCollectorBase(board, type),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs) {

}

std::shared_ptr<eTexture>
eShepherdBase::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return charTexs.fWalk[oid].getTexture(0);
    case eCharacterActionType::collect: {
        coll = &charTexs.fCollect[oid];
    } break;
    case eCharacterActionType::fight: {
        coll = &charTexs.fFight;
    } break;
    case eCharacterActionType::walk: {
        coll = &charTexs.fWalk[oid];
    } break;
    case eCharacterActionType::carry: {
        if(!charTexs.fCarry.size()) {
            coll = &charTexs.fWalk[oid];
        } else {
            coll = &charTexs.fCarry[oid];
        }
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
