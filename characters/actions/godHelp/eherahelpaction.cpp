#include "eherahelpaction.h"

eHeraHelpAction::eHeraHelpAction(eCharacter* const c) :
    eGodAction(c, eCharActionType::heraHelpAction) {}

bool eHeraHelpAction::decide() {
    switch(mStage) {
    case eHeraHelpStage::none:
        mStage = eHeraHelpStage::appear;
        appear();
        break;
    case eHeraHelpStage::appear: {
        auto& board = this->board();
        const auto as = board.agoras();
        for(const auto a : as) {
            mFutureTargets.push_back(a);
        }
        goToTarget();
    } break;
    case eHeraHelpStage::goTo:
        mStage = eHeraHelpStage::give;
        give();
        break;
    case eHeraHelpStage::give:
        goToTarget();
        break;
    case eHeraHelpStage::disappear:
        const auto c = character();
        c->kill();
        break;
    }
    return true;
}

void eHeraHelpAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
    src.readBuilding(&board(), [this](eBuilding* const b) {
        mTarget = static_cast<eAgoraBase*>(b);
    });
    int nt;
    src >> nt;
    for(int i = 0; i < nt; i++) {
        src.readBuilding(&board(), [this](eBuilding* const b) {
            const auto a = static_cast<eAgoraBase*>(b);
            mFutureTargets.push_back(a);
        });
    }
}

void eHeraHelpAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
    dst.writeBuilding(mTarget);
    dst << mFutureTargets.size();
    for(const auto& a : mFutureTargets) {
        dst.writeBuilding(a.get());
    }
}

bool eHeraHelpAction::sHelpNeeded(const eGameBoard& board) {
    const auto as = board.agoras();
    for(const auto a : as) {
        int space = 0;
        space += a->spaceLeft(eResourceType::food);
        space += a->spaceLeft(eResourceType::fleece);
        space += a->spaceLeft(eResourceType::oliveOil);
        space += a->spaceLeft(eResourceType::wine);
        if(space > 4) return true;
    }
    return false;
}

void eHeraHelpAction::goToTarget() {
    while(!mTarget && !mFutureTargets.empty()) {
        mTarget = mFutureTargets.back();
        mFutureTargets.pop_back();
    }
    if(mTarget) {
        mStage = eHeraHelpStage::goTo;
        auto& board = this->board();
        using eGTTT = eGoToTargetTeleport;
        const auto tele = std::make_shared<eGTTT>(board, this);
        const auto ct = mTarget->centerTile();
        goToTile(ct, tele);
    } else {
        mStage = eHeraHelpStage::disappear;
        disappear();
    }
}

void eHeraHelpAction::give() {
    if(!mTarget) return;
    const auto c = character();
    const auto targetTile = mTarget->centerTile();
    using eGA_LFRAF = eGA_lookForRangeActionFinish;
    const auto finishAttackA =
            std::make_shared<eGA_LFRAF>(
                board(), this);
    using eGPAA = eGodProvideAgoraAct;
    const auto act = std::make_shared<eGPAA>(
                board(), mTarget);
    pauseAction();
    spawnGodMissile(eCharacterActionType::bless,
                    c->type(), targetTile,
                    eGodSound::santcify, act,
                    finishAttackA);
    mTarget = nullptr;
}
