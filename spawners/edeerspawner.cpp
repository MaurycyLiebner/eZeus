#include "edeerspawner.h"

#include "characters/edeer.h"
#include "enumbers.h"

eDeerSpawner::eDeerSpawner(const int id,
                           eTile* const tile,
                           eGameBoard& board) :
    eAnimalSpawner(eBannerTypeS::deer, id, tile,
                   eNumbers::sDeerMaxCount,
                   eNumbers::sDeerSpawnPeriod, board) {}


stdsptr<eWildAnimal> eDeerSpawner::create(eGameBoard& board) {
    const auto b = e::make_shared<eDeer>(board);
    return b;
}
