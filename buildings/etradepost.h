#ifndef ETRADEPOST_H
#define ETRADEPOST_H

#include "ewarehousebase.h"

#include "engine/eworldcity.h"
#include "ewalkablehelpers.h"

enum class eTradePostType {
    post, pier
};

class eTradePost : public eWarehouseBase {
public:
    eTradePost(eGameBoard& board, eWorldCity& city,
               const eTradePostType type = eTradePostType::post);
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

    int buy(const int cash);
    int sell(const int items);

    void setWalkable(const eWalkable& w);
    void setUnpackBuilding(eBuilding* const b);
private:
    eWorldCity& mCity;
    const eTradePostType mType;
    eResourceType mImports = eResourceType::none;
    eResourceType mExports = eResourceType::none;

    eWalkable mWalkable = eWalkableHelpers::sDefaultWalkable;
    eBuilding* mUnpackBuilding = this;

    eTile* mRouteStart = nullptr;

    int mRouteTimer = 0;
};

#endif // ETRADEPOST_H
