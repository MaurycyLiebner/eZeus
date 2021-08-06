#ifndef EGAMEWIDGET_H
#define EGAMEWIDGET_H

#include "ewidget.h"
#include "etexturecollection.h"

#include "engine/etile.h"
#include "engine/egameboard.h"
#include "textures/eterraintextures.h"
#include "textures/edemetertextures.h"
#include "textures/ebuildingtextures.h"
#include "textures/echaractertextures.h"

#include "infowidgets/egyminfowidget.h"

class eTerrainEditMenu;
class eGameMenu;

class eGameWidget : public eWidget {
public:
    eGameWidget(eMainWindow* const window);
    ~eGameWidget();

    void initialize(const int w, const int h);

    void pixToId(const int pixX, const int pixY,
                 int& idX, int& idY) const;
protected:
    void paintEvent(ePainter& p);

    bool keyPressEvent(const eKeyPressEvent& e);
    bool mousePressEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
    bool mouseReleaseEvent(const eMouseEvent& e);
    bool mouseWheelEvent(const eMouseWheelEvent& e);
private:
    using eTileAction = std::function<void(eTile* const)>;

    void iterateOverTiles(const eTileAction& a);

    void setTileSize(const eTileSize size);

    void actionOnSelectedTiles(const eTileAction& apply);

    bool mRotate = false;

    int mSpeed = 1;

    int mWheel = 0;

    int mDX = 0;
    int mDY = 0;

    eTileSize mTileSize = eTileSize::s30;
    int mTileW = 58;
    int mTileH = 30;

    eGameBoard mBoard;

    eInfoWidget* mInfoWidget = nullptr;
    eTerrainEditMenu* mTem = nullptr;
    eGameMenu* mGm = nullptr;
};

#endif // EGAMEWIDGET_H
