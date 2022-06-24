#ifndef EWALKABLEHELPERS_H
#define EWALKABLEHELPERS_H

#include "engine/etile.h"
#include <SDL2/SDL_rect.h>

using eWalkable = std::function<bool(eTileBase*)>;
namespace eWalkableHelpers {
    bool sTileUnderBuilding(eTileBase* const t,
                            eBuilding* const b);
    bool sTileUnderBuilding(eTileBase* const t,
                            const SDL_Rect& b);

    using eWalkable = std::function<bool(eTileBase*)>;
    bool sDefaultWalkable(eTileBase* const t);
    bool sRoadWalkable(eTileBase* const t);
    eWalkable sBuildingWalkable(
            eBuilding* const b, const eWalkable& w);
    eWalkable sBuildingWalkable(
            const SDL_Rect& rect, const eWalkable& w);
};

#endif // EWALKABLEHELPERS_H
