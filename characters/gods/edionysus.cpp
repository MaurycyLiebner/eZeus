#include "edionysus.h"

#include "textures/egametextures.h"

eDionysus::eDionysus(eGameBoard& board) :
    eGod(board, eGodType::dionysus) {
    eGameTextures::loadDionysus();
}

std::shared_ptr<eTexture>
eDionysus::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& godTexs = eGameTextures::gods()[id];
    const auto& texs = godTexs.fDionysus;
    const eTextureCollection* coll = nullptr;
    bool reverse = false;
    bool wrap = true;
    bool disappear = false;
    const int oid = static_cast<int>(rotatedOrientation());
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
    case eCharacterActionType::fight2: {
        wrap = false;
        coll = &texs.fFight[oid];
    } break;
    case eCharacterActionType::fight: {
        wrap = true;
        coll = &texs.fFight[oid];
    } break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk: {
        coll = &texs.fWalk[oid];
    } break;
    case eCharacterActionType::die:
        wrap = false;
        disappear = true;
        coll = &texs.fDisappear;
        break;
    case eCharacterActionType::disappear:
        reverse = true;
        wrap = false;
        disappear = true;
        coll = &texs.fAppear;
        break;
    case eCharacterActionType::appear:
        wrap = false;
        coll = &texs.fAppear;
        break;
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, reverse, disappear);
}
