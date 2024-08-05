#include "echariotbase.h"

#include "textures/egametextures.h"
#include "enumbers.h"

eChariotBase::eChariotBase(eGameBoard& board,
                             const eCharTexs charTexs,
                             const eCharacterType type) :
    eSoldier(board, &eCharacterTextures::fHoplite, type),
    mCharTexs(charTexs) {
    setAttack(eNumbers::sChariotAttack);
    setSpeed(eNumbers::sChariotSpeed);
    setHP(eNumbers::sChariotHP);
}

std::shared_ptr<eTexture>
eChariotBase::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& gTexs = eGameTextures::characters();
    const auto& texs = gTexs[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    bool wrap = true;
    const int oid = static_cast<int>(rotatedOrientation());
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return texs.fWalk[oid].getTexture(0);
    case eCharacterActionType::collect:
    case eCharacterActionType::fight:
    case eCharacterActionType::fight2:
    case eCharacterActionType::bless:
    case eCharacterActionType::curse: {
        wrap = true;
        coll = &texs.fFight[oid];
    } break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk: {
        coll = &texs.fWalk[oid];
    } break;
    case eCharacterActionType::disappear:
    case eCharacterActionType::die:
        wrap = false;
        coll = &texs.fDie[oid];
        break;
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, false);
}
