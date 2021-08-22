#include "ethreadbuilding.h"

#include "buildings/esmallhouse.h"
#include "buildings/eresourcebuildingbase.h"

void eThreadBuilding::load(eBuilding* const src) {
    mVacancies = 0;

    memset(mResourceCount, 0, sizeof(mResourceCount));
    memset(mResource, 0, sizeof(mResourceCount));
    mAccepts = eResourceType::none;

    if(src) {
        mType = src->type();
        if(mType == eBuildingType::commonHouse) {
            const auto h = static_cast<eSmallHouse*>(src);
            mVacancies = h->vacancies();
        } else if(mType == eBuildingType::granary ||
                  mType == eBuildingType::warehouse) {
            const auto s = static_cast<eStorageBuilding*>(src);
            mAccepts = s->accepts();
            const auto rc = s->resourceCounts();
            const auto rt = s->resourceTypes();
            for(int i = 0; i < 8; i++) {
                mResourceCount[i] = rc[i];
                mResource[i] = rt[i];
            }
        } else if(const auto b = dynamic_cast<eResourceBuildingBase*>(src)) {
            mResource[0] = b->resourceType();
            mResourceCount[0] = b->resource();
        }
    } else {
        mType = eBuildingType::none;
    }
}

int eThreadBuilding::resourceCount(const eResourceType type) const {
    if(mType == eBuildingType::granary ||
       mType == eBuildingType::warehouse) {
        return eStorageBuilding::sCount(type, mResourceCount, mResource);
    } else {
        const auto t = mResource[0];
        if(t != type) return 0;
        return mResourceCount[0];
    }
}

int eThreadBuilding::resourceSpaceLeft(const eResourceType type) const {
    const bool accepts = static_cast<bool>(mAccepts & type);
    if(!accepts) return 0;
    if(mType == eBuildingType::granary ||
       mType == eBuildingType::warehouse) {
        return eStorageBuilding::sSpaceLeft(type, mResourceCount,
                                            mResource, mAccepts);
    } else {
        return 0;
    }
}
