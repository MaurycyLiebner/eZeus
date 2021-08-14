#include "ebasicpatroler.h"

#include "textures/egametextures.h"

eBasicPatroler::eBasicPatroler(eGameBoard& board,
                               const eCharTexs charTexs,
                               const eCharacterType type) :
    eCharacter(board, type),
    mTextures(eGameTextures::characters()),
    mCharTexs(charTexs) {

}

eTexture eBasicPatroler::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::collect:
    case eCharacterActionType::fight:
    case eCharacterActionType::carry:
    case eCharacterActionType::walk: {
        const int oid = static_cast<int>(orientation());
        coll = &charTexs.fWalk[oid];
    } break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
    }

    if(!coll || coll->size() == 0) return eTexture();
    int t = textureTime() - actionStartTime();
    if(!wrap) t = std::clamp(t, 0, coll->size() - 1);
    int texId = t % coll->size();
    return coll->getTexture(texId);
}
