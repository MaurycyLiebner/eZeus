#ifndef EBUILDINGWITHRESOURCE_H
#define EBUILDINGWITHRESOURCE_H

#include "ebuilding.h"

#include "engine/eresourcetype.h"

class eCartTransporter;

enum class eCartActionType {
    take, give
};

struct eCartTask {
    eCartActionType fType;
    eResourceType fResource;
    int fMaxCount;
};

class eBuildingWithResource : public eBuilding {
public:
    using eBuilding::eBuilding;

    virtual int add(const eResourceType type, const int count) {
        (void)type;
        (void)count;
        return 0;
    }
    virtual int take(const eResourceType type, const int count) {
        (void)type;
        (void)count;
        return 0;
    }

    virtual int count(const eResourceType type) const {
        (void)type;
        return 0;
    }

    virtual int spaceLeft(const eResourceType type) const {
        (void)type;
        return 0;
    }

    virtual std::vector<eCartTask> cartTasks() const {
        return {};
    }
protected:
    bool spawnCart(stdsptr<eCartTransporter>& cart);
};

#endif // EBUILDINGWITHRESOURCE_H
