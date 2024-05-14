#include "emonsterattackevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "characters/actions/emonsteraction.h"
#include "elanguage.h"
#include "emessages.h"

eMonsterAttackEvent::eMonsterAttackEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::monsterAttack, board) {}

void eMonsterAttackEvent::setType(const eMonsterType type) {
    mType = type;
}

void eMonsterAttackEvent::trigger() {
    auto& board = getBoard();
    const auto monster = eMonster::sCreateMonster(mType, board);

    const auto a = e::make_shared<eMonsterAction>(monster.get());
    monster->setAction(a);
    a->increment(1);
    bool validGod = false;
    const auto godType = eMonster::sMonsterSender(mType, &validGod);

    eEventData ed;
    ed.fChar = monster.get();
    ed.fTile = monster->tile();
    ed.fGod = godType;
    ed.fMonster = mType;
    board.event(eEvent::godMonsterUnleash, ed);
    board.registerAttackingMonster(monster.get());

    const auto heroType = eMonster::sSlayer(mType);
    if(!validGod) return board.allowHero(heroType);
    const auto& inst = eMessages::instance;
    const auto gm = inst.godMessages(godType);
    if(!gm) return board.allowHero(heroType);
    const auto& m = gm->fMonster;
    board.allowHero(heroType, m.fReason);
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

stdsptr<eGameEvent> eMonsterAttackEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eMonsterAttackEvent>(getBoard());
    c->mType = mType;
    c->setReason(reason);
    return c;
}
