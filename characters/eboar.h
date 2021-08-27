#ifndef EBOAR_H
#define EBOAR_H

#include "ewildanimal.h"

class eBoar : public eWildAnimal {
public:
    eBoar(eSpawner* const s, eGameBoard& board);
};

#endif // EBOAR_H
