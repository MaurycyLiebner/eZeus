#include "ehasnonbusyresourceobject.h"

#include "engine/etilebase.h"

eHasNonBusyResourceObject::eHasNonBusyResourceObject(
        const stdsptr<eHasResourceObject>& other) :
    eHasResourceObject(eHasResourceObjectType::nonBusy),
    mOther(other) {}

eHasNonBusyResourceObject::eHasNonBusyResourceObject() :
    eHasResourceObject(eHasResourceObjectType::nonBusy) {}

bool eHasNonBusyResourceObject::has(eTileBase* const t) const {
    return !t->busy() && mOther->has(t);
}

void eHasNonBusyResourceObject::read(eReadStream& src) {
    mOther = src.readHasResource();
}

void eHasNonBusyResourceObject::write(eWriteStream& dst) const {
    dst.writeHasResource(mOther.get());
}
