#ifndef EWORLDMAPWIDGET_H
#define EWORLDMAPWIDGET_H

#include "elabel.h"

#include "engine/eworldboard.h"

class eWorldMapWidget : public eLabel {
public:
    eWorldMapWidget(eMainWindow* const window);

    using eColonySelection = std::vector<stdsptr<eWorldCity>>;
    void setSelectColonyMode(const bool scm, const eColonySelection& s);

    void setBoard(eGameBoard* const b);
    void setWorldBoard(eWorldBoard* const b);

    using eSelectCityAction = std::function<void(const stdsptr<eWorldCity>&)>;
    void setSelectCityAction(const eSelectCityAction& s);
    using eSetTextAction = std::function<void(const std::string&)>;
    void setSetTextAction(const eSetTextAction& s);

    void updateWidgets();

    void setMap(const eWorldMap map);
protected:
    void paintEvent(ePainter& p);
    bool mousePressEvent(const eMouseEvent& e);
private:
    void armyDrawXY(eWorldCity& c1, eWorldCity& c2,
                    const double frac, int& x, int& y);

    bool mSelectColonyMode = false;
    std::vector<stdsptr<eWorldCity>> mColonySelection;

    eGameBoard* mGameBoard = nullptr;
    eWorldBoard* mWorldBoard = nullptr;
    int mFrame = 0;

    std::map<std::string, stdsptr<eTexture>> mNames;

    eSelectCityAction mSelectCityAction;
    eSetTextAction mSetTextAction;
};

#endif // EWORLDMAPWIDGET_H
