#ifndef EFOODVENDOR_H
#define EFOODVENDOR_H

#include "epatrolbuilding.h"

class eFoodVendor : public ePatrolBuilding {
public:
    eFoodVendor(eGameBoard& board);

    std::vector<eOverlay> getOverlays(const eTileSize size) const;
private:
    int mResource = 0;
};

#endif // EFOODVENDOR_H
