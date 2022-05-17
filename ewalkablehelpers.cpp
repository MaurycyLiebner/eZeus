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
