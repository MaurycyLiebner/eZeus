#ifndef EAPPEAL_H
#define EAPPEAL_H

#include "buildings/ebuilding.h"

struct eAppeal {
    int fValue;
    int fRange;
};

namespace eAppealHelpers {
    double appealAtDist(const eBuildingType type, const int dist);
    eAppeal appeal(const eBuildingType type);
}

#endif // EAPPEAL_H
