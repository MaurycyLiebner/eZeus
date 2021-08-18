#include "efirefighter.h"

#include "textures/egametextures.h"

eFireFighter::eFireFighter(eGameBoard& board) :
    eCharacter(board, eCharacterType::fireFighter),
    mTextures(eGameTextures::characters()),
    mCharTexs(&eCharacterTextures::fFireFighter) {

}

eTexture eFireFighter::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::collect:
    case eCharacterActionType::walk: {
        coll = &charTexs.fWalk[oid];
    } break;
    case eCharacterActionType::fight: {
        coll = &charTexs.fPutOut[oid];
    } break;
    case eCharacterActionType::carry: {
        coll = &charTexs.fCarry[oid];
    } break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
    }
    if(!coll || coll->size() == 0) return eTexture();
    const int t = textureTime() - actionStartTime();
    int texId = t % coll->size();
    if(!wrap) texId = std::clamp(texId, 0, coll->size() - 1);
    return coll->getTexture(texId);
}
