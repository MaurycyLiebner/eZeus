#ifndef EGAMELOADINGWIDGET_H
#define EGAMELOADINGWIDGET_H

#include "ewidget.h"
#include "textures/eterraintextures.h"
#include "eprogressbar.h"
#include "elabel.h"

class eGameLoadingWidget : public eWidget {
public:
    eGameLoadingWidget(eMainWindow* const window);

    void initialize();
    void setDoneAction(const eAction& a);

    std::vector<eTerrainTextures>&& takeTerrainTextures();
protected:
    void paintEvent(ePainter& p);
private:
    eLabel* mLabel = nullptr;
    eProgressBar* mPB = nullptr;

    int mNextToLoad = 0;
    eAction mDoneAction;

    std::vector<eTerrainTextures> mTerrainTextures;
};

#endif // EGAMELOADINGWIDGET_H
