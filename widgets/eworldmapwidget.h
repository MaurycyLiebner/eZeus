#ifndef EWORLDMAPWIDGET_H
#define EWORLDMAPWIDGET_H

#include "elabel.h"

#include "engine/eworldboard.h"

class eWorldMapWidget : public eLabel {
public:
    eWorldMapWidget(eMainWindow* const window);

    void initialize();

    void setBoard(eGameBoard* const b);

    using eSelectCityAction = std::function<void(const stdsptr<eWorldCity>&)>;
    void setSelectCityAction(const eSelectCityAction& s);
protected:
    void paintEvent(ePainter& p);
    bool mousePressEvent(const eMouseEvent& e);
private:
    eGameBoard* mGameBoard = nullptr;
    eWorldBoard* mWorldBoard = nullptr;
    int mFrame = 0;

    std::map<std::string, stdsptr<eTexture>> mNames;

    eSelectCityAction mSelectCityAction;
};

#endif // EWORLDMAPWIDGET_H
