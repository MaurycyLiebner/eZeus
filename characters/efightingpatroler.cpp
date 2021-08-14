#include "efightingpatroler.h"

#include "textures/egametextures.h"

eFightingPatroler::eFightingPatroler(
        eGameBoard& board, const eCharTexs charTexs,
        const eCharacterType type) :
    eCharacter(board, type),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs) {

}

void eFightingPatroler::setAnimationAction(const eFightingPatrolerAction a) {
    mAction = a;
    mActionStartTime = textureTime();
}

eTexture eFightingPatroler::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    if(mAction == eFightingPatrolerAction::walk) {
        coll = &charTexs.fWalk[oid];
    } else if(mAction == eFightingPatrolerAction::fight) {
        coll = &charTexs.fFight[oid];
    } else if(mAction == eFightingPatrolerAction::die) {
        wrap = false;
        coll = &charTexs.fDie;
    }
    if(!coll || coll->size() == 0) return eTexture();
    const int t = textureTime() - mActionStartTime;
    int texId = t % coll->size();
    if(!wrap) texId = std::clamp(texId, 0, coll->size() - 1);
    return coll->getTexture(texId);
}
