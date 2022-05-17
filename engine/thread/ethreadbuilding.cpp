#include "ethreadbuilding.h"

#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"
#include "buildings/eresourcebuildingbase.h"
#include "buildings/eresourcebuilding.h"

void eThreadBuilding::load(eBuilding* const src) {
    mVacancies = 0;

    memset(mResourceCount, 0, sizeof(mResourceCount));
    memset(mResource, 0, sizeof(mResourceCount));
    mAccepts = eResourceType::none;

    if(src) {
        mType = src->type();
        mTileRect = src->tileRect();
        if(mType == eBuildingType::commonHouse) {
            const auto h = static_cast<eSmallHouse*>(src);
            mVacancies = h->vacancies();
        } else if(mType == eBuildingType::eliteHousing) {
            const auto h = static_cast<eEliteHousing*>(src);
            mVacancies = h->vacancies();
        } else if(mType == eBuildingType::granary ||
                  mType == eBuildingType::warehouse) {
            const auto s = static_cast<eStorageBuilding*>(src);
            mAccepts = s->accepts();
            mGet = s->get();
            const auto rc = s->resourceCounts();
            const auto rt = s->resourceTypes();
            for(int i = 0; i < 8; i++) {
                mResourceCount[i] = rc[i];
                mResource[i] = rt[i];
            }
            mMaxCount = s->maxCount();
        } else if(const auto b = dynamic_cast<eResourceBuildingBase*>(src)) {
            mResource[0] = b->resourceType();
            mResourceCount[0] = b->resource();
        } else if(const auto b = dynamic_cast<eResourceBuilding*>(src)) {
            mWorkedOn = b->workedOn();
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
                                            mResource, mAccepts, mMaxCount);
    } else {
        return 0;
    }
}

bool eThreadBuilding::resourceHas(const eResourceType type) const {
    for(int i = 0; i < 8; i++) {
        const int c = mResourceCount[i];
        if(c <= 0) continue;
        const auto t = mResource[i];
        if(t != type) continue;
        return true;
    }
    return false;
}

bool eThreadBuilding::resourceHasSpace(const eResourceType type) const {
    return resourceSpaceLeft(type) > 0;
}
