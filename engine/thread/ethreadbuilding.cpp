#include "ethreadbuilding.h"

#include "buildings/esmallhouse.h"

void eThreadBuilding::load(eBuilding* const src) {
    mData1 = 0;
    if(src) {
        mType = src->type();
        if(src->type() == eBuildingType::commonHouse) {
            const auto h = static_cast<eSmallHouse*>(src);
            mData1 = h->vacancies();
        }
    } else {
        mType = eBuildingType::none;
    }
}
