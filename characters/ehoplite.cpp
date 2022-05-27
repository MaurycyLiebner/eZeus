#include "ehoplite.h"

#include "textures/egametextures.h"

eHoplite::eHoplite(eGameBoard& board) :
    eCharacter(board, eCharacterType::hoplite) {

}

std::shared_ptr<eTexture>
eHoplite::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = eGameTextures::characters()[id].fHoplite;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::lay:
    case eCharacterActionType::stand:
        return charTexs.fWalk[oid].getTexture(0);
    case eCharacterActionType::collect:
    case eCharacterActionType::fight:
        coll = &charTexs.fFight[oid];
        break;
    case eCharacterActionType::patrol:
    case eCharacterActionType::carry:
    case eCharacterActionType::walk:
        coll = &charTexs.fWalk[oid];
        break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
        break;
    default: return std::shared_ptr<eTexture>();
    }
    if(!coll || coll->size() == 0) return nullptr;
    int t = textureTime() - actionStartTime();
    if(!wrap) t = std::clamp(t, 0, coll->size() - 1);
    const int texId = t % coll->size();
    return coll->getTexture(texId);
}
