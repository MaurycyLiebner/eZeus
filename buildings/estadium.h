#ifndef ESTADIUM_H
#define ESTADIUM_H

#include "epatroltarget.h"

class eStadium : public ePatrolTarget {
public:
    eStadium(eGameBoard& board, const bool r);
    ~eStadium();

    eTextureSpace
    getTextureSpace(const int tx, const int ty,
                    const eTileSize size) const override;

    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    bool rotated() const { return mRotated; }
private:
    const bool mRotated;
};

#endif // ESTADIUM_H
