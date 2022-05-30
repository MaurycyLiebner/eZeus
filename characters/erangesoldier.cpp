#include "erangesoldier.h"

#include "textures/egametextures.h"

eRangeSoldier::eRangeSoldier(eGameBoard& board,
                             const eCharTexs charTexs,
                             const eCharacterType type,
                             const int range) :
    eSoldier(board, &eCharacterTextures::fHoplite, type),
    mCharTexs(charTexs) {
    setRange(range);
}

std::shared_ptr<eTexture> eRangeSoldier::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& textures = eGameTextures::characters();
    const auto& charTexs = textures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return charTexs.fWalk[oid].getTexture(0);
    case eCharacterActionType::collect:
    case eCharacterActionType::carry:
    case eCharacterActionType::walk:
        coll = &charTexs.fWalk[oid];
        break;
    case eCharacterActionType::fight:
        coll = &charTexs.fFight[oid];
        break;
    case eCharacterActionType::fight2:
        coll = &charTexs.fFight2[oid];
        break;
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
