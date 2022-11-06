#ifndef EMESSAGEBOX_H
#define EMESSAGEBOX_H

#include "eframedwidget.h"

#include "emessage.h"
#include "engine/edate.h"

class eWorldCity;

class eMessageBox : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const eMessageEventType et,
                    const eAction& viewTile,
                    const eDate& date,
                    eMessage msg,
                    const std::string& name,
                    eWorldCity* const city,
                    const int bribe);
};

#endif // EMESSAGEBOX_H
