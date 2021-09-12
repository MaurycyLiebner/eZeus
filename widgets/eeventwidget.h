#ifndef EEVENTWIDGET_H
#define EEVENTWIDGET_H

#include "engine/egameboard.h"
#include "ewidget.h"
#include "ebutton.h"

class eEventButton : public eButton {
public:
    eEventButton(const eEvent e,
                 eMainWindow* const window);
};

class eEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void pushEvent(const eEvent e, eTile* const tile);
    void clear();

    using eViewTileHandler = std::function<void(eTile*)>;
    void setViewTileHandler(const eViewTileHandler& h);
private:
    eViewTileHandler mViewTileHandler;
    std::vector<eEventButton*> mButtons;
};

#endif // EEVENTWIDGET_H
