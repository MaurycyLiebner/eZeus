#ifndef ESHEPHERDACTION_H
#define ESHEPHERDACTION_H

#include "eactionwithcomeback.h"

#include "characters/eshepherd.h"
#include "buildings/eshepherbuildingbase.h"

class eDomesticatedAnimal;

class eShepherdAction : public eActionWithComeback {
public:
    eShepherdAction(eShepherBuildingBase* const shed,
                    eResourceCollectorBase* const c,
                    const eCharacterType animalType,
                    const eAction& failAction,
                    const eAction& finishAction);

    bool decide();
private:
    bool findResourceDecision();
    void collectDecision(eDomesticatedAnimal* const a);
    void groomDecision(eDomesticatedAnimal* const a);
    void goBackDecision();
    void waitDecision();

    eCharacterType mAnimalType;

    eResourceCollectorBase* const mCharacter;
    eShepherBuildingBase* const mShed;

    int mGroomed = 0;
    bool mNoResource = false;
};

#endif // ESHEPHERDACTION_H
