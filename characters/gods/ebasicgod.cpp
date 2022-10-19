#include "ebasicgod.h"

#include "textures/egametextures.h"

eBasicGod::eBasicGod(eGameBoard& board,
                     const eGodTexs godTexs,
                     const eGodType gt) :
    eGod(board, gt),
    mGodTexs(godTexs) {}

std::shared_ptr<eTexture>
eBasicGod::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& godTexs = eGameTextures::gods()[id];
    const auto& texs = godTexs.*mGodTexs;
    const eTextureCollection* coll = nullptr;
    bool reverse = false;
    bool wrap = true;
    const int oid = static_cast<int>(orientation());
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return texs.fWalk[oid].getTexture(0);
    case eCharacterActionType::bless:
        wrap = false;
        coll = &texs.fFight[oid];
        break;
    case eCharacterActionType::collect:
    case eCharacterActionType::fight: {
        coll = &texs.fFight[oid];
    } break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk: {
        coll = &texs.fWalk[oid];
    } break;
    case eCharacterActionType::disappear:
    case eCharacterActionType::die:
        wrap = false;
        coll = &texs.fDisappear;
        break;
    case eCharacterActionType::appear:
        wrap = false;
        reverse = true;
        coll = &texs.fDisappear;
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
