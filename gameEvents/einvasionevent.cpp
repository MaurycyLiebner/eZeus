#include "einvasionevent.h"

#include "engine/egameboard.h"

eInvasionEvent::eInvasionEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::invasion, board) {}

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



    board.event(eEvent::invasion, nullptr, mCity.get(), bribe);
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
