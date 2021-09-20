#include "efirefighter.h"

#include "textures/egametextures.h"

eFireFighter::eFireFighter(eGameBoard& board) :
    eCharacter(board, eCharacterType::fireFighter),
    mTextures(eGameTextures::characters()),
    mCharTexs(&eCharacterTextures::fFireFighter) {
    setProvide(eProvide::maintanance, __INT_MAX__);
}

std::shared_ptr<eTexture> eFireFighter::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = mTextures[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool boomerang = false;
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    default:
    case eCharacterActionType::none:
        return std::shared_ptr<eTexture>();
    case eCharacterActionType::stand: {
        return charTexs.fWalk[oid].getTexture(0);
    } break;
    case eCharacterActionType::collect:
    case eCharacterActionType::walk: {
        coll = &charTexs.fWalk[oid];
    } break;
    case eCharacterActionType::fight: {
        coll = &charTexs.fPutOut[oid];
        boomerang = true;
    } break;
    case eCharacterActionType::carry: {
        coll = &charTexs.fCarry[oid];
    } break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
    }
    const int s = coll->size();
    if(!coll || s == 0) return std::shared_ptr<eTexture>();
    int t = textureTime() - actionStartTime();
    if(!wrap) {
        t = std::clamp(t, 0, s - 1);
    } else if(boomerang) {
        t = t % (2*s);
        if(t > s) t = 2*s - t;
    }
    const int texId = t % s;
    return coll->getTexture(texId);
}
