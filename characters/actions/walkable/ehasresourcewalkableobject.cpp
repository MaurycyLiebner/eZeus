#include "ehasresourcewalkableobject.h"

#include "ehasresourceobject.h"

eHasResourceWalkableObject::eHasResourceWalkableObject(
        const stdsptr<eHasResourceObject>& hr,
        const stdsptr<eWalkableObject>& w) :
    eWalkableObject(eWalkableObjectType::hasResource),
    mHr(hr), mW(w) {}

eHasResourceWalkableObject::eHasResourceWalkableObject() :
    eWalkableObject(eWalkableObjectType::hasResource) {}

bool eHasResourceWalkableObject::walkable(eTileBase* const t) const {
    return mHr->has(t) || mW->walkable(t);
}

void eHasResourceWalkableObject::read(eReadStream& src) {
    mHr = src.readHasResource();
    mW = src.readWalkable();
}

void eHasResourceWalkableObject::write(eWriteStream& dst) const {
    dst.writeHasResource(mHr.get());
    dst.writeWalkable(mW.get());
}
