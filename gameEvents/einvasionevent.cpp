#include "einvasionevent.h"

#include "engine/egameboard.h"

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
    ed.fCity = mCity.get();
    const auto boardPtr = &board;
    ed.fA0 = [boardPtr]() { // surrender

    };
    if(board.drachmas() >= bribe) { // bribe
        ed.fA1 = [boardPtr, bribe]() {
            boardPtr->incDrachmas(-bribe);
        };
    }
    ed.fA2 = [boardPtr]() { // fight

    };
    board.event(eEvent::invasion, ed);
}

void eInvasionEvent::write(eWriteStream& dst) const {
    dst << mInfantry;
    dst << mCavalry;
    dst << mArchers;
}

void eInvasionEvent::read(eReadStream& src) {
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
