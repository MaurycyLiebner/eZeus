#include "egodattackevent.h"

#include "engine/egameboard.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "characters/actions/egodattackaction.h"

eGodAttackEvent::eGodAttackEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::godAttack, board) {}

void eGodAttackEvent::setTypes(const std::vector<eGodType>& types) {
    mTypes = types;
    const int nTypes = mTypes.size();
    if(mNextId >= nTypes) mNextId = 0;
}

void eGodAttackEvent::setRandom(const bool r) {
    mRandom = r;
}

void eGodAttackEvent::trigger() {
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

    const auto a = e::make_shared<eGodAttackAction>(god.get());
    god->setAttitude(eGodAttitude::hostile);
    god->setAction(a);
    a->increment(1);
    eEventData ed;
    ed.fTile = god->tile();
    board.event(e, ed);
}

std::string eGodAttackEvent::longName() const {
    return eLanguage::text("god_attack");
}

void eGodAttackEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mTypes.size();
    for(const auto t : mTypes) {
        dst << t;
    }
    dst << mRandom;
    dst << mNextId;
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
    src >> mRandom;
    src >> mNextId;
}

stdsptr<eGameEvent> eGodAttackEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eGodAttackEvent>(getBoard());
    c->mTypes = mTypes;
    c->mNextId = mNextId;
    c->mRandom = mRandom;
    c->setReason(reason);
    return c;
}
