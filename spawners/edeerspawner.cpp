#include "edeerspawner.h"

#include "characters/edeer.h"
#include "characters/actions/eanimalaction.h"

eDeerSpawner::eDeerSpawner(eTile* const tile,
                           eGameBoard& board) :
    eSpawner(tile, 8, 3000, board) {

}

void eDeerSpawner::spawn(eTile* const tile) {
    const auto b = e::make_shared<eDeer>(board());
    b->setSpawner(this);
    b->changeTile(tile);
    const auto e = []() {};
    b->setAction(e::make_shared<eAnimalAction>(
                     b.get(), e, e, tile->x(), tile->y()));
}
