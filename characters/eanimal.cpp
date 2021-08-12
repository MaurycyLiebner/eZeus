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

eTexture eAnimal::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::collect:
    case eCharacterActionType::fight: {
        coll = &charTexs.fFight[oid];
    } break;
    case eCharacterActionType::walk: {
        coll = &charTexs.fWalk[oid];
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
