#ifndef EFERTILEWALKABLEOBJECT_H
#define EFERTILEWALKABLEOBJECT_H

#include "ewalkableobject.h"

class eFertileWalkableObject : public eWalkableObject {
public:
    eFertileWalkableObject();

    bool walkable(eTileBase* const t) const override;
};

#endif // EFERTILEWALKABLEOBJECT_H
