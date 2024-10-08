#ifndef EMINIMAP_H
#define EMINIMAP_H

#include "ewidget.h"

#include "engine/egameboard.h"

class eMiniMap : public eWidget {
public:
    using eWidget::eWidget;

    void renderTargetsReset() override;

    void setBoard(eGameBoard* const board);

    void setChangeAction(const eAction& act);

    void viewFraction(const double fx, const double fy);
    void viewedFraction(double& fx, double& fy);

    void viewTile(const int tileX, const int tileY);
    void viewedTile(int& tileX, int& tileY) const;

    void setViewBoxSize(const double fx, const double fy);

    void scheduleUpdate();
protected:
    bool mousePressEvent(const eMouseEvent& e) override;
    bool mouseMoveEvent(const eMouseEvent& e) override;

    void paintEvent(ePainter& p) override;
private:
    void updateTexture();
    void viewRelPix(const int pixX, const int pixY);
    void viewAbsPix(const int px, const int py);

    int mTime = 0;

    int mMouseX = 0;
    int mMouseY = 0;

    int mCenterX = 0;
    int mCenterY = 0;

    int mDrawX = 0;
    int mDrawY = 0;

    double mViewBoxW = 0.2;
    double mViewBoxH = 0.2;

    int mTDim = 2;

    eGameBoard* mBoard = nullptr;

    bool mUpdateScheduled = false;
    std::shared_ptr<eTexture> mTexture;

    eAction mChangeAction;
};

#endif // EMINIMAP_H
