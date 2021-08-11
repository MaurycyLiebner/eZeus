#include "eresourcecollector.h"

#include "textures/egametextures.h"

eResourceCollector::eResourceCollector(
        eGameBoard& board, const eCharTexs charTexs) :
    eCharacter(board),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs) {

}

void eResourceCollector::setAnimationAction(const eResourceCollectorAction a) {
    mAction = a;
    mActionStartTime = textureTime();
}

eTexture eResourceCollector::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    if(mAction == eResourceCollectorAction::walk) {
        coll = &charTexs.fWalk[oid];
    } else if(mAction == eResourceCollectorAction::collect) {
        coll = &charTexs.fCollect[oid];
    } else if(mAction == eResourceCollectorAction::carry) {
        coll = &charTexs.fCarry[oid];
    } else if(mAction == eResourceCollectorAction::die) {
        wrap = false;
        coll = &charTexs.fDie;
    }
    if(!coll || coll->size() == 0) return eTexture();
    const int t = textureTime() - mActionStartTime;
    int texId = t % coll->size();
    if(!wrap) texId = std::clamp(texId, 0, coll->size() - 1);
    return coll->getTexture(texId);
    if(!coll) return eTexture();
    return coll->getTexture(t % coll->size());
}
