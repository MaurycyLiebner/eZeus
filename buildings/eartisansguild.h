#ifndef EARTISANSGUILD_H
#define EARTISANSGUILD_H

#include "eemployingbuilding.h"

class eArtisansGuild : public eEmployingBuilding {
public:
    eArtisansGuild(eGameBoard& board);
    ~eArtisansGuild();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

};

#endif // EARTISANSGUILD_H
