#include "eprovideresourcehelpaction.h"

#include "etilehelper.h"

eProvideResourceHelpAction::eProvideResourceHelpAction(
        eCharacter* const c,
        const eCharActionType type,
        const eResourceType res,
        const int count) :
    eGodAction(c, type),
    mResource(res),
    mCount(count) {}

bool eProvideResourceHelpAction::decide() {
    switch(mStage) {
    case eProvideResourceHelpStage::none:
        mStage = eProvideResourceHelpStage::appear;
        appear();
        break;
    case eProvideResourceHelpStage::appear:
        mStage = eProvideResourceHelpStage::goTo;
        goToTarget();
        break;
    case eProvideResourceHelpStage::goTo:
        mStage = eProvideResourceHelpStage::give;
        give();
        break;
    case eProvideResourceHelpStage::give: {
        if(mCount > 0) {
            mStage = eProvideResourceHelpStage::goTo;
            goToTarget();
        } else {
            mStage = eProvideResourceHelpStage::disappear;
            disappear();
        }
    } break;
    case eProvideResourceHelpStage::disappear:
        const auto c = character();
        c->kill();
        break;
    }
    return true;
}

void eProvideResourceHelpAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
    src.readBuilding(&board(), [this](eBuilding* const b) {
        mTarget = static_cast<eStorageBuilding*>(b);
    });
    src >> mResource;
    src >> mCount;
}

void eProvideResourceHelpAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
    dst.writeBuilding(mTarget);
    dst << mResource;
    dst << mCount;
}

void eProvideResourceHelpAction::decCount(const int by) {
    mCount -= by;
}

bool eProvideResourceHelpAction::sHelpNeeded(const eGameBoard& board,
                                             const eResourceType res,
                                             const int minSpace) {
    const int r = board.spaceForResource(res);
    return r > minSpace;
}

void eProvideResourceHelpAction::goToTarget() {
    auto& board = this->board();
    using eGTTT = eGoToTargetTeleport;
    const auto tele = std::make_shared<eGTTT>(board, this);
    eStorageBuilding* target = nullptr;
    board.maxSingleSpaceForResource(mResource, &target);
    mTarget = target;
    if(mTarget) {
        const auto ct = mTarget->centerTile();
        const int tx = ct->x();
        const int ty = ct->y();
        const auto tile = eTileHelper::closestRoad(tx, ty, board);
        goToTile(tile, tele);
    } else {
        mStage = eProvideResourceHelpStage::disappear;
        disappear();
    }
}

void eProvideResourceHelpAction::give() {
    if(!mTarget) return;
    const auto c = character();
    const auto targetTile = mTarget->centerTile();
    using eGA_LFRAF = eGA_lookForRangeActionFinish;
    const auto finishAttackA =
            std::make_shared<eGA_LFRAF>(
                board(), this);
    using eGPRA = eGodProvideResourceAct;
    const auto act = std::make_shared<eGPRA>(
                board(), this, mTarget,
                mResource, mCount);
    pauseAction();
    spawnGodMissile(eCharacterActionType::bless,
                    c->type(), targetTile,
                    eGodSound::santcify, act,
                    finishAttackA);
}

