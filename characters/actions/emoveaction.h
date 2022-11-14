#ifndef EMOVEACTION_H
#define EMOVEACTION_H

#include "echaracteraction.h"
#include "engine/eorientation.h"

class eTileBase;
class eTile;

class eMoveAction : public eCharacterAction {
public:
    eMoveAction(eCharacter* const c,
                const stdsptr<eWalkableObject>& tileWalkable);

    bool walkable(eTileBase* const tile) const;

    using eObsticleHandler = std::function<bool(eTile* const)>;
    void setObsticleHandler(const eObsticleHandler& oh);

    void increment(const int by);
protected:
    bool nextTurn();
private:
    virtual eCharacterActionState nextTurn(eOrientation& t) = 0;
    void moveBy(const double inc);
    void moveToTargetTile();

    stdsptr<eWalkableObject> mTileWalkable;

    eOrientation mOrientation;
    eTile* mTargetTile = nullptr;

    double mStartX;
    double mStartY;
    double mTargetX;
    double mTargetY;

    eObsticleHandler mObstHandler;
};

#endif // EMOVEACTION_H
