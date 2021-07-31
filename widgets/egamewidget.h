#ifndef EGAMEWIDGET_H
#define EGAMEWIDGET_H

#include "ewidget.h"
#include "etexturecollection.h"

#include "engine/etile.h"
#include "engine/egameboard.h"
#include "textures/eterraintextures.h"
#include "textures/edemetertextures.h"
#include "textures/ebuildingtextures.h"

#include "infowidgets/egyminfowidget.h"

class eTerrainEditMenu;

class eGameWidget : public eWidget {
public:
    eGameWidget(std::vector<eTerrainTextures>&& textures,
                std::vector<eDemeterTextures>&& demeterTextures,
                std::vector<eBuildingTextures>&& buildingTextures,
                eMainWindow* const window);
    ~eGameWidget();

    void initialize(const int w, const int h);

    void pixToId(const int pixX, const int pixY,
                 int& idX, int& idY) const;
protected:
    void paintEvent(ePainter& p);

    bool mousePressEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
    bool mouseReleaseEvent(const eMouseEvent& e);
    bool mouseWheelEvent(const eMouseWheelEvent& e);
private:
    using eTileAction = std::function<void(eTile* const)>;

    void iterateOverTiles(const eTileAction& a);

    void setTileSize(const eTileSize size);

    void actionOnSelectedTiles(const eTileAction& apply);

    void loadWaterToX(int i0, const std::string& pathBase,
                      std::vector<eTextureCollection>& result) const;

    int mWheel = 0;

    int mDX = 0;
    int mDY = 0;

    eTileSize mTileSize = eTileSize::s30;
    int mTileW = 58;
    int mTileH = 30;

    eGameBoard mBoard;
    eTerrainTextures* mTerrainTextures = nullptr;
    std::vector<eTerrainTextures> mTerrainTexturesColl;
    std::vector<eDemeterTextures> mDemeterTextures;
    std::vector<eBuildingTextures> mBuildingTextures;

    eInfoWidget* mInfoWidget = nullptr;
    eTerrainEditMenu* mTem = nullptr;
};

#endif // EGAMEWIDGET_H
