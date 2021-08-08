#include "eresourcecollector.h"

#include "textures/egametextures.h"

eResourceCollector::eResourceCollector(
        eGameBoard& board, const eCharTexs charTexs) :
    eCharacter(board),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs) {

}

void eResourceCollector::setAction(const eResourceCollectorAction a) {
    mAction = a;
    mActionStartTime = textureTime();
}

eTexture eResourceCollector::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    if(mAction == eResourceCollectorAction::walk) {
        coll = &charTexs.fWalk[oid];
    } else if(mAction == eResourceCollectorAction::collect) {
        coll = &charTexs.fCollect[oid];
    } else if(mAction == eResourceCollectorAction::carry) {
        coll = &charTexs.fCarry[oid];
    } else if(mAction == eResourceCollectorAction::die) {
        coll = &charTexs.fDie;
    }
    if(!coll) return eTexture();
    const int t = textureTime() - mActionStartTime;
    return coll->getTexture(t % coll->size());
}
