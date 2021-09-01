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

bool eMoveAction::walkable(eTileBase* const tile) const {
    return mTileWalkable(tile);
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

inline bool isEqual(const double x, const double y) {
    const double epsilon = 1e-5;
    return std::abs(x - y) <= epsilon * std::abs(x);
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
    const auto c = character();
    double x = c->x();
    double y = c->y();
    const bool xSignBefore = x - mTargetX > 0 ? true : false;
    const bool ySignBefore = y - mTargetY > 0 ? true : false;
    c->setX(x + (mTargetX - mStartX)*inc);
    c->setY(y + (mTargetY - mStartY)*inc);
    x = c->x();
    y = c->y();
    const bool xSignAfter = x - mTargetX > 0 ? true : false;
    const bool ySignAfter = y - mTargetY > 0 ? true : false;
    if(xSignAfter != xSignBefore ||
       ySignAfter != ySignBefore) {
        if(c->tile() == mTargetTile) {
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

        c->changeTile(mTargetTile);
        mTargetX = 0.5;
        mTargetY = 0.5;

        c->setX(mStartX);
        c->setY(mStartY);

        const auto cs = mTargetTile->characters();
        const auto cc = character();
        for(const auto& c : cs) {
            if(c.get() == character()) continue;
            const bool cf = c->canFight(cc);
            const bool ccf = cc->canFight(c.get());
            if(cf && ccf) {
                cc->fight(c.get());
                c->fight(cc);
                break;
            }
        }
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

    const auto c = character();
    c->setOrientation(turn);
    const auto t = c->tile();
    mTargetTile = t->neighbour<eTile>(turn);
    if(!mTargetTile || !mTileWalkable(mTargetTile)) {
        setState(eCharacterActionState::failed);
        return false;
    }
    mStartX = c->x();
    mStartY = c->y();
    mOrientation = turn;
    orientationToTargetCoords(turn, mTargetX, mTargetY);
    if(isEqual(mStartX, mTargetX) &&
       isEqual(mStartY, mTargetY)) {
        return nextTurn();
    }
    return true;
}
