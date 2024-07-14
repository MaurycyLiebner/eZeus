#ifndef EPALACETILE_H
#define EPALACETILE_H

#include "ebuilding.h"

class ePalace;

class ePalaceTile : public eBuilding {
public:
    ePalaceTile(eGameBoard& board,
                const bool other);

    void erase() override;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;

    int provide(const eProvide p, const int n) override;

    void setPalace(ePalace* const palace);
    ePalace* palace() const { return mPalace; }

    bool other() const { return mOther; }
private:
    ePalace* mPalace = nullptr;
    const bool mOther;
};

#endif // EPALACETILE_H
