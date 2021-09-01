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
    SDL_Rect mViewRect;
    eGameBoard* mBoard = nullptr;
};

#endif // EMINIMAP_H
