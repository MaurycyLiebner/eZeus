#ifndef ECARTTRANSPORTER_H
#define ECARTTRANSPORTER_H

#include "etransporterbase.h"

#include "engine/eresourcetype.h"

class eCartTransporter : public eTransporterBase {
public:
    eCartTransporter(eGameBoard& board);

    eOverlay getSecondaryTexture(const eTileSize size) const;
};

#endif // ECARTTRANSPORTER_H
