#ifndef EWORLDMAPWIDGET_H
#define EWORLDMAPWIDGET_H

#include "elabel.h"

#include "engine/eworldboard.h"

class eWorldMapWidget : public eLabel {
public:
    eWorldMapWidget(eMainWindow* const window);

    void initialize();

    void setBoard(eWorldBoard* const b);

    using eSelectCityAction = std::function<void(const stdsptr<eWorldCity>&)>;
    void setSelectCityAction(const eSelectCityAction& s);
protected:
    void paintEvent(ePainter& p);
    bool mousePressEvent(const eMouseEvent& e);
private:
    eWorldBoard* mBoard = nullptr;
    int mFrame = 0;

    eSelectCityAction mSelectCityAction;
};

#endif // EWORLDMAPWIDGET_H
