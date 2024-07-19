#ifndef ETRIREME_H
#define ETRIREME_H

#include "eboatbase.h"

class eTrireme : public eBoatBase {
public:
    eTrireme(eGameBoard& board);

    eOverlay getSecondaryTexture(const eTileSize size) const override;
};

#endif // ETRIREME_H
