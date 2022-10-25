#include "egodvisitevent.h"

#include "engine/egameboard.h"
#include "characters/actions/egodvisitaction.h"

eGodVisitEvent::eGodVisitEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::godVisit, board) {}

void eGodVisitEvent::setTypes(const std::vector<eGodType>& types) {
    mTypes = types;
}

void eGodVisitEvent::trigger() {
    if(mTypes.empty()) return;
    auto& board = getBoard();
    const int tid = rand() % mTypes.size();
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

    const auto a = e::make_shared<eGodVisitAction>(
                       god.get(), []() {}, []() {});
    god->setAction(a);
    a->increment(1);
    board.event(e, god->tile());
}

void eGodVisitEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mTypes.size();
    for(const auto t : mTypes) {
        dst << t;
    }
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
}
