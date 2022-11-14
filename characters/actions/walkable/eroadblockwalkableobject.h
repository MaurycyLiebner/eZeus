#ifndef EROADBLOCKWALKABLEOBJECT_H
#define EROADBLOCKWALKABLEOBJECT_H

#include "ewalkableobject.h"

class eRoadblockWalkableObject : public eWalkableObject {
public:
    eRoadblockWalkableObject();

    bool walkable(eTileBase* const t) const override;
};

#endif // EROADBLOCKWALKABLEOBJECT_H
