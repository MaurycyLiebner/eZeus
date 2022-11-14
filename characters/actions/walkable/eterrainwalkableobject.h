#ifndef ETERRAINWALKABLEOBJECT_H
#define ETERRAINWALKABLEOBJECT_H

#include "ewalkableobject.h"

class eTerrainWalkableObject : public eWalkableObject {
public:
    eTerrainWalkableObject();

    bool walkable(eTileBase* const t) const override;
};

#endif // ETERRAINWALKABLEOBJECT_H
