#ifndef EHEATGETTERS_H
#define EHEATGETTERS_H

#include "buildings/ebuilding.h"
#include "engine/boardData/eheatmap.h"

namespace eHeatGetters {
    eHeat appeal(const eBuildingType type);
    eHeat housing(const eBuildingType type);
    eHeat culture(const eBuildingType type);
    eHeat industry(const eBuildingType type);
    eHeat farming(const eBuildingType type);
    eHeat storage(const eBuildingType type);
}

#endif // EHEATGETTERS_H
