#ifndef ESICKDISGRUNTLEDACTION_H
#define ESICKDISGRUNTLEDACTION_H

#include "eactionwithcomeback.h"

class eSmallHouse;

class eSickDisgruntledAction : public eActionWithComeback {
public:
    eSickDisgruntledAction(eCharacter* const c,
                           eSmallHouse* const ch);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
protected:
    void patrol();
    void goBackDecision(const stdsptr<eWalkableObject>& w =
                            eWalkableObject::sCreateRoadAvenue());
private:
    eSmallHouse* mBuilding = nullptr;

    bool mGoBackNext = false;
};

#endif // ESICKDISGRUNTLEDACTION_H
