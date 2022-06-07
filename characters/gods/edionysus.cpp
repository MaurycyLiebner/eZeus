#include "edionysus.h"

#include "textures/egametextures.h"

eDionysus::eDionysus(eGameBoard& board) :
    eGod(board, eGodType::dionysus) {}

std::shared_ptr<eTexture>
eDionysus::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& godTexs = eGameTextures::gods()[id];
    const auto& texs = godTexs.fDionysus;
    const eTextureCollection* coll = nullptr;
    bool reverse = false;
    bool wrap = true;
    const int oid = static_cast<int>(orientation());
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return texs.fWalk[oid].getTexture(0);
    case eCharacterActionType::bless:
    case eCharacterActionType::collect:
    case eCharacterActionType::fight: {
        coll = &texs.fFight[oid];
    } break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk: {
        coll = &texs.fWalk[oid];
    } break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &texs.fDisappear;
        break;
    case eCharacterActionType::disappear:
        reverse = true;
        wrap = false;
        coll = &texs.fAppear;
        break;
    case eCharacterActionType::appear:
        wrap = false;
        coll = &texs.fAppear;
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
