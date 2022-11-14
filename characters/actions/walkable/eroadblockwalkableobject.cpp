#include "eroadblockwalkableobject.h"

#include "engine/etilebase.h"

eRoadblockWalkableObject::eRoadblockWalkableObject() :
    eWalkableObject(eWalkableObjectType::roadblock) {}

bool eRoadblockWalkableObject::walkable(eTileBase* const t) const {
    const bool hr = t->hasRoad();
    if(!hr) return false;
    return !t->hasRoadblock();
}
