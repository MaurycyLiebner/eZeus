#ifndef EROADWALKABLEOBJECT_H
#define EROADWALKABLEOBJECT_H

#include "ewalkableobject.h"

class eRoadWalkableObject : public eWalkableObject {
public:
    eRoadWalkableObject();

    bool walkable(eTileBase* const t) const override;
};

#endif // EROADWALKABLEOBJECT_H
