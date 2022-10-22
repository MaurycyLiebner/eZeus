#ifndef ERESOURCEBUILDINGBASE_H
#define ERESOURCEBUILDINGBASE_H

#include "eemployingbuilding.h"

class eCartTransporter;

class eResourceBuildingBase : public eEmployingBuilding {
public:
    eResourceBuildingBase(eGameBoard& board,
                          const eBuildingType type,
                          const int sw, const int sh,
                          const int maxEmployees,
                          const eResourceType resType);
    ~eResourceBuildingBase();

    void timeChanged(const int by) override;

    int add(const eResourceType type, const int count) override;
    int take(const eResourceType type, const int count) override;

    int count(const eResourceType type) const override;
    int spaceLeft(const eResourceType type) const override;

    std::vector<eCartTask> cartTasks() const override;

    eResourceType resourceType() const { return mResType; }
    int resource() const { return mResource; }
    int maxResource() const { return mMaxResource; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    const int mMaxResource = 8;

    const eResourceType mResType;

    int mResource{0};

    stdsptr<eCartTransporter> mCart;
};

#endif // ERESOURCEBUILDINGBASE_H
