#ifndef EGAMEWIDGET_H
#define EGAMEWIDGET_H

#include "ewidget.h"
#include "etexturecollection.h"

#include "engine/etile.h"
#include "engine/egameboard.h"
#include "engine/ethreadpool.h"

#include "textures/eterraintextures.h"
#include "textures/edemetertextures.h"
#include "textures/ebuildingtextures.h"
#include "textures/echaractertextures.h"

#include "buildings/epatrolbuilding.h"

#include "infowidgets/egyminfowidget.h"

#include "widgets/egamemenu.h"

class eTerrainEditMenu;

using eBuildingCreator = std::function<stdsptr<eBuilding>()>;

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

    using eSpecialRequirement = std::function<bool(eTile*)>;
    bool canBuild(const int tx, const int ty,
                  const int sw, const int sh,
                  const eSpecialRequirement& specReq = {});
    bool build(const int tx, const int ty,
               const int sw, const int sh,
               const eBuildingCreator& bc,
               const eSpecialRequirement& specReq = {});
    bool erase(eTile* const tile);
    std::vector<ePatrolGuide>::iterator
        findGuide(const int tx, const int ty);

    bool mRotate = false;

    int mTime{0};
    int mSpeed = 1;

    int mWheel = 0;

    int mDX = 0;
    int mDY = 0;

    eTileSize mTileSize = eTileSize::s30;
    int mTileW = 58;
    int mTileH = 30;

    eThreadPool mThreadPool;

    int mUpdateRect = 0;
    std::vector<SDL_Rect> mUpdateRects;
    eGameBoard mBoard;

    bool mDrawElevation = true;
    ePatrolBuilding* mPatrolBuilding = nullptr;

    eInfoWidget* mInfoWidget = nullptr;
    eTerrainEditMenu* mTem = nullptr;
    eGameMenu* mGm = nullptr;
};

#endif // EGAMEWIDGET_H
