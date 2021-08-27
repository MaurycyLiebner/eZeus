#ifndef ESHEPHERDACTION_H
#define ESHEPHERDACTION_H

#include "eactionwithcomeback.h"

#include "characters/eshepherd.h"

class eDomesticatedAnimal;

class eShepherdAction : public eActionWithComeback {
public:
    eShepherdAction(const SDL_Rect& buildingRect,
                    eResourceCollector* const c,
                    const eCharacterType animalType,
                    const eAction& failAction,
                    const eAction& finishAction);

    void increment(const int by);
private:
    bool findResource();
    bool collect(eDomesticatedAnimal* const a);
    void goBack2();

    eCharacterType mAnimalType;

    eResourceCollector* const mCharacter;
    const SDL_Rect mBuildingRect;
};

#endif // ESHEPHERDACTION_H
