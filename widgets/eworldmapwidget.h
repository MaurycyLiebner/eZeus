#ifndef EWORLDMAPWIDGET_H
#define EWORLDMAPWIDGET_H

#include "elabel.h"

class eWorldBoard;

class eWorldMapWidget : public eLabel {
public:
    eWorldMapWidget(eMainWindow* const window);

    void initialize();

    void setBoard(eWorldBoard* const b);
protected:
    void paintEvent(ePainter& p);
private:
    eWorldBoard* mBoard = nullptr;
    int mFrame = 0;
};

#endif // EWORLDMAPWIDGET_H
