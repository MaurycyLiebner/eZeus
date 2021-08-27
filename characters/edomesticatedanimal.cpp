#include "edomesticatedanimal.h"

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
