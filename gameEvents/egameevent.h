#ifndef EGAMEEVENT_H
#define EGAMEEVENT_H

#include "pointers/eobject.h"
#include "engine/edate.h"

#include <functional>

enum class eGameEventType {
    godVisit,
    godAttack,
    monsterAttack,
    invasion
};

class eGameEvent : public eObject {
public:
    using eAction = std::function<void()>;
    eGameEvent(const eGameEventType type, eGameBoard& board);

    virtual void trigger() = 0;

    static stdsptr<eGameEvent> sCreate(const eGameEventType type,
                                       eGameBoard& board);

    virtual void write(eWriteStream& dst) const { (void)dst; }
    virtual void read(eReadStream& src) { (void)src; }

    eGameEventType type() const { return mType; }
private:
    eGameEventType mType;
};

#endif // EGAMEEVENT_H
