#include "ewildanimal.h"

#include "spawners/espawner.h"

eWildAnimal::eWildAnimal(eSpawner* const s,
                         eGameBoard& board,
                         const eCharTexs charTexs,
                         const eCharacterType type) :
    eAnimal(board, charTexs, type),
    mSpawner(s) {

}

eWildAnimal::~eWildAnimal() {
    mSpawner->decCount();
}
