#ifndef EANIMALACTION_H
#define EANIMALACTION_H

#include "ecomplexaction.h"

#include "emovearoundaction.h"

#include "walkable/ewalkableobject.h"

class eTileBase;

class eAnimalAction : public eComplexAction {
public:
    eAnimalAction(eCharacter* const c,
                  const int spawnerX, const int spawnerY,
                  const stdsptr<eWalkableObject>& tileWalkable =
                        eWalkableObject::sCreateDefault());
    eAnimalAction(eCharacter* const c);

    bool decide();

    void setLayTime(const int l) { mLayTime = l; }
    void setWalkTime(const int w) { mWalkTime = w; }

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;
private:
    int mSpawnerX;
    int mSpawnerY;

    stdsptr<eWalkableObject> mTileWalkable;

    int mLayTime = 2000;
    int mWalkTime = 3000;
};

#endif // EANIMALACTION_H
