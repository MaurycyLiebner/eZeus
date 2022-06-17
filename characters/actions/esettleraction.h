#ifndef ESETTLERACTION_H
#define ESETTLERACTION_H

#include "eactionwithcomeback.h"

class eSettlerAction : public eActionWithComeback {
public:
    eSettlerAction(eCharacter* const c,
                   const eAction& failAction,
                   const eAction& finishAction);

    bool decide();
protected:
    void findHouse();
    void goBack2();
    bool enterHouse();
private:
    bool mNoHouses = false;
};

#endif // ESETTLERACTION_H
