#ifndef EMOVEAROUNDACTION_H
#define EMOVEAROUNDACTION_H

#include "emoveaction.h"

#include "walkable/ewalkableobject.h"

#include <vector>

class eMoveAroundAction : public eMoveAction {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    eMoveAroundAction(eCharacter* const c,
                      const int startX, const int startY,
                      const stdsptr<eWalkableObject>& walkable =
                            eWalkableObject::sCreateDefault());

    void increment(const int by);

    void setTime(const int t);

    void setMaxDistance(const int md);
private:
    eCharacterActionState nextTurn(eOrientation& turn);

    int mStartTX;
    int mStartTY;

    int mMaxDist = 5;
    int mRemTime{__INT_MAX__};
};

#endif // EMOVEAROUNDACTION_H
