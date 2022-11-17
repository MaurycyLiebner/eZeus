#include "ewildanimal.h"

#include "spawners/espawner.h"

eWildAnimal::eWildAnimal(eGameBoard& board,
                         const eCharTexs charTexs,
                         const eCharacterType type) :
    eAnimal(board, charTexs, type) {}

eWildAnimal::~eWildAnimal() {
    if(mSpawner) mSpawner->decCount();
}

void eWildAnimal::read(eReadStream& src) {
    eAnimal::read(src);
    src.readBanner(&getBoard(), [this](eBanner* const b) {
        mSpawner = static_cast<eSpawner*>(b);
    });
}

void eWildAnimal::write(eWriteStream& dst) const {
    eAnimal::write(dst);
    dst.writeBanner(mSpawner);
}
