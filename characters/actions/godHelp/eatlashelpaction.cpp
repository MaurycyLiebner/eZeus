#include "eatlashelpaction.h"

eAtlasHelpAction::eAtlasHelpAction(
        eCharacter* const c) :
    eGodAction(c, eCharActionType::atlasHelpAction) {}

bool eAtlasHelpAction::decide() {
    switch(mStage) {
    case eAtlasHelpStage::none:
        mStage = eAtlasHelpStage::appear;
        appear();
        break;
    case eAtlasHelpStage::appear:
        mStage = eAtlasHelpStage::goTo;
        goToTarget();
        break;
    case eAtlasHelpStage::goTo:
        mStage = eAtlasHelpStage::give;
        give();
        break;
    case eAtlasHelpStage::give:
        mStage = eAtlasHelpStage::disappear;
        disappear();
        break;
    case eAtlasHelpStage::disappear:
        const auto c = character();
        c->kill();
        break;
    }
    return true;
}

void eAtlasHelpAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
    src.readBuilding(&board(), [this](eBuilding* const b) {
        mTarget = static_cast<eSanctuary*>(b);
    });
}

void eAtlasHelpAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
    dst.writeBuilding(mTarget);
}

bool eAtlasHelpAction::sHelpNeeded(const eGameBoard& board) {
    eSanctuary* b = nullptr;
    const int r = board.maxSanctuarySpaceForResource(&b);
    return r > 0;
}

void eAtlasHelpAction::goToTarget() {
    auto& board = this->board();
    using eGTTT = eGoToTargetTeleport;
    const auto tele = std::make_shared<eGTTT>(board, this);
    eSanctuary* target = nullptr;
    board.maxSanctuarySpaceForResource(&target);
    mTarget = target;
    if(mTarget) {
        const auto ct = mTarget->centerTile();
        const int tx = ct->x();
        const int ty = ct->y();
        const auto tile = eTileHelper::closestRoad(tx, ty, board);
        goToTile(tile, tele);
    } else {
        disappear();
    }
}

void eAtlasHelpAction::give() {
    if(!mTarget) return;
    const auto c = character();
    const auto targetTile = mTarget->centerTile();
    using eGA_LFRAF = eGA_lookForRangeActionFinish;
    const auto finishAttackA =
            std::make_shared<eGA_LFRAF>(
                board(), this);
    const auto act = std::make_shared<eAtlasHelpAct>(
                board(), mTarget);
    pauseAction();
    spawnGodMissile(eCharacterActionType::bless,
                    c->type(), targetTile,
                    eGodSound::santcify, act,
                    finishAttackA);
}
