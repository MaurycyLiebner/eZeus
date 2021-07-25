#ifndef EMOVINGGAMEOBJECT_H
#define EMOVINGGAMEOBJECT_H

#include "egameobject.h"

class eMovingGameObject : public eGameObject {
public:
    using eGameObject::eGameObject;

    double xF() const { return mPosX; }
    double yF() const { return mPosY; }

    void moveToF(const double x, const double y);
    void moveByF(const double dx, const double dy);
private:
    double mPosX = 0;
    double mPosY = 0;
};

#endif // EMOVINGGAMEOBJECT_H
