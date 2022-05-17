#include "ebasicpatroler.h"

#include "textures/egametextures.h"

eBasicPatroler::eBasicPatroler(eGameBoard& board,
                               const eCharTexs charTexs,
                               const eCharacterType type) :
    eCharacter(board, type),
    mCharTexs(charTexs) {

}

std::shared_ptr<eTexture> eBasicPatroler::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& gTexs = eGameTextures::characters();
    const auto& charTexs = gTexs[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    bool wrap = true;
    const int oid = static_cast<int>(orientation());
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return charTexs.fWalk[oid].getTexture(0);
    case eCharacterActionType::collect:
    case eCharacterActionType::fight:
    case eCharacterActionType::carry:
    case eCharacterActionType::walk: {
        coll = &charTexs.fWalk[oid];
    } break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
        break;
    default: return std::shared_ptr<eTexture>();
    }

    const int s = coll->size();
    if(!coll || s == 0) return std::shared_ptr<eTexture>();
    int t = textureTime() - actionStartTime();
    if(!wrap) t = std::clamp(t, 0, s - 1);
    const int texId = t % s;
    return coll->getTexture(texId);
}

void eBasicPatroler::setCharTextures(const eCharTexs& texs) {
    mCharTexs = texs;
}
