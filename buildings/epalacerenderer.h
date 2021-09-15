#ifndef EPALACERENDERER_H
#define EPALACERENDERER_H

#include "epalace.h"
#include "ebuildingrenderer.h"

class ePalace1Renderer : public eBuildingRenderer {
public:
    ePalace1Renderer(const stdsptr<ePalace>& b);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getOverlays(const eTileSize) const;

    int spanW() const { return 4; }
    int spanH() const { return 4; }
private:
    const stdsptr<ePalace> mPalace;
};

class ePalace2Renderer : public eBuildingRenderer {
public:
    ePalace2Renderer(const stdsptr<ePalace>& b);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getOverlays(const eTileSize size) const;

    int spanW() const { return 4; }
    int spanH() const { return 4; }
private:
    const stdsptr<ePalace> mPalace;
};

#endif // EPALACERENDERER_H
