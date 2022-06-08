#ifndef ETRADEPOST_H
#define ETRADEPOST_H

#include "ewarehousebase.h"

#include "engine/eworldcity.h"

class eTradePost : public eWarehouseBase {
public:
    eTradePost(eGameBoard& board, eWorldCity& city);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void setOrders(const eResourceType imports,
                   const eResourceType exports);

    void getOrders(eResourceType& imports,
                   eResourceType& exports) const;

    eWorldCity& city() { return mCity; }
private:
    eWorldCity& mCity;
    eResourceType mImports = eResourceType::none;
    eResourceType mExports = eResourceType::none;
};

#endif // ETRADEPOST_H
