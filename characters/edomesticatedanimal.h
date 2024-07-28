#ifndef EDOMESTICATEDANIMAL_H
#define EDOMESTICATEDANIMAL_H

#include "eanimal.h"

class eDomesticatedAnimal : public eAnimal {
public:
    using eAnimal::eAnimal;

    void groom();
    int collect();
    bool canCollect() const { return mResource; }
protected:
    void setMaxGroom(const int g) { mMaxGroom = g; }
private:
    virtual void setNakedTexture() {}
    virtual void setFleecedTexture() {}

    int mMaxGroom = 15;
    int mGroomed = 0;
    int mResource = 0;
};

#endif // EDOMESTICATEDANIMAL_H
