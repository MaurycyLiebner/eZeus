#ifndef ECALYDONIANBOAR_H
#define ECALYDONIANBOAR_H

#include "emonster.h"

class eCalydonianBoar : public eMonster {
public:
    eCalydonianBoar(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // ECALYDONIANBOAR_H
