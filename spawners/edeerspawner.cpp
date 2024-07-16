#include "edeerspawner.h"

#include "characters/edeer.h"
#include "characters/actions/eanimalaction.h"

eDeerSpawner::eDeerSpawner(const int id,
                           eTile* const tile,
                           eGameBoard& board) :
    eAnimalSpawner(eBannerTypeS::deer, id, tile, 8, 6000, board) {}


stdsptr<eWildAnimal> eDeerSpawner::create(eGameBoard& board) {
    const auto b = e::make_shared<eDeer>(board);
    return b;
}
