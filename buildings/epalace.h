#ifndef EPALACE_H
#define EPALACE_H

#include "ebuilding.h"

class ePalace : public eBuilding {
public:
    ePalace(eGameBoard& board, const bool r);
    ~ePalace();

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const { return nullptr; }

    std::shared_ptr<eTexture>
    getTexture1(const eTileSize size) const;
    std::shared_ptr<eTexture>
    getTexture2(const eTileSize size) const;

    std::vector<eOverlay>
    getOverlays2(const eTileSize size) const;
private:
    const bool mRotated;
};

#endif // EPALACE_H
