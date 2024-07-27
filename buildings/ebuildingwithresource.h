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

struct eStash {
    eResourceType fType;
    int fCount;
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

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    const std::vector<eStash>& stash() const { return mStash; }
    int stash(const eResourceType type, const int count);
    int stashCount(const eResourceType type) const;
protected:
    void setStashable(const eResourceType s);
    void addFromStash();

    stdptr<eCartTransporter> spawnCart(const eCartActionTypeSupport s =
                                    eCartActionTypeSupport::both);
private:
    eResourceType mStashable = eResourceType::none;
    std::vector<eStash> mStash;
};

#endif // EBUILDINGWITHRESOURCE_H
