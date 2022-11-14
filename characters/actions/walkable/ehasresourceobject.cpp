#include "ehasresourceobject.h"

#include "ehasnonbusyresourceobject.h"

stdsptr<eHasResourceObject> eHasResourceObject::sCreate(
        const eHasResourceObjectType type) {
    switch(type) {
    case eHasResourceObjectType::nonBusy:
        return std::make_shared<eHasNonBusyResourceObject>();
    }
}

stdsptr<eHasResourceObject> eHasResourceObject::sCreateNonBusy(
        const stdsptr<eHasResourceObject>& other) {
    return std::make_shared<eHasNonBusyResourceObject>(other);
}
