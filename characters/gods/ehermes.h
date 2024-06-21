#ifndef EHERMES_H
#define EHERMES_H

#include "egod.h"

class eHermes : public eGod {
public:
    eHermes(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EHERMES_H
