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
    bool disappear = false;
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
    case eCharacterActionType::disappear:
    case eCharacterActionType::die:
        wrap = false;
        disappear = true;
        coll = &texs.fDisappear;
        break;
    case eCharacterActionType::appear:
        wrap = false;
        reverse = true;
        coll = &texs.fDisappear;
        break;
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, reverse, disappear);
}
