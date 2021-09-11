#ifndef ERUINS_H
#define ERUINS_H

#include "ebuilding.h"

class eRuins : public eBuilding {
public:
    eRuins(eGameBoard& board);

    stdsptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // ERUINS_H
