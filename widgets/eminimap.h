#ifndef EMINIMAP_H
#define EMINIMAP_H

#include "ewidget.h"

#include "engine/egameboard.h"

class eMiniMap : public eWidget {
public:
    using eWidget::eWidget;

    void setBoard(eGameBoard* const board);

    void setChangeAction(const eAction& act);

    void viewFraction(const double fx, const double fy);
    void viewedFraction(double& fx, double& fy);

    void viewTile(const int tileX, const int tileY);
    void viewedTile(int& tileX, int& tileY) const;

    void setViewBoxSize(const double fx, const double fy);
protected:
    bool mousePressEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);

    void paintEvent(ePainter& p);
private:
    void updateTexture();
    void viewRelPix(const int pixX, const int pixY);
    void viewAbsPix(const int px, const int py);

    void scheduleUpdate();

    int mTime = 0;

    int mMouseX = 0;
    int mMouseY = 0;

    int mCenterX = 0;
    int mCenterY = 0;

    double mViewBoxW = 0.2;
    double mViewBoxH = 0.2;

    int mTDim = 2;

    eGameBoard* mBoard = nullptr;

    bool mUpdateScheduled = false;
    std::shared_ptr<eTexture> mTexture;

    eAction mChangeAction;
};

#endif // EMINIMAP_H
