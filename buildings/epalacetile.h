#ifndef EPALACETILE_H
#define EPALACETILE_H

#include "ebuilding.h"

class ePalace;

class ePalaceTile : public eBuilding {
public:
    ePalaceTile(eGameBoard& board,
                const bool other);

    void erase();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    void setPalace(ePalace* const palace);
    ePalace* palace() const { return mPalace; }

    bool other() const { return mOther; }
private:
    ePalace* mPalace = nullptr;
    const bool mOther;
};

#endif // EPALACETILE_H
