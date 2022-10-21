#ifndef EGATEHOUSE_H
#define EGATEHOUSE_H

#include "ebuilding.h"

class eGatehouse : public eBuilding {
public:
    eGatehouse(eGameBoard& board, const bool r);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const { return nullptr; }

    std::shared_ptr<eTexture>
    getTextureSides(const eTileSize size) const;
    eOverlay
    getTextureEntrance(const eTileSize size) const;
    eOverlay
    getTextureEntranceBack(const eTileSize size) const;
    eOverlay
    getTextureEntranceOverlay(const eTileSize size) const;

    bool rotated() const { return mRotated; }
private:
    const bool mRotated;
};


#endif // EGATEHOUSE_H
