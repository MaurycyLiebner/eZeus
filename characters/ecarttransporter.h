#ifndef ECARTTRANSPORTER_H
#define ECARTTRANSPORTER_H

#include "ebasicpatroler.h"

#include "engine/eresourcetype.h"

class eCartTransporter : public eBasicPatroler {
public:
    eCartTransporter(eGameBoard& board);

    eTexture getSecondaryTexture(const eTileSize size) const;

    void setResource(const eResourceType type,
                     const int count);

    int resourceCount() const { return mResourceCount; }
    eResourceType resourceType() const { return mResourceType; }
private:
    int mResourceCount = 0;
    eResourceType mResourceType = eResourceType::none;
};

#endif // ECARTTRANSPORTER_H
