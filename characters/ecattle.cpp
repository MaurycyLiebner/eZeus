#include "ecattle.h"

#include "textures/egametextures.h"

eCattle::eCattle(eGameBoard& board, const eCharacterType type) :
    eCharacter(board, type) {
    eGameTextures::loadCattle();
}

std::shared_ptr<eTexture> eCattle::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& texs = eGameTextures::characters();
    using eCTexs = eCattleTextures eCharacterTextures::*;
    eCTexs cTexs;
    const auto t = type();
    if(t == eCharacterType::cattle1) {
        cTexs = &eCharacterTextures::fCattle1;
    } else if(t == eCharacterType::cattle2) {
        cTexs = &eCharacterTextures::fCattle2;
    } else {
        cTexs = &eCharacterTextures::fCattle3;
    }
    const auto& charTexs = texs[id].*cTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::collect:
    case eCharacterActionType::fight:
    case eCharacterActionType::stand:
    case eCharacterActionType::lay:
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
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, false);
}

void eCattle::incTime(const int by) {
    eCharacter::incTime(by);
    mMatureWait += by;
    const int matureWait = 25000;
    if(mMatureWait > matureWait) {
        mMatureWait -= matureWait;
        mature();
    }
}

void eCattle::read(eReadStream& src) {
    eCharacter::read(src);
    src >> mMatureWait;
}

void eCattle::write(eWriteStream& dst) const {
    eCharacter::write(dst);
    dst << mMatureWait;
}

bool eCattle::mature() {
    const auto t = type();
    if(t == eCharacterType::cattle3) {
        return false;
    } else if(t == eCharacterType::cattle2) {
        setType(eCharacterType::cattle3);
    } else if(t == eCharacterType::cattle1) {
        setType(eCharacterType::cattle2);
    }
    return true;
}
