#ifndef ESTORAGEBUILDING_H
#define ESTORAGEBUILDING_H

#include "ebuildingwithresource.h"

class eStorageBuilding : public eBuildingWithResource {
public:
    using eBuildingWithResource::eBuildingWithResource;

    int add(const eResourceType type, const int count);
    int take(const eResourceType type, const int count);

    int count(const eResourceType type) const;
    int spaceLeft(const eResourceType type) const;

    static int sCount(const eResourceType type,
                      const int resourceCount[8],
                      const eResourceType resourceType[8]);
    static int sSpaceLeft(const eResourceType type,
                          const int resourceCount[8],
                          const eResourceType resourceType[8],
                          const eResourceType accepts);

    int resourceCount(const int id) const { return mResourceCount[id]; }
    eResourceType resourceType(const int id) const { return mResource[id]; }

    const int* resourceCounts() const { return &mResourceCount[0]; }
    const eResourceType* resourceTypes() const { return &mResource[0]; }

    void setAccepts(const eResourceType a);
    eResourceType accepts() const { return mAccepts; }
private:
    eResourceType mAccepts = eResourceType::all;
    int mResourceCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    eResourceType mResource[8] = {eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none};
};

#endif // ESTORAGEBUILDING_H
