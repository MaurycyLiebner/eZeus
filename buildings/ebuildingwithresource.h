#ifndef EBUILDINGWITHRESOURCE_H
#define EBUILDINGWITHRESOURCE_H

#include "ebuilding.h"

#include "engine/eresourcetype.h"

class eBuildingWithResource : public eBuilding {
public:
    using eBuilding::eBuilding;

    virtual int add(const eResourceType type, const int count) = 0;
    virtual int take(const eResourceType type, const int count) = 0;

    virtual int count(const eResourceType type) const = 0;
    virtual int spaceLeft(const eResourceType type) const = 0;
};

#endif // EBUILDINGWITHRESOURCE_H
