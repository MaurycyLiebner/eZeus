#include "esoldier.h"

#include "engine/egameboard.h"
#include "esoldierbanner.h"

eSoldier::eSoldier(eGameBoard& board,
                   const eCharTexs charTexs,
                   const eCharacterType type) :
    eFightingPatroler(board, charTexs, type) {
    board.registerSoldier(this);
}

eSoldier::~eSoldier() {
    auto& brd = getBoard();
    brd.unregisterSoldier(this);
    setBanner(nullptr);
}

eSoldierAction* eSoldier::soldierAction() const {
    return mAction.get();
}

void eSoldier::setSoldierAction(const stdsptr<eSoldierAction>& a) {
    mAction = a;
}

eSoldierBanner* eSoldier::banner() const {
    return mBanner;
}

void eSoldier::setBanner(eSoldierBanner* const b) {
    if(mBanner) {
        mBanner->removeSoldier(this);
    }
    mBanner = b;
    if(mBanner) {
        mBanner->addSoldier(this);
    }
}
