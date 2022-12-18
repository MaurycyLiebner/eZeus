#include "egameevent.h"

#include "egodvisitevent.h"
#include "egodattackevent.h"
#include "emonsterattackevent.h"
#include "einvasionevent.h"
#include "epaytributeevent.h"
#include "egrantrequestevent.h"
#include "egiftevent.h"

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
    case eGameEventType::invasion:
        return e::make_shared<eInvasionEvent>(board);
    case eGameEventType::payTribute:
        return e::make_shared<ePayTributeEvent>(board);
    case eGameEventType::grantRequest:
        return e::make_shared<eGrantRequestEvent>(board);
    case eGameEventType::gift:
        return e::make_shared<eGiftEvent>(board);
    }
    return nullptr;
}
