#include "earcher.h"

#include "textures/egametextures.h"
#include "engine/egameboard.h"

eArcher::eArcher(eGameBoard& board) :
    eCharacter(board, eCharacterType::archer) {
    setAttack(0.5);
}

std::shared_ptr<eTexture>
eArcher::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& texs = eGameTextures::characters()[id];
    const eArcherTextures* charTexs;
    auto& board = getBoard();
    if(board.poseidonMode()) {
        eGameTextures::loadPoseidonTowerArcher();
        charTexs = &texs.fPoseidonTowerArcher;
    } else {
        eGameTextures::loadArcher();
        charTexs = &texs.fArcher;
    }
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::lay:
    case eCharacterActionType::stand:
        return charTexs->fWalk[oid].getTexture(0);
    case eCharacterActionType::collect:
    case eCharacterActionType::fight:
        coll = &charTexs->fFight[oid];
        break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk:
        coll = &charTexs->fWalk[oid];
        break;
    case eCharacterActionType::patrol:
        coll = &charTexs->fPatrol[oid];
        break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs->fDie;
        break;
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, false);
}
