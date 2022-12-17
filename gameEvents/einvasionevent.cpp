#include "einvasionevent.h"

#include "engine/egameboard.h"
#include "einvasionhandler.h"

eInvasionEvent::eInvasionEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::invasion, board) {}

void eInvasionEvent::initialize(const int stage,
                                const stdsptr<eWorldCity>& city,
                                const int infantry,
                                const int cavalry,
                                const int archers) {
    mStage = stage;
    mCity = city;

    mInfantry = infantry;
    mCavalry = cavalry;
    mArchers = archers;
}

void eInvasionEvent::trigger() {
    auto& board = getBoard();
    eEventData ed;
    ed.fCity = mCity;
    if(mStage >= 5) {
        ed.fType = eMessageEventType::invasion;
        const int bribe = bribeCost();
        ed.fBribe = bribe;

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
    } else {
        int months;
        if(mStage == 1) {
            months = 12;
            board.event(eEvent::invasion24, ed);
        } else if(mStage == 2) {
            months = 6;
            board.event(eEvent::invasion12, ed);
        } else if(mStage == 3) {
            months = 5;
            board.event(eEvent::invasion6, ed);
        } else if(mStage == 4) {
            months = 1;
            board.event(eEvent::invasion1, ed);
        } else {
            months = 0;
        }
        board.planInvasion(mStage, months, mInfantry,
                           mCavalry, mArchers);
    }
}

void eInvasionEvent::write(eWriteStream& dst) const {
    dst.writeCity(mCity.get());

    dst << mStage;
    dst << mInfantry;
    dst << mCavalry;
    dst << mArchers;
}

void eInvasionEvent::read(eReadStream& src) {
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });

    src >> mStage;
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
