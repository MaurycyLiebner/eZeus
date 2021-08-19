#ifndef EMOVEAROUNDACTION_H
#define EMOVEAROUNDACTION_H

#include "emoveaction.h"

#include <vector>

class eMoveAroundAction : public eMoveAction {
public:
    eMoveAroundAction(eCharacter* const c);
private:
    eCharacterActionState nextTurn(eOrientation& turn);
    eCharacterActionState nextTurn(eOrientation& turn,
                                   const int n, const int i);

    int mStartTX;
    int mStartTY;

    const int mMaxDist = 5;
};

#endif // EMOVEAROUNDACTION_H
