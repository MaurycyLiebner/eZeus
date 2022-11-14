#ifndef EHASRESOURCEOBJECT_H
#define EHASRESOURCEOBJECT_H

#include "fileIO/estreams.h"

class eTileBase;

enum class eHasResourceObjectType {
    nonBusy
};

class eHasResourceObject {
public:
    eHasResourceObject(const eHasResourceObjectType t) :
        mType(t) {}

    virtual bool has(eTileBase* const t) const = 0;

    virtual void read(eReadStream& src) {}
    virtual void write(eWriteStream& dst) const {}

    eHasResourceObjectType type() const { return mType; }

    static stdsptr<eHasResourceObject> sCreate(
            const eHasResourceObjectType type);

    static stdsptr<eHasResourceObject> sCreateNonBusy(
            const stdsptr<eHasResourceObject>& other);
private:
    const eHasResourceObjectType mType;
};

#endif // EHASRESOURCEOBJECT_H
