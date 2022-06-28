#ifndef EPALACETILE_H
#define EPALACETILE_H

#include "ebuilding.h"

class ePalace;

class ePalaceTile : public eBuilding {
public:
    ePalaceTile(eGameBoard& board,
                ePalace* const palace,
                const bool other);

    void erase();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    ePalace* palace() const { return mPalace; }
private:
    ePalace* const mPalace;
    const bool mOther;
};

#endif // EPALACETILE_H
