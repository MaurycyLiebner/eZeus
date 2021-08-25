#include "eanimalaction.h"

#include "characters/echaracter.h"
#include "emovearoundaction.h"
#include "ewaitaction.h"

eAnimalAction::eAnimalAction(eCharacter* const c,
                             const eAction& failAction,
                             const eAction& finishAction,
                             const int spawnerX,
                             const int spawnerY) :
    eComplexAction(c, failAction, finishAction),
    mSpawnerX(spawnerX), mSpawnerY(spawnerY) {
    nextAction();
}

void eAnimalAction::nextAction() {
    const auto c = character();
    const auto finishAct = [this]() {
        nextAction();
    };
    if(rand() % 2 == 0) {
        c->setActionType(eCharacterActionType::walk);
        const auto m = e::make_shared<eMoveAroundAction>(
                           c, finishAct, finishAct,
                           mSpawnerX, mSpawnerY);
        m->setTime(3000);
        setCurrentAction(m);
    } else {
        c->setActionType(eCharacterActionType::lay);
        const auto w = e::make_shared<eWaitAction>(
                           c, finishAct, finishAct);
        w->setTime(2000);
        setCurrentAction(w);
    }
}
