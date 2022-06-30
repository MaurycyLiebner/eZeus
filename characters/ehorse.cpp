#include "ehorse.h"

#include "textures/egametextures.h"

eHorse::eHorse(eGameBoard& board) :
    eCharacter(board, eCharacterType::horse) {}

std::shared_ptr<eTexture> eHorse::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& chars = eGameTextures::characters();
    const auto& charTexs = chars[id].fHorse;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::collect:
    case eCharacterActionType::fight:
    case eCharacterActionType::lay:
    case eCharacterActionType::stand:
        coll = &charTexs.fStand[oid];
        break;
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
    if(!coll || coll->size() == 0) return std::shared_ptr<eTexture>();
    int t = textureTime() - actionStartTime();
    if(!wrap) t = std::clamp(t, 0, coll->size() - 1);
    const int texId = t % coll->size();
    return coll->getTexture(texId);
}
