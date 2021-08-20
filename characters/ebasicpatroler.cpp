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
    case eCharacterActionType::none:
        return eTexture();
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

    const int s = coll->size();
    if(!coll || s == 0) return eTexture();
    int t = textureTime() - actionStartTime();
    if(!wrap) t = std::clamp(t, 0, s - 1);
    const int texId = t % s;
    return coll->getTexture(texId);
}
