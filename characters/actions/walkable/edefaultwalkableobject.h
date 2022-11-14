#ifndef EDEFAULTWALKABLEOBJECT_H
#define EDEFAULTWALKABLEOBJECT_H

#include "ewalkableobject.h"

class eDefaultWalkableObject : public eWalkableObject {
public:
    eDefaultWalkableObject();

    bool walkable(eTileBase* const t) const override;
};

#endif // EDEFAULTWALKABLEOBJECT_H
