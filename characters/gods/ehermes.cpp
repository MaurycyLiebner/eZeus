#include "ehermes.h"

#include "textures/egametextures.h"

eHermes::eHermes(eGameBoard& board) :
    eGod(board, eGodType::hermes) {
    eGameTextures::loadHermes();
}

std::shared_ptr<eTexture>
eHermes::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& godTexs = eGameTextures::gods()[id];
    const auto& texs = godTexs.fHermes;
    const eTextureCollection* coll = nullptr;
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
        coll = &texs.fRun[oid];
        break;
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, false, disappear);
}

