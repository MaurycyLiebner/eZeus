#include "ezeushelpaction.h"

#include "../ewaitaction.h"
#include "einvasionhandler.h"

eZeusHelpAction::eZeusHelpAction(
        eCharacter* const c) :
    eGodAction(c, eCharActionType::zeusHelpAction) {}

bool eZeusHelpAction::decide() {
    switch(mStage) {
    case eZeusHelpStage::none:
        mStage = eZeusHelpStage::appear;
        appear();
        break;
    case eZeusHelpStage::appear:
        mStage = eZeusHelpStage::kill;
        kill();
        break;
    case eZeusHelpStage::kill:
        mStage = eZeusHelpStage::disappear;
        disappear();
        break;
    case eZeusHelpStage::disappear:
        const auto c = character();
        c->kill();
        break;
    }
    return true;
}

void eZeusHelpAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
}

void eZeusHelpAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
}

bool eZeusHelpAction::sHelpNeeded(const eGameBoard& board) {
    const auto& ivs = board.invasions();
    return !ivs.empty();
}

void eZeusHelpAction::kill() {
    const auto c = character();
    c->setActionType(eCharacterActionType::fight);
    const auto a = e::make_shared<eWaitAction>(c);
    using eF = eZHA_killFinish;
    const auto finish = std::make_shared<eF>(board());
    a->setFailAction(finish);
    a->setFinishAction(finish);
    a->setTime(500);
    setCurrentAction(a);
}

void eZHA_killFinish::call() {
    const auto& b = board();
    const auto& ivs = b.invasions();
    for(const auto iv : ivs) {
        iv->killAllWithCorpse();
    }
}
