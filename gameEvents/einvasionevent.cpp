#include "einvasionevent.h"

#include "engine/egameboard.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "einvasionhandler.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "einvasionwarningevent.h"
#include "audio/emusic.h"

eInvasionEvent::eInvasionEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::invasion, branch) {
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
        const int daysBefore = 31*months;
        const auto e = e::make_shared<eInvasionWarningEvent>(
                           eGameEventBranch::child);
        e->initialize(w, mCity);
        addWarning(daysBefore, e);
    }
}

eInvasionEvent::~eInvasionEvent() {
    const auto board = gameBoard();
    if(board) board->removeInvasion(this);
}

void eInvasionEvent::initialize(const stdsptr<eWorldCity>& city,
                                const int infantry,
                                const int cavalry,
                                const int archers) {
    setCity(city);

    mInfantry = infantry;
    mCavalry = cavalry;
    mArchers = archers;
}

void eInvasionEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;
    board->removeInvasion(this);
    eEventData ed;
    ed.fCity = mCity;
    ed.fType = eMessageEventType::invasion;
    const int bribe = bribeCost();
    ed.fBribe = bribe;
    ed.fReason = reason();

    const auto city = mCity;
    ed.fA0 = [board, city]() { // surrender
        eEventData ed;
        ed.fCity = city;
        board->event(eEvent::invasionDefeat, ed);
        board->updateMusic();
    };
    if(board->drachmas() >= bribe) { // bribe
        ed.fA1 = [board, bribe, city]() {
            board->incDrachmas(-bribe);
            eEventData ed;
            ed.fCity = city;
            board->event(eEvent::invasionBribed, ed);
            board->updateMusic();
        };
    }
    const int infantry = mInfantry;
    const int cavalry = mCavalry;
    const int archers = mArchers;
    const auto tile = board->landInvasionTile(mInvasionPoint);
    ed.fTile = tile;
    ed.fA2 = [board, tile, city, infantry, cavalry, archers]() { // fight
        if(!tile) return;
        const auto eh = new eInvasionHandler(*board, city);
        eh->initialize(tile, infantry, cavalry, archers);
    };
    board->event(eEvent::invasion, ed);
    eMusic::playRandomBattleMusic();
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

    dst << mInvasionPoint;

    dst << mWarned;
    mFirstWarning.write(dst);
}

void eInvasionEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src.readCity(gameBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });

    src >> mInfantry;
    src >> mCavalry;
    src >> mArchers;

    src >> mInvasionPoint;

    src >> mWarned;
    mFirstWarning.read(src);
}

stdsptr<eGameEvent> eInvasionEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eInvasionEvent>(branch());
    c->setGameBoard(gameBoard());
    c->setWorldBoard(worldBoard());
    c->initialize(mCity, mInfantry, mCavalry, mArchers);
    c->setReason(reason);
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

void eInvasionEvent::setFirstWarning(const eDate& w) {
    mFirstWarning = w;
    mWarned = true;
    const auto board = gameBoard();
    if(!board) return;
    board->addInvasion(this);
}

int eInvasionEvent::bribeCost() const {
    const auto board = gameBoard();
    if(!board) return 0;
    const auto diff = board->difficulty();
    const int rt = eDifficultyHelpers::soliderBribe(
                       diff, eCharacterType::rockThrower);
    const int ht = eDifficultyHelpers::soliderBribe(
                       diff, eCharacterType::hoplite);
    const int hm = eDifficultyHelpers::soliderBribe(
                       diff, eCharacterType::horseman);
    const int bribe = rt*mArchers + ht*mInfantry + hm*mCavalry;
    return bribe;
}
