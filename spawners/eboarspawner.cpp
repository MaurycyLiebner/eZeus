#include "eboarspawner.h"

#include "characters/eboar.h"
#include "characters/actions/emovearoundaction.h"

eBoarSpawner::eBoarSpawner(eTile* const tile,
                           eGameBoard& board) :
    eSpawner(tile, 8, 1500, board) {

}

void eBoarSpawner::spawn(eTile* const tile) {
    const auto b = new eBoar(this, board());
    b->setTile(tile);
    tile->addCharacter(b);
    b->setAction(eAnimalAction::walk);
    b->setCharAction(new eMoveAroundAction(b));
}
