#ifndef ESTADIUMRENDERER_H
#define ESTADIUMRENDERER_H

#include "estadium.h"
#include "ebuildingrenderer.h"

class eStadium1Renderer : public eBuildingRenderer {
public:
    eStadium1Renderer(const stdsptr<eStadium>& b);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getOverlays(const eTileSize size) const;

    int spanW() const { return 5; }
    int spanH() const { return 5; }
private:
    const stdsptr<eStadium> mStadium;
};

class eStadium2Renderer : public eBuildingRenderer {
public:
    eStadium2Renderer(const stdsptr<eStadium>& b);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getOverlays(const eTileSize size) const;

    int spanW() const { return 5; }
    int spanH() const { return 5; }
private:
    const stdsptr<eStadium> mStadium;
};

#endif // ESTADIUMRENDERER_H
