#include "einvasionevent.h"

#include "engine/egameboard.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "einvasionhandler.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "einvasionwarningevent.h"

eInvasionEvent::eInvasionEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::invasion, board) {}

void eInvasionEvent::initialize(const stdsptr<eWorldCity>& city,
                                const int infantry,
                                const int cavalry,
                                const int archers) {
    mCity = city;

    mInfantry = infantry;
    mCavalry = cavalry;
    mArchers = archers;

    auto& board = getBoard();

    const auto warnTypes = {
        eInvasionWarningType::warning36,
        eInvasionWarningType::warning24,
        eInvasionWarningType::warning12,
        eInvasionWarningType::warning6,
        eInvasionWarningType::warning1
    };
    for(const auto w : warnTypes) {
        int months;
        switch(w) {
        case eInvasionWarningType::warning36:
            months = 36;
            break;
        case eInvasionWarningType::warning24:
            months = 24;
            break;
        case eInvasionWarningType::warning12:
            months = 12;
            break;
        case eInvasionWarningType::warning6:
            months = 6;
            break;
        case eInvasionWarningType::warning1:
            months = 1;
            break;
        }
        const int wdays = 31*months;
        const auto e = e::make_shared<eInvasionWarningEvent>(board);
        e->setReason(reason());
        e->initialize(w, mCity);
        addWarning(wdays, e);
    }
}

void eInvasionEvent::trigger() {
    auto& board = getBoard();
    eEventData ed;
    ed.fCity = mCity;
    ed.fType = eMessageEventType::invasion;
    const int bribe = bribeCost();
    ed.fBribe = bribe;
    ed.fReason = reason();

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

std::string eInvasionEvent::longName() const {
    auto tmpl = eLanguage::text("invasion_by");
    const auto none = eLanguage::text("none");
    const auto cstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%1", cstr);
    return tmpl;
}

void eInvasionEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst.writeCity(mCity.get());

    dst << mInfantry;
    dst << mCavalry;
    dst << mArchers;
}

void eInvasionEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });

    src >> mInfantry;
    src >> mCavalry;
    src >> mArchers;
}

stdsptr<eGameEvent> eInvasionEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eInvasionEvent>(getBoard());
    c->setReason(reason);
    c->initialize(mCity, mInfantry, mCavalry, mArchers);
    return c;
}

void eInvasionEvent::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;

    const auto& ws = warnings();
    for(const auto& w : ws) {
        const auto& ws = w.second;
        const auto iw = static_cast<eInvasionWarningEvent*>(ws.get());
        iw->setCity(c);
    }
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
