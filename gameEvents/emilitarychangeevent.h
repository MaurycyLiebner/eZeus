#ifndef EMILITARYCHANGEEVENT_H
#define EMILITARYCHANGEEVENT_H

#include "eeconomicmilitarychangeeventbase.h"

class eMilitaryChangeEvent : public eEconomicMilitaryChangeEventBase {
public:
    eMilitaryChangeEvent(const eGameEventBranch branch);

   void trigger() override;
   std::string longName() const override;;
};

#endif // EMILITARYCHANGEEVENT_H
