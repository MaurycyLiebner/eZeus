#include "ethreadbuilding.h"

#include "buildings/esmallhouse.h"

void eThreadBuilding::load(eBuilding* const src) {
    mVacancies = 0;

    memset(mResourceCount, 0, sizeof(mResourceCount));
    memset(mResource, 0, sizeof(mResourceCount));

    if(src) {
        mType = src->type();
        if(mType == eBuildingType::commonHouse) {
            const auto h = static_cast<eSmallHouse*>(src);
            mVacancies = h->vacancies();
        } else if(mType == eBuildingType::granary ||
                  mType == eBuildingType::warehouse) {
            const auto s = static_cast<eStorageBuilding*>(src);
            const auto rc = s->resourceCounts();
            const auto rt = s->resourceTypes();
            for(int i = 0; i < 8; i++) {
                mResourceCount[i] = rc[i];
                mResource[i] = rt[i];
            }
        }
    } else {
        mType = eBuildingType::none;
    }
}

int eThreadBuilding::resourceCount(const eResourceType type) const {
    return eStorageBuilding::sCount(type, mResourceCount, mResource);
}

int eThreadBuilding::resourceSpaceLeft(const eResourceType type) const {
    return eStorageBuilding::sSpaceLeft(type, mResourceCount, mResource);
}
