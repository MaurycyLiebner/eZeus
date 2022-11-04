#include "edieaction.h"

#include "characters/echaracter.h"

eDieAction::eDieAction(eCharacter* const c,
                       const eAction& finishAction) :
    eCharacterAction(c, finishAction, finishAction) {
    const auto aType = c->actionType();
    if(aType != eCharacterActionType::none) {
        c->setActionType(eCharacterActionType::die);
    }
}

void eDieAction::increment(const int by) {
    mTime += by;
    if(mTime > 1024) setState(eCharacterActionState::finished);
}
