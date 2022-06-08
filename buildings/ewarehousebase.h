#ifndef EWAREHOUSEBASE_H
#define EWAREHOUSEBASE_H

#include "estoragebuilding.h"

class eWarehouseBase : public eStorageBuilding {
public:
    using eStorageBuilding::eStorageBuilding;

    using eXY = std::vector<std::pair<double, double>>;
    void getSpaceOverlays(const eTileSize size,
                          std::vector<eOverlay>& os,
                          const eXY& xy) const;
};

#endif // EWAREHOUSEBASE_H
