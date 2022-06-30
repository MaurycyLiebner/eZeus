#ifndef EANIMALACTION_H
#define EANIMALACTION_H

#include "ecomplexaction.h"

#include "emovearoundaction.h"

class eTileBase;

class eAnimalAction : public eComplexAction {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    eAnimalAction(eCharacter* const c,
                  const eAction& failAction,
                  const eAction& finishAction,
                  const int spawnerX, const int spawnerY,
                  const eTileWalkable& tileWalkable =
                        eMoveAroundAction::sDefaultWalkable);

    void nextAction();

    void setLayTime(const int l) { mLayTime = l; }
    void setWalkTime(const int w) { mWalkTime = w; }
private:
    const int mSpawnerX;
    const int mSpawnerY;

    const eTileWalkable mTileWalkable;

    int mLayTime = 2000;
    int mWalkTime = 3000;
};

#endif // EANIMALACTION_H
