#ifndef EGAMEWIDGET_H
#define EGAMEWIDGET_H

#include "ewidget.h"
#include "etexturecollection.h"

#include "engine/egameeventloop.h"

class eTerrainEditMenu;

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
private:
    using eTileAction = std::function<void(eTile* const)>;
    void actionOnSelectedTiles(const eTileAction& apply);

    void loadWaterToX(int i0, const std::string& pathBase,
                      std::vector<eTextureCollection>& result) const;

    int mDX = 0;
    int mDY = 0;

//    const int mTileW = 58;
//    const int mTileH = 30;
    const int mTileW = 116;
    const int mTileH = 60;

    eGameBoard mBoard;

    std::thread mLoopThread;
    eGameEventLoop mLoop;

    eTextureCollection mDryTerrainTexs;
    eTextureCollection mBeachTerrainTexs;
    eTextureCollection mBeachToDryTerrainTexs;
    eTextureCollection mWaterTerrainTexs;
    std::vector<eTextureCollection> mWaterToDryTerrainTexs;
    eTextureCollection mFertileTerrainTexs;
    eTextureCollection mFertileToDryTerrainTexs;
    std::vector<eTextureCollection> mDryToScrubTerrainTexs;
    eTextureCollection mScrubTerrainTexs;
    std::vector<eTextureCollection> mFertileToScrubTerrainTexs;
    std::vector<eTextureCollection> mForestToDryTerrainTexs;
    eTextureCollection mForestToScrubTerrainTexs;
    eTextureCollection mForestTerrainTexs;
    std::vector<eTextureCollection> mWaterToBeachTerrainTexs;
    eTexture mSelectedTex;
    eTextureCollection mWaterToBeachToDryTerrainTexs;

    eTerrainEditMenu* mTem = nullptr;
};

#endif // EGAMEWIDGET_H
