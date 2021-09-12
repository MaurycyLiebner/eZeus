#include "edemeter.h"

#include "engine/etile.h"
#include "textures/egametextures.h"

eDemeter::eDemeter(eGameBoard& board) :
    eCharacter(board, eCharacterType::demeter) {

}

std::shared_ptr<eTexture> eDemeter::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = eGameTextures::demeter()[id];
    const eTextureCollection* coll = nullptr;
    bool reverse = false;
    bool wrap = true;
    const int oid = static_cast<int>(orientation());
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return charTexs.fWalk[oid].getTexture(0);
    case eCharacterActionType::collect:
    case eCharacterActionType::fight: {
        coll = &charTexs.fFight[oid];
    } break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk: {
        coll = &charTexs.fWalk[oid];
    } break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
        break;
    case eCharacterActionType::appear:
        wrap = false;
        reverse = true;
        coll = &charTexs.fDie;
        break;
    default:
        return std::shared_ptr<eTexture>();
    }

    const int s = coll->size();
    if(!coll || s == 0) return std::shared_ptr<eTexture>();
    int t = textureTime() - actionStartTime();
    if(reverse) {
        t = coll->size() - t;
    }
    if(!wrap) t = std::clamp(t, 0, s - 1);
    const int texId = t % s;
    return coll->getTexture(texId);
}
