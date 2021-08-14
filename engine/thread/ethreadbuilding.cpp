#include "ethreadbuilding.h"

void eThreadBuilding::load(eBuilding* const src) {
    if(src) {
        mType = src->type();
    } else {
        mType = eBuildingType::none;
    }
}
