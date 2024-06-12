#include "emonsterinvasioneventbase.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "characters/actions/emonsteraction.h"
#include "emonsterinvasionevent.h"

eMonsterInvasionEventBase::eMonsterInvasionEventBase(const eGameEventType type,
        const eGameEventBranch branch) :
    eGameEvent(type, branch) {}


void eMonsterInvasionEventBase::setType(const eMonsterType type) {
    mType = type;
    const auto& ws = warnings();
    for(const auto& w : ws) {
        const auto& ws = w.second;
        const auto iw = dynamic_cast<eMonsterInvasionWarningEvent*>(ws.get());
        if(!iw) continue;
        iw->setMonster(type);
    }
}

void eMonsterInvasionEventBase::setPointId(const int p) {
    mPointId = p;
}

void eMonsterInvasionEventBase::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mType;
    dst << mPointId;
}

void eMonsterInvasionEventBase::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mType;
    src >> mPointId;
}

eMonster* eMonsterInvasionEventBase::triggerBase() const {
    const auto board = gameBoard();
    if(!board) return nullptr;
    const auto monster = eMonster::sCreateMonster(mType, *board);
    board->registerMonster(monster.get());
    monster->setPlayerId(2);

    const auto a = e::make_shared<eMonsterAction>(monster.get());
    monster->setAction(a);
    a->increment(1);

    return monster.get();
}
