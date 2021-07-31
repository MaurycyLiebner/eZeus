#include "emoveaction.h"

#include "../echaracter.h"

eMoveAction::eMoveAction(eCharacter* const c,
                         const eTileWalkable& tileWalkable,
                         const eFailAction& failAction) :
    eCharacterAction(c),
    mTileWalkable(tileWalkable),
    mFailAction(failAction) {
    mStartX = c->x();
    mStartY = c->y();
    mOrientation = c->orientation();
}

void orientationToTargetCoords(const eOrientation o,
                               double& targetX,
                               double& targetY) {
    switch(o) {
    case eOrientation::topRight:
        targetX = 0.5;
        targetY = 0;
        break;
    case eOrientation::right:
        targetX = 1;
        targetY = 0;
        break;
    case eOrientation::bottomRight:
        targetX = 1;
        targetY = 0.5;
        break;
    case eOrientation::bottom:
        targetX = 1;
        targetY = 1;
        break;
    case eOrientation::bottomLeft:
        targetX = 0.5;
        targetY = 1;
        break;
    case eOrientation::left:
        targetX = 0;
        targetY = 1;
        break;
    case eOrientation::topLeft:
        targetX = 0;
        targetY = 0.5;
        break;
    case eOrientation::top:
        targetX = 0;
        targetY = 0;
        break;
    }
}

void eMoveAction::increment() {
    if(!mTargetTile) {
        if(nextTurn()) increment();
        return;
    }

    const double inc = 0.01;
    double x = mCharacter->x();
    double y = mCharacter->y();
    const bool xSignBefore = x - mTargetX > 0 ? true : false;
    const bool ySignBefore = y - mTargetY > 0 ? true : false;
    mCharacter->setX(x + (mTargetX - mStartX)*inc);
    mCharacter->setY(y + (mTargetY - mStartY)*inc);
    x = mCharacter->x();
    y = mCharacter->y();
    const bool xSignAfter = x - mTargetX > 0 ? true : false;
    const bool ySignAfter = y - mTargetY > 0 ? true : false;
    if(xSignAfter != xSignBefore ||
       ySignAfter != ySignBefore) {
        if(mCharacter->tile() == mTargetTile) {
            nextTurn();
            return;
        }
        {
            double targetX;
            double targetY;
            orientationToTargetCoords(mOrientation, targetX, targetY);
            mStartX = 1 - targetX;
            mStartY = 1 - targetY;
        }

        mCharacter->tile()->removeCharacter(mCharacter);
        mCharacter->setTile(mTargetTile);
        mTargetTile->addCharacter(mCharacter);
        mTargetX = 0.5;
        mTargetY = 0.5;

        mCharacter->setX(mStartX);
        mCharacter->setY(mStartY);
    }
}

bool eMoveAction::nextTurn() {
    eOrientation turn;
    const bool r = nextTurn(turn);
    if(!r) {
        mFailAction();
        return false;
    }

    mCharacter->setOrientation(turn);
    const auto t = mCharacter->tile();
    mTargetTile = t->neighbour(turn);
    if(!mTargetTile) {
        mFailAction();
        return false;
    }
    if(!mTileWalkable(mTargetTile)) {
        mFailAction();
        return false;
    }
    mStartX = mCharacter->x();
    mStartY = mCharacter->y();
    mOrientation = turn;
    orientationToTargetCoords(turn, mTargetX, mTargetY);
    return true;
}
