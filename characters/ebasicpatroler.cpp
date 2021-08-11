#include "ebasicpatroler.h"

#include "textures/egametextures.h"

eBasicPatroler::eBasicPatroler(
        eGameBoard& board, const eCharTexs charTexs) :
    eCharacter(board),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs) {

}

void eBasicPatroler::setAnimationAction(const eBasicPatrolerAction a) {
    mAction = a;
    mActionStartTime = textureTime();
}

eTexture eBasicPatroler::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    bool wrap = true;
    if(mAction == eBasicPatrolerAction::walk) {
        const int oid = static_cast<int>(orientation());
        coll = &charTexs.fWalk[oid];
    } else if(mAction == eBasicPatrolerAction::die) {
        wrap = false;
        coll = &charTexs.fDie;
    }
    if(!coll || coll->size() == 0) return eTexture();
    const int t = textureTime() - mActionStartTime;
    int texId = t % coll->size();
    if(!wrap) texId = std::clamp(texId, 0, coll->size() - 1);
    return coll->getTexture(texId);
}
