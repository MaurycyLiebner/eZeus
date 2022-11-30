#include "etrader.h"

#include "edonkey.h"
#include "characters/actions/efollowaction.h"

#include "textures/egametextures.h"

eTrader::eTrader(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fTrader,
                   eCharacterType::trader) {
    eGameTextures::loadTrader();
}

void eTrader::createFollowers() {
    const auto t = tile();
    auto& board = getBoard();
    mFollowers.clear();
    for(int i = 0; i < 2; i++) {
        const auto d = e::make_shared<eDonkey>(board);
        eCharacter* follow = i == 0 ? this : mFollowers.back().get();
        const auto aox = e::make_shared<eFollowAction>(follow, d.get());
        d->setAction(aox);
        d->changeTile(t);
        mFollowers.push_back(d);
    }
}

void eTrader::setActionType(const eCharacterActionType t) {
    eBasicPatroler::setActionType(t);
    for(const auto& f : mFollowers) {
        f->setActionType(t);
    }
}
