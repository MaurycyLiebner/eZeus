#include "ehephaestushelpaction.h"

#include "etilehelper.h"
#include "buildings/epalace.h"
#include "gameEvents/einvasionevent.h"
#include "characters/monsters/ecalydonianboar.h"
#include "characters/actions/edefendcityaction.h"

eHephaestusHelpAction::eHephaestusHelpAction(eCharacter* const c) :
    eGodAction(c, eCharActionType::hephaestusHelpAction) {}

bool eHephaestusHelpAction::decide() {
    switch(mStage) {
    case eHephaestusHelpStage::none:
        mStage = eHephaestusHelpStage::appear;
        appear();
        break;
    case eHephaestusHelpStage::appear:
        mStage = eHephaestusHelpStage::provide;
        provide();
        break;
    case eHephaestusHelpStage::provide:
        mStage = eHephaestusHelpStage::disappear;
        disappear();
        break;
    case eHephaestusHelpStage::disappear:
        const auto c = character();
        c->kill();
        break;
    }
    return true;
}

void eHephaestusHelpAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
}

void eHephaestusHelpAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
}

bool eHephaestusHelpAction::sHelpNeeded(const eGameBoard& board) {
    return board.invasionToDefend();
}

void eHephaestusHelpAction::provide() {
    auto& board = eHephaestusHelpAction::board();
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

    const auto talos = e::make_shared<eTalos>(board);
    const auto tile = c->tile();
    talos->changeTile(tile);
    const auto da = e::make_shared<eDefendCityAction>(talos.get());
    talos->setAction(da);
}
