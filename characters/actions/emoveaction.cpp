#include "emoveaction.h"

#include "../echaracter.h"
#include "walkable/ewalkableobject.h"

#include "vec2.h"

eMoveAction::eMoveAction(eCharacter* const c,
                         const stdsptr<eWalkableObject>& tileWalkable,
                         const eCharActionType type) :
    eCharacterAction(c, type),
    mTileWalkable(tileWalkable) {
    mStartX = c->x();
    mStartY = c->y();
    mOrientation = c->orientation();
}

eMoveAction::eMoveAction(eCharacter* const c,
                         const eCharActionType type) :
    eMoveAction(c, nullptr, type) {}

bool eMoveAction::walkable(eTileBase* const tile) const {
    return mTileWalkable->walkable(tile);
}

void eMoveAction::setObsticleHandler(const stdsptr<eObsticleHandler>& oh) {
    mObstHandler = oh;
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

    const auto c = character();
    moveBy(c->speed()*0.005 * by);
}

void eMoveAction::read(eReadStream& src) {
    eCharacterAction::read(src);
    mTileWalkable = src.readWalkable();
    src >> mOrientation;
    mTargetTile = src.readTile(board());
    src >> mStartX;
    src >> mStartY;
    src >> mTargetX;
    src >> mTargetY;
    mObstHandler = src.readObsticleHandler(board());
}

void eMoveAction::write(eWriteStream& dst) const {
    eCharacterAction::write(dst);
    dst.writeWalkable(mTileWalkable.get());
    dst << mOrientation;
    dst.writeTile(mTargetTile);
    dst << mStartX;
    dst << mStartY;
    dst << mTargetX;
    dst << mTargetY;
    dst.writeObsticleHandler(mObstHandler.get());
}

void eMoveAction::moveBy(const double inc) {
    const auto c = character();
    const double x = c->x();
    const double y = c->y();

    vec2d moveVec(mTargetX - x,
                  mTargetY - y);
    const double dist = moveVec.length();
    if(dist > inc) {
        moveVec.normalize();
        moveVec *= inc;
        c->setX(x + moveVec.x);
        c->setY(y + moveVec.y);
    } else {
        c->setX(mTargetX);
        c->setY(mTargetY);
        const stdptr<eMoveAction> tptr(this);
        const auto t = mTargetTile;
        moveToTargetTile();
        if(tptr && t != mTargetTile) moveBy(inc - dist);
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
    if(!mTargetTile) {
        setState(eCharacterActionState::failed);
        return false;
    }
    if(!walkable(mTargetTile)) {
        if(mObstHandler && mObstHandler->handle(mTargetTile)) {
        } else {
            setState(eCharacterActionState::failed);
            return false;
        }
    }
    mStartX = c->x();
    mStartY = c->y();
    mOrientation = turn;
    orientationToTargetCoords(turn, mTargetX, mTargetY);
    if(isEqual(mStartX, mTargetX) &&
       isEqual(mStartY, mTargetY)) {
        moveToTargetTile();
    }
    return true;
}

void eMoveAction::moveToTargetTile() {
    if(!mTargetTile) {
        setState(eCharacterActionState::failed);
        return;
    }
    const auto c = character();
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

    const bool prepend = mOrientation == eOrientation::bottomLeft ||
                         mOrientation == eOrientation::bottom ||
                         mOrientation == eOrientation::bottomRight;
    c->changeTile(mTargetTile, prepend);
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
