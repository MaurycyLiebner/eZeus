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
    void tileAtPix(const int pixX, const int pixY,
                   int& tileX, int& tileY) const;
    void pixAtTile(const int tileX, const int tileY,
                   int& pixX, int& pixY) const;

    void viewTile(const int tileX, const int tileY);
    void viewPix(const int pixX, const int pixY);

    int mCenterX = 0;
    int mCenterY = 0;

    eGameBoard* mBoard = nullptr;
};

#endif // EMINIMAP_H
