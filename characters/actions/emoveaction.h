#ifndef EMOVEACTION_H
#define EMOVEACTION_H

#include "echaracteraction.h"
#include "engine/eorientation.h"

class eTileBase;
class eTile;

class eMoveAction : public eCharacterAction {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;

    eMoveAction(eCharacter* const c,
                const eTileWalkable& tileWalkable,
                const eAction& failAction,
                const eAction& finishAction);

    bool walkable(eTileBase* const tile) const;

    void increment(const int by);
protected:
    bool nextTurn();
private:
    virtual eCharacterActionState nextTurn(eOrientation& t) = 0;
    void moveBy(const double inc);
    void moveToTargetTile();

    const eTileWalkable mTileWalkable;

    eOrientation mOrientation;
    eTile* mTargetTile = nullptr;

    double mStartX;
    double mStartY;
    double mTargetX;
    double mTargetY;
};

#endif // EMOVEACTION_H
