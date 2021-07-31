#ifndef EMOVEAROUNDACTION_H
#define EMOVEAROUNDACTION_H

#include "emoveaction.h"

#include <vector>

class eMoveAroundAction : public eMoveAction {
public:
    eMoveAroundAction(eCharacter* const c);
private:
    bool nextTurn(eOrientation& turn);

    std::vector<eOrientation> mTurns;
};

#endif // EMOVEAROUNDACTION_H
