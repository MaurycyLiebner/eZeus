#include "ebasicpatroler.h"

#include "textures/egametextures.h"

eBasicPatroler::eBasicPatroler(
        eGameBoard& board, const eCharTexs charTexs) :
    eCharacter(board),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs) {

}

void eBasicPatroler::setAction(const eBasicPatrolerAction a) {
    mAction = a;
    mActionStartTime = textureTime();
}

eTexture eBasicPatroler::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    if(mAction == eBasicPatrolerAction::walk) {
        const int oid = static_cast<int>(orientation());
        coll = &charTexs.fWalk[oid];
    } else if(mAction == eBasicPatrolerAction::die) {
        coll = &charTexs.fDie;
    }
    if(!coll) return eTexture();
    const int t = textureTime() - mActionStartTime;
    return coll->getTexture(t % coll->size());
}
