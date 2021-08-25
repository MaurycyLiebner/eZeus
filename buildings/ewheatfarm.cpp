#include "ewheatfarm.h"

eWheatFarm::eWheatFarm(eGameBoard& board) :
    eFarmBase(board, eBuildingType::wheatFarm, 3, 3,
              eResourceType::wheat) {}
