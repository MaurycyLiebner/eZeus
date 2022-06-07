#ifndef EBUILDINGWITHRESOURCE_H
#define EBUILDINGWITHRESOURCE_H

#include "ebuilding.h"

#include "engine/eresourcetype.h"
#include "characters/ecarttransporter.h"

enum class eCartActionType {
    take, give
};

struct eCartTask {
    eCartActionType fType;
    eResourceType fResource;
    int fMaxCount = 0;
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
    bool spawnCart(stdsptr<eCartTransporter>& cart,
                   const eCartActionTypeSupport s =
                    eCartActionTypeSupport::both);
};

#endif // EBUILDINGWITHRESOURCE_H
