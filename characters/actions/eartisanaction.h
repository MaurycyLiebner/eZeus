#ifndef EARTISANACTION_H
#define EARTISANACTION_H

#include "eactionwithcomeback.h"

#include "characters/eartisan.h"
#include "buildings/eartisansguild.h"
#include "buildings/sanctuaries/esanctbuilding.h"

class eArtisanAction : public eActionWithComeback {
public:
    eArtisanAction(eArtisansGuild* const guild,
                   eArtisan* const c,
                   const eAction& failAction,
                   const eAction& finishAction);
    bool decide();
private:
    bool findTargetDecision();
    void workOnDecision(eTile* const tile);
    void goBackDecision();

    eArtisan* const mArtisan;
    eArtisansGuild* const mGuild;

    bool mNoTarget = false;
};

#endif // EARTISANACTION_H
