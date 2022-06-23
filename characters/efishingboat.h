#ifndef EFISHINGBOAT_H
#define EFISHINGBOAT_H

#include "eresourcecollectorbase.h"

class eCharacterTextures;

class eFishingBoat : public eResourceCollectorBase {
public:
    eFishingBoat(eGameBoard& board);
    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EFISHINGBOAT_H
