#ifndef EHEROSHALL_H
#define EHEROSHALL_H

#include "buildings/ebuilding.h"

#include "characters/heroes/ehero.h"

class eHerosHall : public eBuilding {
public:
    eHerosHall(const eHeroType type, eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    static eBuildingType sHeroTypeToHallType(const eHeroType type);
    static eHeroType sHallTypeToHeroType(const eBuildingType type,
                                         bool* const valid = nullptr);
private:
    eHeroType mType;
};

#endif // EHEROSHALL_H
