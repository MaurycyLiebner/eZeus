#include "eresourcebuildingbase.h"

int eResourceBuildingBase::incResource(const int by) {
    const int r = std::clamp(mResource + by, 0, mMaxResource);
    const int result = mResource - r;
    mResource = r;
    return result;
}
