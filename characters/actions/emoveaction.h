#ifndef EMOVEACTION_H
#define EMOVEACTION_H

#include "echaracteraction.h"
#include "engine/eorientation.h"

#include <functional>

class eTile;

class eMoveAction : public eCharacterAction {
public:
    using eTileWalkable = std::function<bool(eTile* const)>;

    eMoveAction(eCharacter* const c,
                const eTileWalkable& tileWalkable);

    void increment();
private:
    virtual bool nextTurn(eOrientation& t) = 0;
    bool nextTurn();

    const eTileWalkable mTileWalkable;

    eOrientation mOrientation;
    eTile* mTargetTile = nullptr;

    double mStartX;
    double mStartY;
    double mTargetX;
    double mTargetY;
};

#endif // EMOVEACTION_H
