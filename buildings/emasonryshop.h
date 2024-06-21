#ifndef EMASONRYSHOP_H
#define EMASONRYSHOP_H

#include "eresourcecollectbuilding.h"

class eMasonryShop : public eResourceCollectBuilding {
public:
    eMasonryShop(eGameBoard& board);

    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged(const int by);
private:
    void setCollectAction();

    bool mCollectActionSet = false;
};

#endif // EMASONRYSHOP_H
