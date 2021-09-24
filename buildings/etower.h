#ifndef ETOWER_H
#define ETOWER_H

#include "eemployingbuilding.h"

#include "characters/earcher.h"

class eTower : public eEmployingBuilding {
public:
    eTower(eGameBoard& board);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const;
    std::vector<eOverlay>
    getOverlays(const eTileSize size) const;

    void timeChanged(const int by);

    bool spawn();
private:
    bool mSpawnPatrolers = true;

    int mWaitTime = 5000;
    int mSpawnTime = 0;

    stdsptr<eArcher> mArcher;
};

#endif // ETOWER_H
