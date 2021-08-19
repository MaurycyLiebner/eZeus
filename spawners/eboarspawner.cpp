#include "eboarspawner.h"

#include "characters/eboar.h"
#include "characters/actions/emovearoundaction.h"

eBoarSpawner::eBoarSpawner(eTile* const tile,
                           eGameBoard& board) :
    eSpawner(tile, 8, 3000, board) {

}

void eBoarSpawner::spawn(eTile* const tile) {
    const auto b = new eBoar(this, board());
    b->setTile(tile);
    tile->addCharacter(b);
    b->setActionType(eCharacterActionType::walk);
    b->setAction(new eMoveAroundAction(b));
}
