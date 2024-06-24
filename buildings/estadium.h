#ifndef ESTADIUM_H
#define ESTADIUM_H

#include "epatroltarget.h"

class eStadium : public ePatrolTarget {
public:
    eStadium(eGameBoard& board, const bool r);
    ~eStadium();

    void timeChanged(const int by) override;

    eTextureSpace
    getTextureSpace(const int tx, const int ty,
                    const eTileSize size) const override;

    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    bool rotated() const { return mRotated; }
protected:
    int overlayId() const { return mOverlayId; }
    int overlayTime() const { return mOverlayTime/4; }
private:
    const bool mRotated;

    int mOverlayTime = 0;
    int mOverlayId = 0;
};

#endif // ESTADIUM_H
