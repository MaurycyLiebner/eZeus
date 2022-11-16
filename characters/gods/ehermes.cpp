#include "ehermes.h"

#include "textures/egametextures.h"

eHermes::eHermes(eGameBoard& board) :
    eGod(board, eGodType::hermes) {}

std::shared_ptr<eTexture>
eHermes::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& godTexs = eGameTextures::gods()[id];
    const auto& texs = godTexs.fHermes;
    const eTextureCollection* coll = nullptr;
    bool wrap = true;
    const int oid = static_cast<int>(orientation());
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return texs.fWalk[oid].getTexture(0);
    case eCharacterActionType::bless:
    case eCharacterActionType::curse:
        wrap = false;
        coll = &texs.fFight[oid];
        break;
    case eCharacterActionType::collect:
    case eCharacterActionType::fight: {
        wrap = false;
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
    case eCharacterActionType::appear:
        coll = &texs.fRun[oid];
        break;
    default:
        return std::shared_ptr<eTexture>();
    }

    const int s = coll->size();
    if(!coll || s == 0) return std::shared_ptr<eTexture>();
    int t = textureTime() - actionStartTime();
    if(!wrap) t = std::clamp(t, 0, s - 1);
    const int texId = t % s;
    return coll->getTexture(texId);
}

