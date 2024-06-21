#include "ehermeshelpaction.h"

#include "etilehelper.h"
#include "buildings/epalace.h"
#include "gameEvents/ereceiverequestevent.h"

eHermesHelpAction::eHermesHelpAction(eCharacter* const c) :
    eGodAction(c, eCharActionType::hermesHelpAction) {}

bool eHermesHelpAction::decide() {
    switch(mStage) {
    case eHermesHelpStage::none:
        mStage = eHermesHelpStage::appear;
        appear();
        break;
    case eHermesHelpStage::appear:
        mStage = eHermesHelpStage::provide;
        provide();
        break;
    case eHermesHelpStage::provide:
        mStage = eHermesHelpStage::disappear;
        disappear();
        break;
    case eHermesHelpStage::disappear:
        const auto c = character();
        c->kill();
        break;
    }
    return true;
}

void eHermesHelpAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
}

void eHermesHelpAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
}

bool eHermesHelpAction::sHelpNeeded(const eGameBoard& board) {
    const auto& crs = board.cityRequests();
    return !crs.empty();
}

void eHermesHelpAction::provide() {
    auto& board = eHermesHelpAction::board();
    const auto c = character();
    const auto p = board.palace();
    const int bw = board.width();
    const int bh = board.height();
    const auto centerTile = board.dtile(bw/2, bh/2);
    const auto targetTile = p ? p->centerTile() : centerTile;
    using eGA_LFRAF = eGA_lookForRangeActionFinish;
    const auto finishAttackA = std::make_shared<eGA_LFRAF>(
                                   board, this);
    pauseAction();
    spawnGodMissile(eCharacterActionType::bless,
                    c->type(), targetTile,
                    eGodSound::santcify, nullptr,
                    finishAttackA);
    const auto& crs = board.cityRequests();
    if(crs.empty()) return;
    crs[0]->fulfillWithoutCost();
}
