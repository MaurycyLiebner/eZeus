#include "eboarspawner.h"

#include "characters/eboar.h"
#include "characters/actions/eanimalaction.h"

eBoarSpawner::eBoarSpawner(eTile* const tile,
                           eGameBoard& board) :
    eSpawner(tile, 8, 3000, board) {

}

void eBoarSpawner::spawn(eTile* const tile) {
    const auto b = e::make_shared<eBoar>(this, board());
    b->changeTile(tile);
    const auto e = []() {};
    b->setAction(e::make_shared<eAnimalAction>(
                     b.get(), e, e, tile->x(), tile->y()));
}
