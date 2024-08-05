#ifndef EDOMESTICATEDANIMAL_H
#define EDOMESTICATEDANIMAL_H

#include "eanimal.h"

class eDomesticatedAnimal : public eAnimal {
public:
    using eCharTexs = eAnimalTextures eCharacterTextures::*;
    eDomesticatedAnimal(eGameBoard& board,
                        const eCharTexs charTexs,
                        const eCharacterType type,
                        const int maxGroom);

    void groom();
    int collect();
    bool canCollect() const { return mResource; }

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;
private:
    virtual void setNakedTexture() {}
    virtual void setFleecedTexture() {}

    const int mMaxGroom;
    int mGroomed = 0;
    int mResource = 0;
};

#endif // EDOMESTICATEDANIMAL_H
