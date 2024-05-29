#ifndef EMILITARYCHANGEEVENT_H
#define EMILITARYCHANGEEVENT_H

#include "eeconomicmilitarychangeeventbase.h"

class eMilitaryChangeEvent : public eEconomicMilitaryChangeEventBase {
public:
    eMilitaryChangeEvent(const eGameEventBranch branch,
                         eGameBoard& board);

   void trigger() override;
   std::string longName() const override;;

   stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
};

#endif // EMILITARYCHANGEEVENT_H
