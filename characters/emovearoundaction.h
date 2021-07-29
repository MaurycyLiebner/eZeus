#ifndef EMOVEAROUNDACTION_H
#define EMOVEAROUNDACTION_H

#include "echaracteraction.h"

#include "engine/eorientation.h"

class eTile;

#include <vector>

class eMoveAroundAction : public eCharacterAction {
public:
    eMoveAroundAction(eDemeter* const d);

    void increment();
private:
    bool nextTurn();

    eOrientation mOrientation;
    eTile* mTargetTile = nullptr;

    double mStartX;
    double mStartY;
    double mTargetX;
    double mTargetY;

    std::vector<eOrientation> mTurns;
};

#endif // EMOVEAROUNDACTION_H
