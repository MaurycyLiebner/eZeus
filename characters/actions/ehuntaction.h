#ifndef EHUNTACTION_H
#define EHUNTACTION_H

#include "eactionwithcomeback.h"

#include "characters/ehunter.h"

class eHuntAction : public eActionWithComeback {
public:
    eHuntAction(const SDL_Rect& buildingRect,
                eHunter* const c,
                const eAction& failAction,
                const eAction& finishAction);

    void increment(const int by);

    void resume();
private:
    bool findResource();
    bool collect();
    void goBack2();

    eHunter* const mCharacter;
    const SDL_Rect mBuildingRect;
};

#endif // EHUNTACTION_H
