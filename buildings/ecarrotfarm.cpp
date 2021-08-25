#include "ecarrotfarm.h"

eCarrotFarm::eCarrotFarm(eGameBoard& board) :
    eFarmBase(board, eBuildingType::carrotsFarm, 3, 3,
              eResourceType::carrots) {}

