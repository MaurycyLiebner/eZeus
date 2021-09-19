#ifndef EGROWERACTION_H
#define EGROWERACTION_H

#include "eactionwithcomeback.h"

#include "characters/egrower.h"

class eGrowerAction : public eActionWithComeback {
public:
    eGrowerAction(const eGrowerType type,
                  const SDL_Rect& buildingRect,
                  eGrower* const c,
                  const eAction& failAction,
                  const eAction& finishAction);

    void increment(const int by);
private:
    bool findResource();
    bool workOn(eTile* const tile);
    void goBack2();

    const eGrowerType mType;
    eGrower* const mGrower;
    const SDL_Rect mBuildingRect;
    int mCount = 0;
};

#endif // EGROWERACTION_H
