#include "edieaction.h"

#include "characters/ebasicpatroler.h"
#include "characters/efightingpatroler.h"
#include "characters/eresourcecollector.h"
#include "characters/eanimal.h"

eDieAction::eDieAction(eCharacter* const c,
                       const eAction& finishAction) :
    eCharacterAction(c, finishAction, finishAction) {
    if(const auto bp = dynamic_cast<eBasicPatroler*>(c)) {
        bp->setAnimationAction(eBasicPatrolerAction::die);
    } else if(const auto fp = dynamic_cast<eFightingPatroler*>(c)) {
        fp->setAnimationAction(eFightingPatrolerAction::die);
    } else if(const auto rc = dynamic_cast<eResourceCollector*>(c)) {
        rc->setAnimationAction(eResourceCollectorAction::die);
    } else if(const auto rc = dynamic_cast<eAnimal*>(c)) {
        rc->setAnimationAction(eAnimalAction::die);
    }
}

void eDieAction::increment(const int by) {
    mTime += by;
    if(mTime > 256) setState(eCharacterActionState::finished);
}
