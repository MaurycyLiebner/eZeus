#ifndef ESHEEP_H
#define ESHEEP_H

#include "edomesticatedanimal.h"

class eSheep : public eDomesticatedAnimal {
public:
    eSheep(eGameBoard& board);

private:
    void setNakedTexture();
    void setFleecedTexture();
};

#endif // ESHEEP_H
