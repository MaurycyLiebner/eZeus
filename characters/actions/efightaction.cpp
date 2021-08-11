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
    if(const auto bp = dynamic_cast<eBasicPatroler*>(c)) {
        bp->setAnimationAction(eBasicPatrolerAction::walk);
    } else if(const auto fp = dynamic_cast<eFightingPatroler*>(c)) {
        fp->setAnimationAction(eFightingPatrolerAction::fight);
    } else if(const auto rc = dynamic_cast<eResourceCollector*>(c)) {
        rc->setAnimationAction(eResourceCollectorAction::walk);
    } else if(const auto rc = dynamic_cast<eAnimal*>(c)) {
        rc->setAnimationAction(eAnimalAction::fight);
    }
}

void eFightAction::increment(const int by) {
    const auto c = character();
    const int a = c->attack();
    const bool dead = mOpponent->defend(by*a);
    if(dead || character()->dead()) {
        setState(eCharacterActionState::finished);
    }
}
