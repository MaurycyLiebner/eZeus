#include "einvasionevent.h"

#include "engine/egameboard.h"
#include "characters/esoldierbanner.h"
#include "einvasionhandler.h"

eInvasionEvent::eInvasionEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::invasion, board) {}

void eInvasionEvent::setCity(const stdsptr<eWorldCity>& city) {
    mCity = city;
}

void eInvasionEvent::setArmy(const int infantry,
                             const int cavalry,
                             const int archers) {
    mInfantry = infantry;
    mCavalry = cavalry;
    mArchers = archers;
}

void eInvasionEvent::trigger() {
    auto& board = getBoard();
    const int bribe = bribeCost();

    eEventData ed;
    ed.fType = eMessageEventType::invasion;
    ed.fBribe = bribe;
    ed.fCity = mCity;
    const auto boardPtr = &board;
    const auto city = mCity;
    ed.fA0 = [boardPtr, city]() { // surrender
        eEventData ed;
        ed.fCity = city;
        boardPtr->event(eEvent::invasionDefeat, ed);
    };
    if(board.drachmas() >= bribe) { // bribe
        ed.fA1 = [boardPtr, bribe, city]() {
            boardPtr->incDrachmas(-bribe);
            eEventData ed;
            ed.fCity = city;
            boardPtr->event(eEvent::invasionBribed, ed);
        };
    }
    const int infantry = mInfantry;
    const int cavalry = mCavalry;
    const int archers = mArchers;
    ed.fA2 = [boardPtr, city, infantry, cavalry, archers]() { // fight
        auto& board = *boardPtr;
        const auto tile = board.landInvasionTile(0);
        if(!tile) return;
        const auto eh = new eInvasionHandler(board, city);
        eh->initialize(tile, infantry, cavalry, archers);
    };
    board.event(eEvent::invasion, ed);
}

void eInvasionEvent::write(eWriteStream& dst) const {
    dst.writeCity(mCity.get());

    dst << mInfantry;
    dst << mCavalry;
    dst << mArchers;
}

void eInvasionEvent::read(eReadStream& src) {
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });

    src >> mInfantry;
    src >> mCavalry;
    src >> mArchers;
}

int eInvasionEvent::bribeCost() const {
    auto& board = getBoard();
    const auto diff = board.difficulty();
    const int rt = eDifficultyHelpers::soliderBribe(
                       diff, eCharacterType::rockThrower);
    const int ht = eDifficultyHelpers::soliderBribe(
                       diff, eCharacterType::hoplite);
    const int hm = eDifficultyHelpers::soliderBribe(
                       diff, eCharacterType::horseman);
    const int bribe = rt*mArchers + ht*mInfantry + hm*mCavalry;
    return bribe;
}
