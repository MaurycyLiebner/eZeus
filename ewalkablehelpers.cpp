#include "ewalkablehelpers.h"

#include "buildings/ebuilding.h"

bool eWalkableHelpers::sDefaultWalkable(eTileBase* const t) {
    return t->walkable();
}

bool eWalkableHelpers::sRoadWalkable(eTileBase* const t) {
    return t->hasRoad();
}

eWalkableHelpers::eWalkable eWalkableHelpers::sBuildingWalkable(
        eBuilding* const b, const eWalkable& w) {
    const auto rect = b->tileRect();
    return sBuildingWalkable(rect, w);
}

eWalkableHelpers::eWalkable eWalkableHelpers::sBuildingWalkable(
        const SDL_Rect& rect, const eWalkable& w) {
    return [rect, w](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return w(t);
    };
}

bool eWalkableHelpers::sTileUnderBuilding(
        eTileBase* const t, eBuilding* const b) {
    return sTileUnderBuilding(t, b->tileRect());
}

bool eWalkableHelpers::sTileUnderBuilding(
        eTileBase* const t, const SDL_Rect& b) {
    const SDL_Point p{t->x(), t->y()};
    return SDL_PointInRect(&p, &b);
}

bool eWalkableHelpers::sRoadRoadblockWalkable(eTileBase* const t) {
    const bool hr = t->hasRoad();
    if(!hr) return false;
    return !t->hasRoadblock();
}

bool eWalkableHelpers::sBuildingsWalkable(eTileBase* const t) {
    const auto terr = t->terrain() & eTerrain::walkable;
    return static_cast<bool>(terr);
}

int eWalkableHelpers::sMonsterTileDistance(eTileBase* const tile) {
    const auto ubt = tile->underBuildingType();
    const bool r = eBuilding::sWalkableBuilding(ubt);
    if(r) return 1;
    return 4;
}

int eWalkableHelpers::sRoadAvenueTileDistance(eTileBase* const tile) {
    const auto type = tile->underBuildingType();
    const bool a = type == eBuildingType::avenue;
    if(a) return 10;
    return 1;
}
