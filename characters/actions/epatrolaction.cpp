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
    const auto t = c->tile();
    if(t) {
        mStartX = t->x();
        mStartY = t->y();
    }
    mO = c->orientation();
}

void ePatrolAction::increment(const int by) {
    if(mGoBack) {
        goBack();
        if(!mGoBackAction) {
            setState(eCharacterActionState::failed);
            return;
        }
        mGoBackAction->increment(by);
        const auto s = mGoBackAction->state();
        setState(s);
    } else {
        return eMoveAction::increment(by);
    }
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
    const auto failAction = [this]() { setState(eCharacterActionState::failed); };
    const auto finishAction = [this]() { setState(eCharacterActionState::finished); };

    const auto tileWalkable0 = [](eTile* const t) {
        return t->hasRoad();
    };
    const auto pf0 = ePathFinder(t, tileWalkable0, tileStart);
    std::vector<eOrientation> path0;
    const bool r0 = pf0.findPath(100, path0, false, true);
    if(r0) {
        mGoBackAction = new eMovePathAction(c, path0, tileWalkable0,
                                            failAction, finishAction);
        return true;
    }
    return false;
}

eCharacterActionState ePatrolAction::nextTurn(eOrientation& t) {
    mGoBack = mWalkedDistance++ > mMaxDistance;
    const auto tile = mCharacter->tile();
    if(!tile) {
        return eCharacterActionState::failed;
    }

    const int tx = tile->x();
    const int ty = tile->y();

    ePatrolGuide g;
    const bool r = getGuide(tx, ty, g);
    if(r) {
        auto dirs = gExtractDirections(g.fDir);
        if(!dirs.empty()) {
            eTile* tt = nullptr;
            std::random_shuffle(dirs.begin(), dirs.end());
            for(const auto dir : dirs) {
                mO = directionToOrientation(dir);
                tt = tile->neighbour(mO);
                if(tt && tt->hasRoad()) break;
            }
        }
    }
    const auto tt = tile->neighbour(mO);
    if(!tt || !tt->hasRoad()) {
        const auto r = tile->randomDiagonalNeighbour([&](eTile* const t) {
            return t->hasRoad() && t->neighbour(mO) != tile;
        });
        if(r.second) {
            mO = r.first;
        } else {
            const auto o = !mO;
            const auto t = tile->neighbour(o);
            if(t && t->hasRoad()) {
                mO = o;
            } else {
                const bool r = goBack();
                if(r) {
                    return eCharacterActionState::running;
                } else {
                    return eCharacterActionState::failed;
                }
            }
        }
    }
    t = mO;
    return eCharacterActionState::running;
}
