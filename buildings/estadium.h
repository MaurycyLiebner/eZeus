#ifndef ESTADIUM_H
#define ESTADIUM_H

#include "epatroltarget.h"

class eStadium : public ePatrolTarget {
public:
    eStadium(eGameBoard& board, const bool r);
    ~eStadium();

    std::shared_ptr<eTexture> getTexture1(const eTileSize size) const;
    std::shared_ptr<eTexture> getTexture2(const eTileSize size) const;

    std::vector<eOverlay> getOverlays2(const eTileSize size) const;

    void timeChanged(const int by);
protected:
    int overlayId() const { return mOverlayId; }
    int overlayTime() const { return mOverlayTime/4; }
private:
    const bool mRotated;

    int mOverlayTime = 0;
    int mOverlayId = 0;
};

#endif // ESTADIUM_H
