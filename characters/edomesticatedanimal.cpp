#include "edomesticatedanimal.h"

eDomesticatedAnimal::eDomesticatedAnimal(
        eGameBoard& board,
        const eCharTexs charTexs,
        const eCharacterType type,
        const int maxGroom) :
    eAnimal(board, charTexs, type),
    mMaxGroom(maxGroom) {}

void eDomesticatedAnimal::groom() {
    if(mResource >= 1) return;
    mGroomed++;
    if(mGroomed >= mMaxGroom) {
        mGroomed = 0;
        mResource = 1;
        setFleecedTexture();
    }
}

int eDomesticatedAnimal::collect() {
    if(mResource <= 0) return 0;
    const int r = mResource;
    mResource = 0;
    setNakedTexture();
    return r;
}

void eDomesticatedAnimal::read(eReadStream& src) {
    eAnimal::read(src);
    src >> mGroomed;
    src >> mResource;
    if(mResource == 0) {
        setNakedTexture();
    } else {
        setFleecedTexture();
    }
}

void eDomesticatedAnimal::write(eWriteStream& dst) const {
    eAnimal::write(dst);
    dst << mGroomed;
    dst << mResource;
}
