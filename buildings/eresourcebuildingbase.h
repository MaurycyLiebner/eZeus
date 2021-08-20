#ifndef ERESOURCEBUILDINGBASE_H
#define ERESOURCEBUILDINGBASE_H

#include "ebuilding.h"

class eResourceBuildingBase : public eBuilding {
public:
    using eBuilding::eBuilding;

    int resource() const { return mResource; }
    int incResource(const int by);
private:
    const int mMaxResource = 8;
    int mResource{0};
};

#endif // ERESOURCEBUILDINGBASE_H
