#ifndef ESETTLERACTION_H
#define ESETTLERACTION_H

#include "eactionwithcomeback.h"

class eSettlerAction : public eActionWithComeback {
public:
    eSettlerAction(eCharacter* const c,
                   const eAction& failAction,
                   const eAction& finishAction);

    void increment(const int by);
protected:
    void findHouse();
    void goBack2();
    bool enterHouse();
};

#endif // ESETTLERACTION_H
