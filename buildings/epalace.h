#ifndef EPALACE_H
#define EPALACE_H

#include "ebuilding.h"

class ePalaceTile;

class ePalace : public eBuilding {
public:
    ePalace(eGameBoard& board, const bool r);
    ~ePalace();

    void erase();

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const { return nullptr; }

    std::shared_ptr<eTexture>
    getTexture1(const eTileSize size) const;
    std::shared_ptr<eTexture>
    getTexture2(const eTileSize size) const;

    std::vector<eOverlay>
    getOverlays2(const eTileSize size) const;

    void addTile(const stdsptr<ePalaceTile>& tile);
private:
    const bool mRotated;
    std::vector<stdsptr<ePalaceTile>> mTiles;
};

#endif // EPALACE_H
