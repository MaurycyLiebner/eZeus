#ifndef EMOVEAROUNDACTION_H
#define EMOVEAROUNDACTION_H

#include "emoveaction.h"

#include "walkable/ewalkableobject.h"
#include "elimits.h"
#include <vector>

class eMoveAroundAction : public eMoveAction {
public:
    eMoveAroundAction(eCharacter* const c,
                      const int startX, const int startY,
                      const stdsptr<eWalkableObject>& walkable =
                            eWalkableObject::sCreateDefault());
    eMoveAroundAction(eCharacter* const c);

    void increment(const int by) override;

    void setTime(const int t);

    void setMaxDistance(const int md);

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    eCharacterActionState nextTurn(eOrientation& turn) override;

    int mStartTX;
    int mStartTY;

    int mMaxDist = 5;
    int mRemTime{__INT_MAX__};
};

#endif // EMOVEAROUNDACTION_H
