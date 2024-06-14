#ifndef EECONOMICCHANGEEVENT_H
#define EECONOMICCHANGEEVENT_H

#include "eeconomicmilitarychangeeventbase.h"

class eEconomicChangeEvent : public eEconomicMilitaryChangeEventBase {
public:
    eEconomicChangeEvent(const eGameEventBranch branch);

   void trigger() override;
   std::string longName() const override;
};

#endif // EECONOMICCHANGEEVENT_H
