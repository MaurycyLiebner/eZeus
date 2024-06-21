#ifndef EHUNTACTION_H
#define EHUNTACTION_H

#include "eactionwithcomeback.h"

#include "characters/ehunter.h"

class eHuntingLodge;

class eHuntAction : public eActionWithComeback {
public:
    eHuntAction(eHuntingLodge* const b,
                eCharacter* const c);
    eHuntAction(eCharacter* const c);

    void increment(const int by) override;
    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void findResourceDecision();
    void goBackDecision();
    void waitDecision();

    eHuntingLodge* mLodge = nullptr;
    eHunter* mHunter = nullptr;

    bool mNoResource = false;
};

#endif // EHUNTACTION_H
