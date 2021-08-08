#include "efightingpatroler.h"

#include "textures/egametextures.h"

eFightingPatroler::eFightingPatroler(
        eGameBoard& board, const eCharTexs charTexs) :
    eCharacter(board),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs) {

}

void eFightingPatroler::setAction(const eFightingPatrolerAction a) {
    mAction = a;
    mActionStartTime = textureTime();
}

eTexture eFightingPatroler::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    if(mAction == eFightingPatrolerAction::walk) {
        coll = &charTexs.fWalk[oid];
    } else if(mAction == eFightingPatrolerAction::die) {
        coll = &charTexs.fDie;
    } else if(mAction == eFightingPatrolerAction::fight) {
        coll = &charTexs.fFight[oid];
    }
    if(!coll) return eTexture();
    const int t = textureTime() - mActionStartTime;
    return coll->getTexture(t % coll->size());
}
