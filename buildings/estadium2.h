#ifndef ESTADIUM2_H
#define ESTADIUM2_H

#include "epatroltarget.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eStadium1Base;
class eStadium1W;
class eStadium1H;

class eStadium2Base : public ePatrolTarget {
public:
    eStadium2Base(eGameBoard& board,
                  const eBaseTex baseTex,
                  eStadium1Base* const s1);

    void timeChanged(const int by);
protected:
    int overlayId() const { return mOverlayId; }
private:
    int mOverlayTime = 0;
    int mOverlayId = 0;
};

class eStadium2W : public eStadium2Base {
public:
    eStadium2W(eGameBoard& board, eStadium1W* const s1);

    std::vector<eOverlay> getOverlays(const eTileSize size) const;
};

class eStadium2H : public eStadium2Base {
public:
    eStadium2H(eGameBoard& board, eStadium1H* const s1);

    std::vector<eOverlay> getOverlays(const eTileSize size) const;
};

#endif // ESTADIUM2_H
