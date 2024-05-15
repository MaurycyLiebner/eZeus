#include "eeventtrigger.h"

#include "egameevent.h"
#include "evectorhelpers.h"

eEventTrigger::eEventTrigger(const std::string& name,
                             eGameBoard& board) :
    eObject(board),
    mName(name) {}

void eEventTrigger::trigger(eGameEvent& parent,
                            const eDate& date,
                            const std::string& reason) {
    for(const auto& e : mEvents) {
        const auto c = e->makeCopy(reason);
        if(!c) continue;
        c->setIsMainEvent();
        const int delay = e->period();
        const auto d = date + delay;
        c->initializeDate(d);
        parent.addConsequence(c);
    }
}

void eEventTrigger::write(eWriteStream& dst) const {
    dst << mEvents.size();
    for(const auto& c : mEvents) {
        dst << c->type();
        c->write(dst);
    }
}

void eEventTrigger::read(eReadStream& src) {
    int ncs;
    src >> ncs;
    for(int i = 0; i < ncs; i++) {
        eGameEventType type;
        src >> type;
        const auto e = eGameEvent::sCreate(type, getBoard());
        e->read(src);
        mEvents.emplace_back(e);
    }
}

void eEventTrigger::addEvent(const stdsptr<eGameEvent>& e) {
    mEvents.push_back(e);
}

void eEventTrigger::removeEvent(const stdsptr<eGameEvent>& e) {
    eVectorHelpers::remove(mEvents, e);
}
