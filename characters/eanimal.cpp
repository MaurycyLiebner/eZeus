#include "eanimal.h"

#include "textures/egametextures.h"

#include "spawners/eboarspawner.h"

eAnimal::eAnimal(eSpawner* const s,
                 eGameBoard& board,
                 const eCharTexs charTexs) :
    eCharacter(board),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs),
    mSpawner(s) {

}

eAnimal::~eAnimal() {
    mSpawner->decCount();
}

void eAnimal::setAnimationAction(const eAnimalAction a) {
    mAction = a;
    mActionStartTime = textureTime();
}

eTexture eAnimal::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    if(mAction == eAnimalAction::walk) {
        coll = &charTexs.fWalk[oid];
    } else if(mAction == eAnimalAction::fight) {
        coll = &charTexs.fFight[oid];
    } else if(mAction == eAnimalAction::die) {
        wrap = false;
        coll = &charTexs.fDie;
    }
    if(!coll || coll->size() == 0) return eTexture();
    const int t = textureTime() - mActionStartTime;
    int texId = t % coll->size();
    if(!wrap) texId = std::clamp(texId, 0, coll->size() - 1);
    return coll->getTexture(texId);
}
