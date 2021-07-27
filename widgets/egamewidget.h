#ifndef EGAMEWIDGET_H
#define EGAMEWIDGET_H

#include "ewidget.h"
#include "etexturecollection.h"

#include "engine/egameeventloop.h"

class eGameWidget : public eWidget {
public:
    eGameWidget(eMainWindow* const window);
    ~eGameWidget();

    void initialize(const int w, const int h);
protected:
    void paintEvent(ePainter& p);

    bool mousePressEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);
private:
    int mDX = 0;
    int mDY = 0;

    std::thread mLoopThread;
    eGameEventLoop mLoop;

    eTextureCollection mDryTerrainTexs;
    eTextureCollection mBeachTerrainTexs;
    eTextureCollection mBeachToDryTerrainTexs;
    eTextureCollection mRiverTerrainTexs;
    std::vector<eTextureCollection> mRiverToDryTerrainTexs;
    eTextureCollection mFertileTerrainTexs;
    eTextureCollection mFertileToDryTerrainTexs;
    std::vector<eTextureCollection> mDryToScrubTerrainTexs;
    eTextureCollection mScrubTerrainTexs;
    std::vector<eTextureCollection> mFertileToScrubTerrainTexs;
    std::vector<eTextureCollection> mForestToDryTerrainTexs;
    eTextureCollection mForestToScrubTerrainTexs;
    eTextureCollection mForestTerrainTexs;
};

#endif // EGAMEWIDGET_H
