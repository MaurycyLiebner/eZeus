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
    int mapDimension() const;

    void viewPix(const int pixX, const int pixY);
    void setCenterPix(const int px, const int py);

    int mMouseX = 0;
    int mMouseY = 0;

    int mCenterX = 0;
    int mCenterY = 0;

    eGameBoard* mBoard = nullptr;
};

#endif // EMINIMAP_H