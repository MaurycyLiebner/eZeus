#ifndef EBOAR_H
#define EBOAR_H

#include "eanimal.h"

class eBoar : public eAnimal {
public:
    eBoar(eSpawner* const s, eGameBoard& board);
};

#endif // EBOAR_H
