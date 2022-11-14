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
    eComplexAction(c, failAction, finishAction),
    mGuides(guides), mBuilding(b) {

}

bool ePatrolGuidedMoveAction::decide() {
    const bool r = eComplexAction::decide();
    if(r) return true;
    nextGuide();
    return true;
}

void ePatrolGuidedMoveAction::nextGuide() {
    const int maxG = mGuides.size();
    if(mNextGuide >= maxG || mWalkedDistance > mMaxWalkDistance) {
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
        setState(eCharacterActionState::finished);
    };

    const auto a  = e::make_shared<eMoveToAction>(
                        c, failFunc, [](){});
    a->setFoundAction([tptr, this, a]() {
        if(!tptr) return;
        const int pl = a->pathLength();
        a->setMaxWalkDistance(mMaxWalkDistance - mWalkedDistance);
        mWalkedDistance += pl;
    });
    a->start(finalTile, eWalkableObject::sCreateRoad());
    setCurrentAction(a);
}
