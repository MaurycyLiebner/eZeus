#include "epatrolmoveaction.h"

#include "../echaracter.h"
#include "engine/etile.h"
#include "emovepathaction.h"
#include "engine/epathfinder.h"

ePatrolMoveAction::ePatrolMoveAction(eCharacter* const c,
                                     const std::vector<ePatrolGuide>& guides,
                                     const eAction& failAction,
                                     const eAction& finishAction) :
    eMoveAction(c,
                [](eTileBase* const tile) {
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

bool ePatrolMoveAction::getGuide(const int tx, const int ty,
                                 ePatrolGuide& result) {
    for(const auto& g : mGuides) {
        if(g.fX == tx && g.fY == ty) {
            result = g;
            return true;
        }
    }
    return false;
}

eCharacterActionState ePatrolMoveAction::nextTurn(eOrientation& t) {
    if(mWalkedDistance++ > mMaxDistance) {
        setState(eCharacterActionState::finished);
        return eCharacterActionState::finished;
    }
    const auto c = character();
    const auto tile = c->tile();
    if(!tile) return eCharacterActionState::failed;

    const int tx = tile->x();
    const int ty = tile->y();

    auto options = tile->diagonalNeighbours([&](eTileBase* const t) {
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
        return eCharacterActionState::failed;
    }
    return eCharacterActionState::running;
}
