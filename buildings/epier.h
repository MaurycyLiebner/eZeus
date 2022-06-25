#ifndef EPIER_H
#define EPIER_H

#include "ebuilding.h"

class ePier : public eBuilding {
public:
    ePier(eGameBoard& board, const eOrientation o);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    void erase();

    void setTradePost(eBuilding* const b);
private:
    const eOrientation mO;
    eBuilding* mTradePost = nullptr;
};

#endif // EPIER_H
