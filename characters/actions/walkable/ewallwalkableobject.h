#ifndef EWALLWALKABLEOBJECT_H
#define EWALLWALKABLEOBJECT_H

#include "ewalkableobject.h"

class eWallWalkableObject : public eWalkableObject {
public:
    eWallWalkableObject();

    bool walkable(eTileBase* const t) const override;
};

#endif // EWALLWALKABLEOBJECT_H
