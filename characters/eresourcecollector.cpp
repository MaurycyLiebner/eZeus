#include "eresourcecollector.h"

#include "textures/egametextures.h"

eResourceCollector::eResourceCollector(
        eGameBoard& board, const eCharTexs charTexs,
        const eCharacterType type) :
    eCharacter(board, type),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs) {

}

eTexture eResourceCollector::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::collect:
    case eCharacterActionType::fight: {
        coll = &charTexs.fCollect[oid];
    } break;
    case eCharacterActionType::walk: {
        coll = &charTexs.fWalk[oid];
    } break;
    case eCharacterActionType::carry: {
        coll = &charTexs.fCarry[oid];
    } break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
    }
    if(!coll || coll->size() == 0) return eTexture();
    int t = textureTime() - actionStartTime();
    if(!wrap) t = std::clamp(t, 0, coll->size() - 1);
    const int texId = t % coll->size();
    return coll->getTexture(texId);
}
