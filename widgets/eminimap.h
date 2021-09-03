#ifndef EMINIMAP_H
#define EMINIMAP_H

#include "ewidget.h"

#include "engine/egameboard.h"

class eMiniMap : public eWidget {
public:
    using eWidget::eWidget;

    void setBoard(eGameBoard* const board);
protected:
    bool mousePressEvent(const eMouseEvent& e);
    bool mouseMoveEvent(const eMouseEvent& e);

    void paintEvent(ePainter& p);
private:
    void updateTexture();
    int mapDimension() const;

    void viewTile(const int tileX, const int tileY);
    void viewRelPix(const int pixX, const int pixY);
    void viewAbsPix(const int px, const int py);

    void scheduleUpdate();

    int mTime = 0;

    int mMouseX = 0;
    int mMouseY = 0;

    int mCenterX = 0;
    int mCenterY = 0;

    eGameBoard* mBoard = nullptr;

    bool mUpdateScheduled = false;
    std::shared_ptr<eTexture> mTexture;
};

#endif // EMINIMAP_H
