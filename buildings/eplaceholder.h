#ifndef EPLACEHOLDER_H
#define EPLACEHOLDER_H

#include "ebuilding.h"

class ePlaceholder : public eBuilding {
public:
    ePlaceholder(eGameBoard& board);

    stdsptr<eTexture> getTexture(const eTileSize size) const override;

    void erase() override;

    void sanctuaryErase();
};

#endif // EPLACEHOLDER_H
