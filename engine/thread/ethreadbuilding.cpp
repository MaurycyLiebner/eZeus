#include "ethreadbuilding.h"

#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"
#include "buildings/eresourcebuildingbase.h"
#include "buildings/eresourcebuilding.h"
#include "buildings/sanctuaries/esanctbuilding.h"
#include "buildings/eanimalbuilding.h"
#include "buildings/echariotfactory.h"
#include "buildings/ehorseranch.h"
#include "buildings/sanctuaries/esanctuary.h"

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
                  mType == eBuildingType::warehouse ||
                  mType == eBuildingType::tradePost) {
            const auto s = static_cast<eStorageBuilding*>(src);
            mAccepts = s->accepts();
            mGet = s->get();
            const auto rc = s->resourceCounts();
            const auto rt = s->resourceTypes();
            mSpaceCount = s->spaceCount();
            for(int i = 0; i < mSpaceCount; i++) {
                mResourceCount[i] = rc[i];
                mResource[i] = rt[i];
            }
            mMaxCount = s->maxCount();
        } else if(const auto b = dynamic_cast<eResourceBuildingBase*>(src)) {
            mResource[0] = b->resourceType();
            mResourceCount[0] = b->resource();
            mSpaceCount = 1;
        } else if(const auto b = dynamic_cast<eHorseRanch*>(src)) {
            mResource[0] = eResourceType::horse;
            mResourceCount[0] = b->horseCount();
            mSpaceCount = 1;
        } else if(const auto b = dynamic_cast<eChariotFactory*>(src)) {
            mResource[0] = eResourceType::chariot;
            mResourceCount[0] = b->chariotCount();
            mSpaceCount = 1;
        } else if(const auto b = dynamic_cast<eResourceBuilding*>(src)) {
            mWorkedOn = b->workedOn();
        } else if(const auto b = dynamic_cast<eSanctBuilding*>(src)) {
            mWorkedOn = b->workedOn();
            const auto s = b->sanctuary();
            const bool h = s->constructionHalted();
            if(h) {
                mResourcesAvailable = false;
            } else {
                mResourcesAvailable = b->resourcesAvailable();
            }
        } else if(const auto b = dynamic_cast<eAnimalBuilding*>(src)) {
            mWorkedOn = b->animal();
        }
    } else {
        mType = eBuildingType::none;
    }
}

int eThreadBuilding::resourceCount(const eResourceType type) const {
    if(mType == eBuildingType::granary ||
       mType == eBuildingType::warehouse ||
       mType == eBuildingType::tradePost) {
        return eStorageBuilding::sCount(type, mResourceCount,
                                        mResource, mSpaceCount);
    } else {
        const auto t = mResource[0];
        if(!static_cast<bool>(t & type)) return 0;
        return mResourceCount[0];
    }
}

int eThreadBuilding::resourceSpaceLeft(const eResourceType type) const {
    const bool accepts = static_cast<bool>(mAccepts & type);
    if(!accepts) return 0;
    if(mType == eBuildingType::granary ||
       mType == eBuildingType::warehouse ||
       mType == eBuildingType::tradePost) {
        return eStorageBuilding::sSpaceLeft(type, mResourceCount, mResource,
                                            mAccepts, mMaxCount, mSpaceCount);
    } else {
        return 0;
    }
}

bool eThreadBuilding::resourceHas(const eResourceType type) const {
    for(int i = 0; i < mSpaceCount; i++) {
        const int c = mResourceCount[i];
        if(c <= 0) continue;
        const auto t = mResource[i];
        if(!static_cast<bool>(t & type)) continue;
        return true;
    }
    return false;
}

bool eThreadBuilding::resourceHasSpace(const eResourceType type) const {
    return resourceSpaceLeft(type) > 0;
}
