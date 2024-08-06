#ifndef ETRADESHUTDOWNEVENT_H
#define ETRADESHUTDOWNEVENT_H

#include "ebasiccityevent.h"

class eTradeShutDownEvent : public eBasicCityEvent {
public:
    eTradeShutDownEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;;
};

#endif // ETRADESHUTDOWNEVENT_H
