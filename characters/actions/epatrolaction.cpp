#include "epatrolaction.h"

#include "../echaracter.h"
#include "engine/etile.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"

ePatrolAction::ePatrolAction(eCharacter* const c,
                             const eAction& failAction,
                             const eAction& finishAction) :
    eMoveAction(c,
                [](eTile* const tile) {
                    return tile->hasRoad();
                },
                failAction, finishAction) {
    mStartX = c->x();
    mStartY = c->y();
    mO = c->orientation();
}

void ePatrolAction::increment(const int by) {
    if(mGoBackAction) {
        mGoBackAction->increment(by);
        const auto s = mGoBackAction->state();
        setState(s);
        return;
    }
    return eMoveAction::increment(by);
}

bool ePatrolAction::getGuide(const int tx, const int ty,
                             ePatrolGuide& result) {
    for(const auto& g : mGuides) {
        if(g.fX == tx && g.fY == ty) {
            result = g;
            return true;
        }
    }
    return false;
}

bool ePatrolAction::goBack() {
    if(mGoBackAction) return false;
    const auto c = character();
    const auto t = c->tile();

    const auto tileStart = [this](eTile* const t) {
        return t->x() == mStartX && t->y() == mStartY;
    };
    const auto failAction = []() {};
    const auto finishAction = []() {};

    {
        const auto tileWalkable0 = [](eTile* const t) {
            return t->hasRoad();
        };
        const auto pf0 = ePathFinder(t, tileWalkable0, tileStart);
        std::vector<eOrientation> path0;
        const bool r0 = pf0.findPath(100, path0, false);
        if(r0) {
            mGoBackAction = new eMovePathAction(c, path0, tileWalkable0,
                                                failAction, finishAction);
            return true;
        }
    }

    {
        const auto tileWalkable1 = [](eTile* const) {
            return true;
        };
        const auto pf1 = ePathFinder(t, tileWalkable1, tileStart);
        std::vector<eOrientation> path1;
        const bool r1 = pf1.findPath(100, path1, false);
        if(r1) {
            mGoBackAction = new eMovePathAction(c, path1, tileWalkable1,
                                                failAction, finishAction);
            return true;
        }
    }
    return false;
}

eCharacterActionState ePatrolAction::nextTurn(eOrientation& t) {
    const auto tile = mCharacter->tile();
    if(!tile) return eCharacterActionState::failed;

    const int tx = tile->x();
    const int ty = tile->y();
    if(mWalkedDistance++ > mMaxDistance) {
        const bool r = goBack();
        if(r) return eCharacterActionState::running;
        else return eCharacterActionState::failed;
    }
    ePatrolGuide g;
    const bool r = getGuide(tx, ty, g);
    if(r) mO = directionToOrientation(g.fDir);
    const auto tt = tile->neighbour(mO);
    if(!tt || !tt->hasRoad()) {
        const auto r = tile->randomDiagonalNeighbour([](eTile* const t) {
            return t->hasRoad();
        });
        const auto t = r.second;
        if(!t) {
            const bool r = goBack();
            if(r) return eCharacterActionState::running;
            else return eCharacterActionState::failed;
        }
        mO = r.first;
    }
    t = mO;
    return eCharacterActionState::running;
}
