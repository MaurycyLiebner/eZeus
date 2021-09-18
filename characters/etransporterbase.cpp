#include "etransporterbase.h"

void eTransporterBase::setResource(const eResourceType type,
                           const int count) {
    mResourceType = type;
    mResourceCount = count;
}
