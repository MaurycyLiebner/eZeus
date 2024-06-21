#include "emonsterunleashedevent.h"

#include "elanguage.h"
#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "emessages.h"

eMonsterUnleashedEvent::eMonsterUnleashedEvent(const eGameEventBranch branch) :
    eMonsterInvasionEventBase(eGameEventType::monsterUnleashed, branch) {}

void eMonsterUnleashedEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;

    bool validGod = false;
    const auto godType = eMonster::sMonsterSender(type(), &validGod);
    if(!validGod) return;

    const auto monster = triggerBase();

    eEventData ed;
    ed.fChar = monster;
    ed.fTile = monster->tile();
    ed.fGod = godType;
    ed.fMonster = type();
    board->event(eEvent::godMonsterUnleash, ed);

    const auto& inst = eMessages::instance;
    const auto gm = inst.godMessages(godType);
    const auto& m = gm->fMonster;
    const auto heroType = eMonster::sSlayer(type());
    board->allowHero(heroType, m.fReason);
}

std::string eMonsterUnleashedEvent::longName() const {
    return eLanguage::text("monster_unleash_long_name");
}
