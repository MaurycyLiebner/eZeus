#include "eboarspawner.h"

#include "characters/eboar.h"
#include "characters/actions/eanimalaction.h"

eBoarSpawner::eBoarSpawner(const int id,
                           eTile* const tile,
                           eGameBoard& board) :
    eSpawner(eBannerTypeS::boar, id, tile, 8, 3000, board) {}

void eBoarSpawner::spawn(eTile* const tile) {
    const auto b = e::make_shared<eBoar>(board());
    b->setSpawner(this);
    b->changeTile(tile);
    const auto a = e::make_shared<eAnimalAction>(
                       b.get(), tile->x(), tile->y());
    b->setAction(a);
}
