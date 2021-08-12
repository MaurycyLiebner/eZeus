#include "efightaction.h"

#include "characters/echaracter.h"

#include "characters/ebasicpatroler.h"
#include "characters/efightingpatroler.h"
#include "characters/eresourcecollector.h"
#include "characters/eanimal.h"

eFightAction::eFightAction(eCharacter* const c,
                           eCharacter* const o,
                           const eAction& finishAction) :
    eCharacterAction(c, finishAction, finishAction),
    mOpponent(o) {
    c->setActionType(eCharacterActionType::fight);
}

void eFightAction::increment(const int by) {
    const auto c = character();
    const int a = c->attack();
    const bool dead = mOpponent->defend(by*a);
    if(dead || c->dead()) {
        setState(eCharacterActionState::finished);
    }
}
