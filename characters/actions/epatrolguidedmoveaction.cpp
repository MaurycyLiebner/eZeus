#include "epatrolguidedmoveaction.h"

#include "emovetoaction.h"
#include "../echaracter.h"

ePatrolGuidedMoveAction::ePatrolGuidedMoveAction(
        eCharacter* const c,
        const SDL_Rect& buildingRect,
        const std::vector<ePatrolGuide>& guides,
        const eAction& failAction,
        const eAction& finishAction) :
    eComplexAction(c, failAction, finishAction),
    mGuides(guides), mBuildingRect(buildingRect) {

}

void ePatrolGuidedMoveAction::increment(const int by) {
    if(!currentAction()) nextGuide();
    eComplexAction::increment(by);
}

void ePatrolGuidedMoveAction::nextGuide() {
    const int maxG = mGuides.size();
    if(mNextGuide >= maxG) {
        return setState(eCharacterActionState::finished);
    }
    const auto& g = mGuides.at(mNextGuide++);

    const auto c = character();

    const auto finalTile = [g](eThreadTile* const t) {
        return t->x() == g.fX && t->y() == g.fY;
    };
    const stdptr<ePatrolGuidedMoveAction> tptr(this);
    const auto failFunc = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::failed);
    };

    const auto finishAction = [tptr]() {
        if(tptr) tptr->nextGuide();
    };

    const auto a  = e::make_shared<eMoveToAction>(
                        c, failFunc, finishAction);
    a->start(finalTile, eMoveToAction::sRoadWalkable);
    tptr->setCurrentAction(a);
}
