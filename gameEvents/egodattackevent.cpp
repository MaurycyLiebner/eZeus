#include "egodattackevent.h"

#include "engine/egameboard.h"
#include "characters/actions/egodattackaction.h"

eGodAttackEvent::eGodAttackEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::godAttack, board) {}

void eGodAttackEvent::setTypes(const std::vector<eGodType>& types) {
    mTypes = types;
}

void eGodAttackEvent::trigger() {
    if(mTypes.empty()) return;
    auto& board = getBoard();
    const int tid = rand() % mTypes.size();
    const auto t = mTypes.at(tid);
    const auto god = eGod::sCreateGod(t, board);
    eEvent e;
    switch(t) {
    case eGodType::aphrodite:
        e = eEvent::aphroditeInvasion;
        break;
    case eGodType::apollo:
        e = eEvent::apolloInvasion;
        break;
    case eGodType::ares:
        e = eEvent::aresInvasion;
        break;
    case eGodType::artemis:
        e = eEvent::artemisInvasion;
        break;
    case eGodType::athena:
        e = eEvent::athenaInvasion;
        break;
    case eGodType::atlas:
        e = eEvent::atlasInvasion;
        break;
    case eGodType::demeter:
        e = eEvent::demeterInvasion;
        break;
    case eGodType::dionysus:
        e = eEvent::dionysusInvasion;
        break;
    case eGodType::hades:
        e = eEvent::hadesInvasion;
        break;
    case eGodType::hephaestus:
        e = eEvent::hephaestusInvasion;
        break;
    case eGodType::hera:
        e = eEvent::heraInvasion;
        break;
    case eGodType::hermes:
        e = eEvent::hermesInvasion;
        break;
    case eGodType::poseidon:
        e = eEvent::poseidonInvasion;
        break;
    case eGodType::zeus:
        e = eEvent::zeusInvasion;
        break;
    }

    const auto a = e::make_shared<eGodAttackAction>(
                       god.get(), []() {}, []() {});
    god->setAction(a);
    a->increment(1);
    board.event(e, god->tile());
}

void eGodAttackEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mTypes.size();
    for(const auto t : mTypes) {
        dst << t;
    }
}

void eGodAttackEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    int n;
    src >> n;
    for(int i = 0; i < n; i++) {
        eGodType t;
        src >> t;
        mTypes.push_back(t);
    }
}
