#include "epatrolguidedmoveaction.h"

#include "emovetoaction.h"
#include "../echaracter.h"
#include "buildings/epatrolbuildingbase.h"

ePatrolGuidedMoveAction::ePatrolGuidedMoveAction(
        eCharacter* const c,
        ePatrolBuildingBase* const b,
        const std::vector<ePatrolGuide>& guides,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mGuides(guides), mBuilding(b) {

}

bool ePatrolGuidedMoveAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return true;
    if(mGuideFail) {
        mGuideFail = false;
        goBack(mBuilding, eWalkableHelpers::sDefaultWalkable);
    } else {
        nextGuide();
    }
    return true;
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
    const auto failFunc = [tptr, this]() {
        if(!tptr) return;
        mGuideFail = true;
    };

    const auto a  = e::make_shared<eMoveToAction>(
                        c, failFunc, [](){});
    a->start(finalTile, eWalkableHelpers::sRoadWalkable);
    setCurrentAction(a);
}
