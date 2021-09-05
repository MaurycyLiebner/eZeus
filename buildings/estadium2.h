#ifndef ESTADIUM2_H
#define ESTADIUM2_H

#include "epatroltarget.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eStadium2Base : public ePatrolTarget {
public:
    eStadium2Base(eGameBoard& board,
                  const eBaseTex baseTex);

    void timeChanged(const int by);
protected:
    int overlayId() const { return mOverlayId; }
private:
    int mOverlayTime = 0;
    int mOverlayId = 0;
};

class eStadium2W : public eStadium2Base {
public:
    eStadium2W(eGameBoard& board);

    std::vector<eOverlay> getOverlays(const eTileSize size) const;
};

class eStadium2H : public eStadium2Base {
public:
    eStadium2H(eGameBoard& board);

    std::vector<eOverlay> getOverlays(const eTileSize size) const;
};

#endif // ESTADIUM2_H
