#ifndef EEVENTTRIGGER_H
#define EEVENTTRIGGER_H

#include "pointers/eobject.h"

#include <string.h>
#include "engine/edate.h"

class eGameEvent;

class eEventTrigger : public eObject {
public:
    eEventTrigger(const std::string& name,
                  eGameBoard& board);

    const std::string& name() const { return mName; }

    void trigger(eGameEvent& parent,
                 const eDate& date,
                 const std::string& reason);

    void write(eWriteStream& dst) const;
    void read(eReadStream& src);

    void addEvent(const stdsptr<eGameEvent>& e);
    const std::vector<stdsptr<eGameEvent>>& events() const
    { return mEvents; }
private:
    std::string mName;
    std::vector<stdsptr<eGameEvent>> mEvents;
};

#endif // EEVENTTRIGGER_H
