#ifndef EPALACE_H
#define EPALACE_H

#include "ebuilding.h"

class ePalaceTile;

class ePalace : public eBuilding {
public:
    ePalace(eGameBoard& board, const bool r);
    ~ePalace();

    void erase() override;

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const override { return nullptr; }

    std::shared_ptr<eTexture>
    getTexture1(const eTileSize size) const;
    std::shared_ptr<eTexture>
    getTexture2(const eTileSize size) const;

    std::vector<eOverlay>
    getOverlays2(const eTileSize size) const;

    void addTile(ePalaceTile* const tile);

    const std::vector<ePalaceTile*>& tiles() const { return mTiles; }

    bool rotated() const { return mRotated; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    const bool mRotated;
    std::vector<ePalaceTile*> mTiles;
};

#endif // EPALACE_H
