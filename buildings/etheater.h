#ifndef ETHEATER_H
#define ETHEATER_H

#include "epatrolbuilding.h"

class eTheater : public ePatrolBuilding {
public:
    eTheater(eGameBoard& board);

    void timeChanged(const int by);
private:
    void spawnGetActor();

    int mWaitTime = 5000;
    int mSpawnTime = 0;
    stdsptr<eCharacter> mChar;
};

#endif // ETHEATER_H
