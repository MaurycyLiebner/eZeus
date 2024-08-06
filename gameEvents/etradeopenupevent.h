#ifndef ETRADEOPENUPEVENT_H
#define ETRADEOPENUPEVENT_H

#include "ebasiccityevent.h"

class eTradeOpenUpEvent : public eBasicCityEvent {
public:
    eTradeOpenUpEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;;
};

#endif // ETRADEOPENUPEVENT_H
