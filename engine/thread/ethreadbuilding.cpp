#include "ethreadbuilding.h"

eThreadBuilding::eThreadBuilding() {

}

void eThreadBuilding::load(eBuilding* const src) {
    if(src) {
        mType = src->type();
    } else {
        mType = eBuildingType::none;
    }
}
