#ifndef EMOVEAROUNDACTION_H
#define EMOVEAROUNDACTION_H

#include "emoveaction.h"

#include <vector>

class eMoveAroundAction : public eMoveAction {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    eMoveAroundAction(eCharacter* const c,
                      const eAction& failAction,
                      const eAction& finishAction,
                      const int startX, const int startY,
                      const eTileWalkable& walkable = sDefaultWalkable);

    static bool sDefaultWalkable(eTileBase* const tile);
    static bool sFertileWalkable(eTileBase* const tile);

    void increment(const int by);

    void setTime(const int t);
private:
    eCharacterActionState nextTurn(eOrientation& turn);
    eCharacterActionState nextTurn(eOrientation& turn,
                                   const int n, const int i);

    int mStartTX;
    int mStartTY;

    const int mMaxDist = 5;
    int mRemTime{__INT_MAX__};
};

#endif // EMOVEAROUNDACTION_H
