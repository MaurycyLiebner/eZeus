#ifndef ERESOURCECOLLECTBUILDINGBASE_H
#define ERESOURCECOLLECTBUILDINGBASE_H

#include "eresourcebuildingbase.h"

class eResourceCollectBuildingBase : public eResourceBuildingBase {
public:
    using eResourceBuildingBase::eResourceBuildingBase;

    virtual void addRaw() = 0;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void setNoTarget(const bool t);
    bool noTarget() const { return mNoTarget; }
private:
    bool mNoTarget = true;
};

#endif // ERESOURCECOLLECTBUILDINGBASE_H
