#include "efirefightaction.h"

#include "../echaracter.h"
#include "engine/etile.h"
#include "epatrolmoveaction.h"

eFireFightAction::eFireFightAction(eCharacter* const c,
                                   const std::vector<ePatrolGuide>& guides,
                                   const eAction& failAction,
                                   const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mGuides(guides) {

}

void eFireFightAction::increment(const int by) {
    if(!currentAction()) {
        const auto failFunc = [this]() {
            setState(eCharacterActionState::failed);
        };
        const auto finishFunc = [this]() {
            goBack2();
        };
        const auto a = new ePatrolMoveAction(character(), mGuides,
                                           failFunc, finishFunc);
        setCurrentAction(a);
    } else eActionWithComeback::increment(by);
}

bool eFireFightAction::goBack2() {
    return eActionWithComeback::goBack([](eTileBase* const t) {
        return t->hasRoad();
    });
}
