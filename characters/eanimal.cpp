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

void eAnimal::setAction(const eAnimalAction a) {
    mAction = a;
    mActionStartTime = textureTime();
}

eTexture eAnimal::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    if(mAction == eAnimalAction::walk) {
        coll = &charTexs.fWalk[oid];
    } else if(mAction == eAnimalAction::fight) {
        coll = &charTexs.fFight[oid];
    } else if(mAction == eAnimalAction::die) {
        coll = &charTexs.fDie;
    }
    if(!coll || coll->size() == 0) return eTexture();
    const int t = textureTime() - mActionStartTime;
    return coll->getTexture(t % coll->size());
}
