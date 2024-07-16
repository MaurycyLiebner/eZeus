#include "eboarspawner.h"

#include "characters/eboar.h"

eBoarSpawner::eBoarSpawner(const int id,
                           eTile* const tile,
                           eGameBoard& board) :
    eAnimalSpawner(eBannerTypeS::boar, id, tile, 8, 3000, board) {}

stdsptr<eWildAnimal> eBoarSpawner::create(eGameBoard& board) {
    const auto b = e::make_shared<eBoar>(board);
    return b;
}
