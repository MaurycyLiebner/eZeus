#include "edeerspawner.h"

#include "characters/edeer.h"
#include "characters/actions/eanimalaction.h"

eDeerSpawner::eDeerSpawner(eTile* const tile,
                           eGameBoard& board) :
    eSpawner(tile, 8, 3000, board) {

}

void eDeerSpawner::spawn(eTile* const tile) {
    const auto b = new eDeer(this, board());
    b->setTile(tile);
    tile->addCharacter(b);
    const auto e = []() {};
    b->setAction(new eAnimalAction(b, e, e, tile->x(), tile->y()));
}
