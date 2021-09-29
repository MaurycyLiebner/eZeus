#include "esanctuary.h"

eSanctuary::eSanctuary(const eTexCollPtr statues,
                       const eTexCollPtr monuments,
                       eGameBoard& board,
                       const eBuildingType type,
                       const int sw, const int sh,
                       const int maxEmployees) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees),
    mStatues(statues), mMonuments(monuments) {}
