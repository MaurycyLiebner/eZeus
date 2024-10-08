#ifndef EWALKABLEHELPERS_H
#define EWALKABLEHELPERS_H

#include "engine/etile.h"
#include <SDL2/SDL_rect.h>

#include "characters/actions/walkable/ewalkableobject.h"

using eWalkable = std::function<bool(eTileBase*)>;
namespace eWalkableHelpers {
    bool sTileUnderBuilding(eTileBase* const t,
                            eBuilding* const b);
    bool sTileUnderBuilding(eTileBase* const t,
                            const SDL_Rect& b);

    using eWalkable = std::function<bool(eTileBase*)>;
    bool sDefaultWalkable(eTileBase* const t);
    bool sRoadWalkable(eTileBase* const t);
    bool sRoadRoadblockWalkable(eTileBase* const t);
    bool sBuildingsWalkable(eTileBase* const t);
    int sMonsterTileDistance(eTileBase* const tile);
    int sRoadAvenueTileDistance(eTileBase* const tile);
    eWalkable sBuildingWalkable(
            eBuilding* const b, const eWalkable& w);
    eWalkable sBuildingWalkable(
            const SDL_Rect& rect, const eWalkable& w);
};

#endif // EWALKABLEHELPERS_H
