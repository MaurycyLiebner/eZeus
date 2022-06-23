#ifndef ERESOURCECOLLECTBUILDINGBASE_H
#define ERESOURCECOLLECTBUILDINGBASE_H

#include "eresourcebuildingbase.h"

class eResourceCollectBuildingBase : public eResourceBuildingBase {
public:
    using eResourceBuildingBase::eResourceBuildingBase;

    virtual void addRaw() = 0;
};

#endif // ERESOURCECOLLECTBUILDINGBASE_H
