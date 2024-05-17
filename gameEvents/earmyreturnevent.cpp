#include "earmyreturnevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"
#include "buildings/eheroshall.h"

eArmyReturnEvent::eArmyReturnEvent(
        const eGameEventBranch branch,
        eGameBoard& board) :
    eGameEvent(eGameEventType::armyReturnEvent, branch, board) {}

void eArmyReturnEvent::initialize(
        const eEnlistedForces& forces,
        const stdsptr<eWorldCity>& city) {
    mForces = forces;
    mCity = city;
}

void eArmyReturnEvent::trigger() {
    if(!mCity) return;
    auto& board = getBoard();

    for(const auto& s : mForces.fSoldiers) {
        s->backFromAbroad();
    }

    for(const auto h : mForces.fHeroes) {
        const auto hh = board.heroHall(h);
        if(!hh) continue;
        hh->setHeroOnQuest(false);
    }

    for(const auto& a : mForces.fAllies) {
        a->setAbroad(false);
    }

    eEventData ed;
    ed.fCity = mCity;
    board.event(eEvent::armyReturns, ed);
}

std::string eArmyReturnEvent::longName() const {
    return eLanguage::text("army_returns_event_long_name");
}

void eArmyReturnEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    mForces.write(dst);
    dst.writeCity(mCity.get());
}

void eArmyReturnEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    auto& board = getBoard();
    mForces.read(board, src);
    src.readCity(&board, [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

stdsptr<eGameEvent> eArmyReturnEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eArmyReturnEvent>(branch(), getBoard());
    c->mForces = mForces;
    c->mCity = mCity;
    c->setReason(reason);
    return c;
}
