#ifndef ERECTWALKABLEOBJECT_H
#define ERECTWALKABLEOBJECT_H

#include "ewalkableobject.h"

class eRectWalkableObject : public eWalkableObject {
public:
    eRectWalkableObject(const stdsptr<eWalkableObject>& other,
                        const SDL_Rect& rect);
    eRectWalkableObject(const SDL_Rect& rect);
    eRectWalkableObject();

    bool walkable(eTileBase* const t) const override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    stdsptr<eWalkableObject> mOther;
    SDL_Rect mRect;
};

#endif // ERECTWALKABLEOBJECT_H
