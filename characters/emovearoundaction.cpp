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
        if(mDirX == 0) {
            if(mDirY == 1) {
                mStartX = 0.75;
                mStartY = 0.25;
            } else if(mDirY == -1) {
                mStartX = 0.25;
                mStartY = 0.75;
            }
        } else if(mDirY == 0) {
            if(mDirX == 1) {
                mStartX = 0.25;
                mStartY = 0.25;
            } else if(mDirX == -1) {
                mStartX = 0.75;
                mStartY = 0.75;
            }
        } else if(mDirX == 1) {
            if(mDirY == 1) {
                mStartX = 0.5;
                mStartY = 0;
            } else if(mDirY == -1) {
                mStartX = 0;
                mStartY = 0.5;
            }
        } else if(mDirX == -1) {
            if(mDirY == 1) {
                mStartX = 1;
                mStartY = 0.5;
            } else if(mDirY == -1) {
                mStartX = 0.5;
                mStartY = 1;
            }
        }

        mCharacter->tile()->removeDemeter(mCharacter);
        mCharacter->setTile(mTargetTile);
        mTargetTile->addDemeter(mCharacter);
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
    mDirX = mTargetTile->x() - t->x();
    mDirY = mTargetTile->y() - t->y();
    if(mDirX == 0) {
        if(mDirY == 1) {
            mTargetX = 0.25;
            mTargetY = 0.75;
        } else if(mDirY == -1) {
            mTargetX = 0.75;
            mTargetY = 0.25;
        }
    } else if(mDirY == 0) {
        if(mDirX == 1) {
            mTargetX = 0.75;
            mTargetY = 0.75;
        } else if(mDirX == -1) {
            mTargetX = 0.25;
            mTargetY = 0.25;
        }
    } else if(mDirX == 1) {
        if(mDirY == 1) {
            mTargetX = 0.5;
            mTargetY = 1;
        } else if(mDirY == -1) {
            mTargetX = 1;
            mTargetY = 0.5;
        }
    } else if(mDirX == -1) {
        if(mDirY == 1) {
            mTargetX = 0;
            mTargetY = 0.5;
        } else if(mDirY == -1) {
            mTargetX = 0.5;
            mTargetY = 0;
        }
    }
    return true;
}
