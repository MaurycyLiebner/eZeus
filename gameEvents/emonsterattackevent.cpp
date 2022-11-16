#include "emonsterattackevent.h"

#include "engine/egameboard.h"
#include "characters/actions/emonsteraction.h"

eMonsterAttackEvent::eMonsterAttackEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::monsterAttack, board) {}

void eMonsterAttackEvent::setTypes(const std::vector<eMonsterType>& types) {
    mTypes = types;
    const int nTypes = mTypes.size();
    if(mNextId >= nTypes) mNextId = 0;
}

void eMonsterAttackEvent::setRandom(const bool r) {
    mRandom = r;
}

void eMonsterAttackEvent::trigger() {
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
    const auto monster = eMonster::sCreateMonster(t, board);
    eEvent e;
    switch(t) {
    case eMonsterType::calydonianBoar:
        e = eEvent::calydonianBoarInvasion;
        break;
    case eMonsterType::cerberus:
        e = eEvent::cerberusInvasion;
        break;
    case eMonsterType::chimera:
        e = eEvent::chimeraInvasion;
        break;
    case eMonsterType::cyclops:
        e = eEvent::cyclopsInvasion;
        break;
    case eMonsterType::dragon:
        e = eEvent::dragonInvasion;
        break;
    case eMonsterType::echidna:
        e = eEvent::echidnaInvasion;
        break;
    case eMonsterType::harpies:
        e = eEvent::harpiesInvasion;
        break;
    case eMonsterType::hector:
        e = eEvent::hectorInvasion;
        break;
    case eMonsterType::hydra:
        e = eEvent::hydraInvasion;
        break;
    case eMonsterType::kraken:
        e = eEvent::krakenInvasion;
        break;
    case eMonsterType::maenads:
        e = eEvent::maenadsInvasion;
        break;
    case eMonsterType::medusa:
        e = eEvent::medusaInvasion;
        break;
    case eMonsterType::minotaur:
        e = eEvent::minotaurInvasion;
        break;
    case eMonsterType::scylla:
        e = eEvent::scyllaInvasion;
        break;
    case eMonsterType::sphinx:
        e = eEvent::sphinxInvasion;
        break;
    case eMonsterType::talos:
        e = eEvent::talosInvasion;
        break;
    }

    const auto a = e::make_shared<eMonsterAction>(monster.get());
    monster->setAction(a);
    a->increment(1);
    eEventData ed;
    ed.fTile = monster->tile();
    board.event(e, ed);
}

void eMonsterAttackEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mTypes.size();
    for(const auto t : mTypes) {
        dst << t;
    }
    dst << mRandom;
    dst << mNextId;
}

void eMonsterAttackEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    int n;
    src >> n;
    for(int i = 0; i < n; i++) {
        eMonsterType t;
        src >> t;
        mTypes.push_back(t);
    }
    src >> mRandom;
    src >> mNextId;
}
