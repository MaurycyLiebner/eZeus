#ifndef EHUNTACTION_H
#define EHUNTACTION_H

#include "eactionwithcomeback.h"

#include "characters/ehunter.h"

class eThreadTile;

class eHuntAction : public eActionWithComeback {
public:
    using eHasResource = std::function<bool(eTileBase*)>;
    using eHasCollectableResource = std::function<bool(eTile*)>;
    eHuntAction(const SDL_Rect& buildingRect,
                eHunter* const c,
                const eHasResource& hr,
                const eHasCollectableResource& hcr,
                const eAction& failAction,
                const eAction& finishAction);

    void increment(const int by);

    void resume();
private:
    bool findResource();
    bool collect();
    void goBack2();

    const eHasResource mHasResource;
    const eHasCollectableResource mHasCollectableResource;
    eHunter* const mCharacter;
    const SDL_Rect mBuildingRect;
};

#endif // EHUNTACTION_H
