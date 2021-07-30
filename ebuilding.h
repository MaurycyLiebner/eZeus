#ifndef EBUILDING_H
#define EBUILDING_H

#include "etexturecollection.h"

class eBuilding {
public:
    eBuilding(eTexture& tex,
              const std::vector<std::pair<int, int>>& overlayPos,
              std::vector<eTextureCollection>& overlays);

    void incTime() { mTime++; };
    void draw(ePainter& p,
              const int x, const int y,
              const eAlignment align);
private:
    int mTime = 0;

    eTexture& mTex;
    const std::vector<std::pair<int, int>> mOverlayPos;
    std::vector<eTextureCollection>& mOverlays;
};

#endif // EBUILDING_H
