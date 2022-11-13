#include "ewildanimal.h"

#include "spawners/espawner.h"

eWildAnimal::eWildAnimal(eGameBoard& board,
                         const eCharTexs charTexs,
                         const eCharacterType type) :
    eAnimal(board, charTexs, type) {}

eWildAnimal::~eWildAnimal() {
    if(mSpawner) mSpawner->decCount();
}
