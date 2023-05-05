#include "emonsterattackevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "characters/actions/emonsteraction.h"
#include "elanguage.h"
#include "buildings/eheroshall.h"

eMonsterAttackEvent::eMonsterAttackEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::monsterAttack, board) {}

void eMonsterAttackEvent::setType(const eMonsterType type) {
    mType = type;
}

void eMonsterAttackEvent::trigger() {
    auto& board = getBoard();
    const auto monster = eMonster::sCreateMonster(mType, board);
    eEvent e;
    switch(mType) {
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

    const auto heroType = eMonster::sSlayer(mType);
    board.allowHero(heroType);
}

std::string eMonsterAttackEvent::longName() const {
    return eLanguage::text("monster_attack");
}

void eMonsterAttackEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mType;
}

void eMonsterAttackEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mType;
}
