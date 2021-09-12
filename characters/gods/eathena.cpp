#include "eathena.h"

#include "engine/etile.h"
#include "textures/egametextures.h"

eAthena::eAthena(eGameBoard& board) :
    eCharacter(board, eCharacterType::athena) {

}

std::shared_ptr<eTexture> eAthena::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = eGameTextures::gods()[id];
    const auto& atn = charTexs.fAthena;
    const eTextureCollection* coll = nullptr;
    bool reverse = false;
    bool wrap = true;
    const int oid = static_cast<int>(orientation());
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return atn.fWalk[oid].getTexture(0);
    case eCharacterActionType::bless:
        coll = &atn.fBless[oid];
        break;
    case eCharacterActionType::collect:
    case eCharacterActionType::fight:
        coll = &atn.fFight[oid];
        break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk:
        coll = &atn.fWalk[oid];
        break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &atn.fDisappear;
        break;
    case eCharacterActionType::appear:
        wrap = false;
        reverse = true;
        coll = &atn.fDisappear;
        break;
    default:
        return nullptr;
    }

    if(!coll) return nullptr;
    const int s = coll->size();
    if(s == 0) return nullptr;
    int t = textureTime() - actionStartTime();
    if(reverse) {
        t = coll->size() - t;
    }
    if(!wrap) t = std::clamp(t, 0, s - 1);
    const int texId = t % s;
    return coll->getTexture(texId);
}
