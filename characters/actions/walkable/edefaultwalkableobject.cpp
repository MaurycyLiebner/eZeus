#include "edefaultwalkableobject.h"

#include "engine/etilebase.h"

eDefaultWalkableObject::eDefaultWalkableObject() :
    eWalkableObject(eWalkableObjectType::ddefault) {}

bool eDefaultWalkableObject::walkable(eTileBase* const t) const {
    return t->walkable();
}
