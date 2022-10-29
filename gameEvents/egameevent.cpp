#include "egameevent.h"

#include "egodvisitevent.h"
#include "egodattackevent.h"
#include "emonsterattackevent.h"

eGameEvent::eGameEvent(const eGameEventType type,
                       eGameBoard& board) :
    eObject(board), mType(type) {}

stdsptr<eGameEvent> eGameEvent::sCreate(const eGameEventType type,
                                        eGameBoard& board) {
    switch(type) {
    case eGameEventType::godVisit:
        return e::make_shared<eGodVisitEvent>(board);
    case eGameEventType::godAttack:
        return e::make_shared<eGodAttackEvent>(board);
    case eGameEventType::monsterAttack:
        return e::make_shared<eMonsterAttackEvent>(board);
    }
}
