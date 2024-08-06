#ifndef EDEMANDCHANGEEVENT_H
#define EDEMANDCHANGEEVENT_H

#include "esupplydemandchangeevent.h"

class eDemandChangeEvent : public eSupplyDemandChangeEvent {
public:
    eDemandChangeEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;
};

#endif // EDEMANDCHANGEEVENT_H
