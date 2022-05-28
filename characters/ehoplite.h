#ifndef EHOPLITE_H
#define EHOPLITE_H

#include "esoldier.h"

class eHoplite : public eSoldier {
public:
    eHoplite(eGameBoard& board);
    ~eHoplite();

    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const;
};

#endif // EHOPLITE_H
