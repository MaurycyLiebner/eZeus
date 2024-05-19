#include "ebasicpatroler.h"

#include "textures/egametextures.h"
#include "engine/egameboard.h"

eBasicPatroler::eBasicPatroler(eGameBoard& board,
                               const eCharTexs charTexs,
                               const eCharacterType type) :
    eCharacter(board, type),
    mCharTexs(charTexs) {

}

std::shared_ptr<eTexture> eBasicPatroler::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& gTexs = eGameTextures::characters();
    const auto& charTexs = gTexs[id].*mCharTexs;
    const eTextureCollection* coll = nullptr;
    bool wrap = true;
    const int oid = static_cast<int>(orientation());
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return charTexs.fWalk[oid].getTexture(0);
    case eCharacterActionType::collect:
    case eCharacterActionType::fight:
    case eCharacterActionType::carry:
    case eCharacterActionType::walk: {
        coll = &charTexs.fWalk[oid];
    } break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
        break;
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, false);
}

void eBasicPatroler::beingKilled() {
    if(playerId() == 1) {
        auto& brd = getBoard();
        brd.walkerKilled();
    }
}

void eBasicPatroler::setCharTextures(const eCharTexs& texs) {
    mCharTexs = texs;
}
