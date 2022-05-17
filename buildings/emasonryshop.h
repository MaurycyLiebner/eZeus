#ifndef EMASONRYSHOP_H
#define EMASONRYSHOP_H

#include "eresourcecollectbuilding.h"

class eMasonryShop : public eResourceCollectBuilding {
public:
    eMasonryShop(eGameBoard& board);

    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged(const int by);

    int add(const eResourceType type, const int count);
private:
    int mRawCount{0};

    int mProcessWaitTime = 10000;
    int mProcessTime = mProcessWaitTime;
};

#endif // EMASONRYSHOP_H
