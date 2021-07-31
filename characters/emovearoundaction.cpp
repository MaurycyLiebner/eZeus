#include "emovearoundaction.h"

#include "edemeter.h"

eMoveAroundAction::eMoveAroundAction(eDemeter* const d) :
    eCharacterAction(d) {
    for(int i = 0; i < 100; i++) {
        const int oid = rand() % 8;
        const auto o = static_cast<eOrientation>(oid);
        mTurns.push_back(o);
    }
    mStartX = d->x();
    mStartY = d->y();
    mOrientation = d->orientation();
}

void orientationToTargetCoords(const eOrientation o,
                               double& targetX, double& targetY) {
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

void eMoveAroundAction::increment() {
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

bool eMoveAroundAction::nextTurn() {
    if(mTurns.empty()) return false;
    const auto o = mTurns.back();
    mCharacter->setOrientation(o);
    mTurns.pop_back();

    const auto t = mCharacter->tile();
    mTargetTile = t->neighbour(o);
    if(!mTargetTile) return nextTurn();
    mStartX = mCharacter->x();
    mStartY = mCharacter->y();
    mOrientation = o;
    orientationToTargetCoords(o, mTargetX, mTargetY);

    return true;
}
