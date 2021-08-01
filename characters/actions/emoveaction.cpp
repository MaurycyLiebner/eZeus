#include "emoveaction.h"

#include "../echaracter.h"

eMoveAction::eMoveAction(eCharacter* const c,
                         const eTileWalkable& tileWalkable,
                         const eAction& failAction,
                         const eAction& finishAction) :
    eCharacterAction(c, failAction, finishAction),
    mTileWalkable(tileWalkable) {
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

void eMoveAction::increment(const int by) {
    switch(state()) {
    case eCharacterActionState::failed:
    case eCharacterActionState::finished:
        return;
    case eCharacterActionState::running:
        break;
    }

    if(!mTargetTile) {
        if(nextTurn()) increment(by);
        return;
    }

    const double inc = 0.01 * by;
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
    const auto r = nextTurn(turn);
    setState(r);
    switch(r) {
    case eCharacterActionState::failed:
    case eCharacterActionState::finished:
        return false;
    case eCharacterActionState::running:
        break;
    }

    mCharacter->setOrientation(turn);
    const auto t = mCharacter->tile();
    mTargetTile = t->neighbour(turn);
    if(!mTargetTile || !mTileWalkable(mTargetTile)) {
        setState(eCharacterActionState::failed);
        return false;
    }
    mStartX = mCharacter->x();
    mStartY = mCharacter->y();
    mOrientation = turn;
    orientationToTargetCoords(turn, mTargetX, mTargetY);
    return true;
}
