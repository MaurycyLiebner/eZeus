#ifndef EDOMESTICATEDANIMAL_H
#define EDOMESTICATEDANIMAL_H

#include "eanimal.h"

class eDomesticatedAnimal : public eAnimal {
public:
    using eAnimal::eAnimal;

    void groom();
    int collect();
    bool canCollect() const { return mResource; }
    void setBusy(const bool b) { mBusy = b; }
    bool busy() const { return mBusy; }
private:
    virtual void setNakedTexture() {}
    virtual void setFleecedTexture() {}

    const int mMaxGroom = 50;
    bool mBusy = false;
    int mGroomed = 0;
    int mResource = 0;
};

#endif // EDOMESTICATEDANIMAL_H
