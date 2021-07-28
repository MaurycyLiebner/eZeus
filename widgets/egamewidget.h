#ifndef EGAMEWIDGET_H
#define EGAMEWIDGET_H

#include "ewidget.h"
#include "etexturecollection.h"

#include "engine/egameeventloop.h"
#include "engine/eterraintextures.h"

class eTerrainEditMenu;

enum class eTileSize {
    s15, s30, s60
};

class eGameWidget : public eWidget {
public:
    eGameWidget(eMainWindow* const window);
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
    void setTileSize(const eTileSize size);

    using eTileAction = std::function<void(eTile* const)>;
    void actionOnSelectedTiles(const eTileAction& apply);

    void loadWaterToX(int i0, const std::string& pathBase,
                      std::vector<eTextureCollection>& result) const;

    int mDX = 0;
    int mDY = 0;

    eTileSize mTileSize = eTileSize::s30;
    int mTileW = 58;
    int mTileH = 30;

    eGameBoard mBoard;
    eTerrainTextures* mTerrainTextures = nullptr;
    std::vector<eTerrainTextures> mTerrainTexturesColl;

    std::thread mLoopThread;
    eGameEventLoop mLoop;

    eTerrainEditMenu* mTem = nullptr;
};

#endif // EGAMEWIDGET_H
