#ifndef EPIER_H
#define EPIER_H

#include "ebuilding.h"

class ePier : public eBuilding {
public:
    ePier(eGameBoard& board, const eOrientation o);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const eOrientation mO;
};

#endif // EPIER_H
