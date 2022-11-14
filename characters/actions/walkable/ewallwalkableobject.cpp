#include "ewallwalkableobject.h"

#include "buildings/ebuilding.h"
#include "engine/etilebase.h"

eWallWalkableObject::eWallWalkableObject() :
    eWalkableObject(eWalkableObjectType::wall) {}

bool eWallWalkableObject::walkable(eTileBase* const t) const {
    const auto checker = [](eTileBase* const t) {
        if(!t) return false;
        const auto ubt = t->underBuildingType();
        return ubt == eBuildingType::wall ||
               ubt == eBuildingType::tower;
    };
    if(!checker(t)) return false;
    const auto bl = t->tileRel(0, 1);
    if(!checker(bl)) return false;
    const auto br = t->tileRel(1, 0);
    if(!checker(br)) return false;
    const auto b = t->tileRel(1, 1);
    if(!checker(b)) return false;
    return true;
}
