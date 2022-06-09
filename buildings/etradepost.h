#ifndef ETRADEPOST_H
#define ETRADEPOST_H

#include "ewarehousebase.h"

#include "engine/eworldcity.h"

class eTradePost : public eWarehouseBase {
public:
    eTradePost(eGameBoard& board, eWorldCity& city);
    ~eTradePost();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged(const int by);

    void setOrders(const eResourceType imports,
                   const eResourceType exports);

    void getOrders(eResourceType& imports,
                   eResourceType& exports) const;

    eWorldCity& city() { return mCity; }

    eTile* routeStart() const { return mRouteStart; }
    void updateRouteStart();

    void spawnTrader();
private:
    eWorldCity& mCity;
    eResourceType mImports = eResourceType::none;
    eResourceType mExports = eResourceType::none;

    eTile* mRouteStart = nullptr;

    int mRouteTimer = 0;
};

#endif // ETRADEPOST_H
