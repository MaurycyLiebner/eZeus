#include "epatrolaction.h"

#include "../echaracter.h"
#include "engine/etile.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"

ePatrolAction::ePatrolAction(eCharacter* const c,
                             const std::vector<ePatrolGuide>& guides,
                             const eAction& failAction,
                             const eAction& finishAction) :
    eMoveAction(c,
                [](eTile* const tile) {
                    return tile->hasRoad();
                },
                failAction, finishAction),
    mGuides(guides) {
    const auto t = c->tile();
    if(t) {
        mStartX = t->x();
        mStartY = t->y();
    }
    mO = c->orientation();
}

ePatrolAction::~ePatrolAction() {
    if(mGoBackAction) delete mGoBackAction;
}

void ePatrolAction::increment(const int by) {
    const bool gb = mWalkedDistance++ > mMaxDistance;
    if(gb) {
        if(!mGoBackAction) {
            if(!goBack()) {
                setState(eCharacterActionState::failed);
                return;
            }
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

    const auto finalTile = [this](eTile* const t) {
        return t->x() == mStartX && t->y() == mStartY;
    };
    const auto failAction = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishAction = [this]() {
        setState(eCharacterActionState::finished);
    };

    const auto tileWalkable0 = [](eTile* const t) {
        return t->hasRoad();
    };
    const auto pf0 = ePathFinder(t, tileWalkable0, finalTile);
    std::vector<eOrientation> path0;
    const bool r0 = pf0.findPath(100, path0, false, true);
    if(r0) {
        mGoBackAction = new eMovePathAction(c, path0, tileWalkable0,
                                            failAction, finishAction);
        return true;
    }
    setState(eCharacterActionState::failed);
    return false;
}

eCharacterActionState ePatrolAction::nextTurn(eOrientation& t) {
    const auto tile = mCharacter->tile();
    if(!tile) {
        return eCharacterActionState::failed;
    }

    const int tx = tile->x();
    const int ty = tile->y();

    auto options = tile->diagonalNeighbours([&](eTile* const t) {
        return t && t->hasRoad() && t->neighbour(mO) != tile;
    });

    ePatrolGuide g;
    const bool r = getGuide(tx, ty, g);
    if(r) {
        for(auto it = options.begin(); it != options.end(); it++) {
            const auto o = (*it).first;
            const auto odir = gOrientationToDirection(o);
            if(!static_cast<bool>(odir & g.fDir)) {
                const auto itt = it;
                it--;
                options.erase(itt);
            }
        }
    }
    if(options.empty()) {
        mO = !mO;
    } else {
        std::random_shuffle(options.begin(), options.end());
        mO = options.front().first;
    }
    t = mO;
    const auto tt = tile->neighbour(mO);
    if(!tt || !tt->hasRoad()) {
        const bool r = goBack();
        if(r) {
            return eCharacterActionState::running;
        } else {
            return eCharacterActionState::failed;
        }
    }
    return eCharacterActionState::running;
}
