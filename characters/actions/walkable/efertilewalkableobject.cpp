#include "efertilewalkableobject.h"

#include "engine/etilebase.h"

eFertileWalkableObject::eFertileWalkableObject() :
    eWalkableObject(eWalkableObjectType::fertile) {}

bool eFertileWalkableObject::walkable(eTileBase* const t) const {
    const bool r = t->walkable();
    if(!r) return false;
    return t->terrain() == eTerrain::fertile;
}
