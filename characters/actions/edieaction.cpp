#include "edieaction.h"

#include "characters/ebasicpatroler.h"
#include "characters/efightingpatroler.h"
#include "characters/eresourcecollector.h"
#include "characters/eanimal.h"

eDieAction::eDieAction(eCharacter* const c,
                       const eAction& finishAction) :
    eCharacterAction(c, finishAction, finishAction) {
    c->setActionType(eCharacterActionType::die);
}

void eDieAction::increment(const int by) {
    mTime += by;
    if(mTime > 512) setState(eCharacterActionState::finished);
}
