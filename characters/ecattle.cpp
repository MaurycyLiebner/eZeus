#include "ecattle.h"

#include "textures/egametextures.h"
#include "enumbers.h"

int eCattle::sId = 0;

eCattle::eCattle(eGameBoard& board, const eCharacterType type) :
    eCharacter(board, type), mId(sId++) {
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
    } else if(t == eCharacterType::cattle3) {
        cTexs = &eCharacterTextures::fCattle3;
    } else {
        eGameTextures::loadBull();
        const auto& charTexs = texs[id].fBull;
        const eTextureCollection* coll = nullptr;
        const int oid = static_cast<int>(rotatedOrientation());
        bool wrap = true;
        const auto a = actionType();
        switch(a) {
        case eCharacterActionType::collect:
        case eCharacterActionType::fight:
        case eCharacterActionType::fight2:
            coll = &charTexs.fAttack[oid];
            break;
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
    const auto& charTexs = texs[id].*cTexs;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(rotatedOrientation());
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
    const int matureWait = eNumbers::sCattleMaturePeriod;
    if(mMatureWait > matureWait) {
        mMatureWait = 0;
        mature();
    }
}

void eCattle::read(eReadStream& src) {
    eCharacter::read(src);
    src >> mId;
    src >> mMatureWait;
    src >> sId;
}

void eCattle::write(eWriteStream& dst) const {
    eCharacter::write(dst);
    dst << mId;
    dst << mMatureWait;
    dst << sId;
}

bool eCattle::mature() {
    const auto t = type();
    if(t == eCharacterType::cattle3) {
        return false;
    } else if(t == eCharacterType::cattle2) {
        if(mId != 0 && mId % 7 == 0) {
            setType(eCharacterType::bull);
        } else {
            setType(eCharacterType::cattle3);
        }
    } else if(t == eCharacterType::cattle1) {
        setType(eCharacterType::cattle2);
    }
    return true;
}
