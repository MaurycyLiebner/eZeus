#include "eterrainwalkableobject.h"

#include "engine/etilebase.h"

eTerrainWalkableObject::eTerrainWalkableObject() :
    eWalkableObject(eWalkableObjectType::terrain) {}

bool eTerrainWalkableObject::walkable(eTileBase* const t) const {
    const auto terr = t->terrain() & eTerrain::walkable;
    return static_cast<bool>(terr);
}
