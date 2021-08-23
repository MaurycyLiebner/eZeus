#ifndef EANIMALACTION_H
#define EANIMALACTION_H

#include "ecomplexaction.h"

class eAnimalAction : public eComplexAction {
public:
    eAnimalAction(eCharacter* const c,
                  const eAction& failAction,
                  const eAction& finishAction,
                  const int spawnerX,
                  const int spawnerY);

    void nextAction();

private:
    const int mSpawnerX;
    const int mSpawnerY;
};

#endif // EANIMALACTION_H
