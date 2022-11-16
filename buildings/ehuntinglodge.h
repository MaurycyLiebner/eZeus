#ifndef EHUNTINGLODGE_H
#define EHUNTINGLODGE_H

#include "eresourcebuildingbase.h"

#include "textures/ebuildingtextures.h"

class eHunter;

class eHuntingLodge : public eResourceBuildingBase {
public:
    eHuntingLodge(eGameBoard& board);
    ~eHuntingLodge();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged(const int by);

    bool spawn();
private:
    stdptr<eHunter> mHunter;
};

#endif // EHUNTINGLODGE_H
