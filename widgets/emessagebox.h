#ifndef EMESSAGEBOX_H
#define EMESSAGEBOX_H

#include "eframedwidget.h"

#include "emessage.h"
#include "engine/edate.h"

class eWorldCity;
struct eEventData;

class eMessageBox : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const eEventData& ed,
                    const eAction& viewTile,
                    eMessage msg);

protected:
    bool mousePressEvent(const eMouseEvent& e);
};

#endif // EMESSAGEBOX_H
