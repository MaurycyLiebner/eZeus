#ifndef EGAMELOADINGWIDGET_H
#define EGAMELOADINGWIDGET_H

#include "ewidget.h"
#include "textures/eterraintextures.h"
#include "textures/edemetertextures.h"
#include "textures/ebuildingtextures.h"
#include "textures/echaractertextures.h"
#include "eprogressbar.h"
#include "elabel.h"

class eGameLoadingWidget : public eWidget {
public:
    eGameLoadingWidget(eMainWindow* const window);

    void initialize();
    void setDoneAction(const eAction& a);

    std::vector<eTerrainTextures>&& takeTerrainTextures();
    std::vector<eDemeterTextures>&& takeDemeterTextures();
    std::vector<eBuildingTextures>&& takeBuildingTextures();
    std::vector<eCharacterTextures>&& takeCharacterTextures();
protected:
    void paintEvent(ePainter& p);
private:
    eLabel* mLabel = nullptr;
    eProgressBar* mPB = nullptr;

    int mNextToLoad = 0;
    eAction mDoneAction;

    int mSize = 0;

    std::vector<eTerrainTextures> mTerrainTextures;
    std::vector<eDemeterTextures> mDemeterTextures;
    std::vector<eBuildingTextures> mBuildingTextures;
    std::vector<eCharacterTextures> mCharacterTextures;
};

#endif // EGAMELOADINGWIDGET_H
