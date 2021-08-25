#include "eonionfarm.h"

eOnionFarm::eOnionFarm(eGameBoard& board) :
    eFarmBase(board, eBuildingType::onionsFarm, 3, 3,
              eResourceType::onions) {}
