#include "egodvisitevent.h"

#include "engine/egameboard.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "characters/actions/egodvisitaction.h"

eGodVisitEvent::eGodVisitEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::godVisit, board) {}

void eGodVisitEvent::setTypes(const std::vector<eGodType>& types) {
    mTypes = types;
    const int nTypes = mTypes.size();
    if(mNextId >= nTypes) mNextId = 0;
}

void eGodVisitEvent::setRandom(const bool r) {
    mRandom = r;
}

void eGodVisitEvent::trigger() {
    if(mTypes.empty()) return;
    auto& board = getBoard();
    int tid;
    const int nTypes = mTypes.size();
    if(mRandom) {
        tid = rand() % mTypes.size();
    } else {
        tid = mNextId;
        if(++mNextId >= nTypes) mNextId = 0;
    }
    const auto t = mTypes.at(tid);
    const auto god = eGod::sCreateGod(t, board);
    eEvent e;
    switch(t) {
    case eGodType::aphrodite:
        e = eEvent::aphroditeVisit;
        break;
    case eGodType::apollo:
        e = eEvent::apolloVisit;
        break;
    case eGodType::ares:
        e = eEvent::aresVisit;
        break;
    case eGodType::artemis:
        e = eEvent::artemisVisit;
        break;
    case eGodType::athena:
        e = eEvent::athenaVisit;
        break;
    case eGodType::atlas:
        e = eEvent::atlasVisit;
        break;
    case eGodType::demeter:
        e = eEvent::demeterVisit;
        break;
    case eGodType::dionysus:
        e = eEvent::dionysusVisit;
        break;
    case eGodType::hades:
        e = eEvent::hadesVisit;
        break;
    case eGodType::hephaestus:
        e = eEvent::hephaestusVisit;
        break;
    case eGodType::hera:
        e = eEvent::heraVisit;
        break;
    case eGodType::hermes:
        e = eEvent::hermesVisit;
        break;
    case eGodType::poseidon:
        e = eEvent::poseidonVisit;
        break;
    case eGodType::zeus:
        e = eEvent::zeusVisit;
        break;
    }

    const auto a = e::make_shared<eGodVisitAction>(god.get());
    god->setAction(a);
    god->setAttitude(eGodAttitude::friendly);
    a->increment(1);
    eEventData ed;
    ed.fTile = god->tile();
    board.event(e, ed);
}

void eGodVisitEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mTypes.size();
    for(const auto t : mTypes) {
        dst << t;
    }
    dst << mRandom;
    dst << mNextId;
}

void eGodVisitEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    int n;
    src >> n;
    for(int i = 0; i < n; i++) {
        eGodType t;
        src >> t;
        mTypes.push_back(t);
    }
    src >> mRandom;
    src >> mNextId;
}
