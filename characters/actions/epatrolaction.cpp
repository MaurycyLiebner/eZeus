#include "epatrolaction.h"

#include "../echaracter.h"
#include "engine/etile.h"
#include "epatrolmoveaction.h"

ePatrolAction::ePatrolAction(eCharacter* const c,
                             const SDL_Rect& buildingRect,
                             const std::vector<ePatrolGuide>& guides,
                             const eAction& failAction,
                             const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mGuides(guides), mBuildingRect(buildingRect) {

}

void ePatrolAction::increment(const int by) {
    if(!currentAction()) patrol();
    eActionWithComeback::increment(by);
}

void ePatrolAction::patrol() {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto failFunc = [this]() {
        setState(eCharacterActionState::failed);
    };
    const auto finishFunc = [this]() {
        goBack2();
    };
    if(mGuides.empty()) {
        const auto a = e::make_shared<ePatrolMoveAction>(
                           c, mBuildingRect,
                           failFunc, finishFunc);
        setCurrentAction(a);
    } else {
        const auto a = e::make_shared<ePatrolGuidedMoveAction>(
                           c, mBuildingRect, mGuides,
                           failFunc, finishFunc);
        setCurrentAction(a);
    }
}

void ePatrolAction::goBack2() {
    const auto rect = mBuildingRect;
    eActionWithComeback::goBack([rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->hasRoad();
    });
}

void ePatrolAction::goBackNoRoad() {
    const auto rect = mBuildingRect;
    eActionWithComeback::goBack([rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable();
    });
}
