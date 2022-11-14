#include "eroadwalkableobject.h"

#include "engine/etilebase.h"

eRoadWalkableObject::eRoadWalkableObject() :
    eWalkableObject(eWalkableObjectType::road) {}

bool eRoadWalkableObject::walkable(eTileBase* const t) const {
    return t->hasRoad();
}
