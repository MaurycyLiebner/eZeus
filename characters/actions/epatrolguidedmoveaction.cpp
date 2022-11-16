#include "epatrolguidedmoveaction.h"

#include "emovetoaction.h"
#include "../echaracter.h"
#include "buildings/epatrolbuildingbase.h"
#include "earcheraction.h"

ePatrolGuidedMoveAction::ePatrolGuidedMoveAction(eCharacter* const c,
        ePatrolBuildingBase* const b,
        const std::vector<ePatrolGuide>& guides) :
    eComplexAction(c, eCharActionType::patrolGuidedMoveAction),
    mGuides(guides), mBuilding(b) {}

ePatrolGuidedMoveAction::ePatrolGuidedMoveAction(eCharacter* const c) :
    ePatrolGuidedMoveAction(c, nullptr, {}) {}

bool ePatrolGuidedMoveAction::decide() {
    nextGuide();
    return true;
}

void ePatrolGuidedMoveAction::read(eReadStream& src) {
    eComplexAction::read(src);
    int n;
    src >> n;
    for(int i = 0; i < n; i++) {
        auto& g = mGuides.emplace_back();
        src >> g.fX;
        src >> g.fY;
    }
    src.readBuilding(&board(), [this](eBuilding* const b) {
        mBuilding = static_cast<ePatrolBuildingBase*>(b);
    });
    src >> mNextGuide;
    src >> mMaxWalkDistance;
    src >> mWalkedDistance;
}

void ePatrolGuidedMoveAction::write(eWriteStream& dst) const {
    eComplexAction::write(dst);
    dst << mGuides.size();
    for(const auto& g : mGuides) {
        dst << g.fX;
        dst << g.fY;
    }
    dst.writeBuilding(mBuilding);
    dst << mNextGuide;
    dst << mMaxWalkDistance;
    dst << mWalkedDistance;
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
    const auto failFunc = std::make_shared<eAA_patrolFinish>(
                              board(), this);

    const auto a  = e::make_shared<eMoveToAction>(c);
    a->setFailAction(failFunc);
    a->setFoundAction([tptr, this, a]() {
        if(!tptr) return;
        const int pl = a->pathLength();
        a->setMaxWalkDistance(mMaxWalkDistance - mWalkedDistance);
        mWalkedDistance += pl;
    });
    a->start(finalTile, eWalkableObject::sCreateRoad());
    setCurrentAction(a);
}
