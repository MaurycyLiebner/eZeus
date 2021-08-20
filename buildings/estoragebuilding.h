#ifndef ESTORAGEBUILDING_H
#define ESTORAGEBUILDING_H

#include "ebuilding.h"

enum class eResourceType {
    none = 0,
    urchin,
    fish,
    meat,
    cheese,
    carrots,
    onions,
    wheat
};

class eStorageBuilding : public eBuilding {
public:
    using eBuilding::eBuilding;

    int add(const eResourceType type, const int count);
    int take(const eResourceType type, const int count);

    int resourceCount(const int id) const { return mResourceCount[id]; }
    eResourceType resourceType(const int id) const { return mResource[id]; }
private:
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
