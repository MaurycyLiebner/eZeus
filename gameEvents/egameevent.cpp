#include "egameevent.h"

#include "egodvisitevent.h"

eGameEvent::eGameEvent(const eGameEventType type,
                       eGameBoard& board) :
    eObject(board), mType(type) {}

stdsptr<eGameEvent> eGameEvent::sCreate(const eGameEventType type,
                                        eGameBoard& board) {
    switch(type) {
    case eGameEventType::godVisit:
        return e::make_shared<eGodVisitEvent>(board);
    }
}
