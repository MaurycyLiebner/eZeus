#ifndef EELITEHOUSINGRENDERER_H
#define EELITEHOUSINGRENDERER_H

#include "ebuildingrenderer.h"

class eEliteHousing;

enum class eEliteRendererType {
    left, bottom, top, right
};

class eEliteHousingRenderer : public eBuildingRenderer {
public:
    eEliteHousingRenderer(const eEliteRendererType type,
                          const stdsptr<eEliteHousing>& b);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getOverlays(const eTileSize size) const;

    int spanW() const { return 2; }
    int spanH() const { return 2; }

    bool isMain() const { return false; }
private:
    const eEliteRendererType mType;
    const stdsptr<eEliteHousing> mBuilding;
};

#endif // EELITEHOUSINGRENDERER_H
