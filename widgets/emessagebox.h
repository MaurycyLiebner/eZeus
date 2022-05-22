#ifndef EMESSAGEBOX_H
#define EMESSAGEBOX_H

#include "eframedwidget.h"

#include "emessage.h"
#include "engine/edate.h"

class eMessageBox : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const eAction& viewTile,
                    const eDate& date,
                    eMessage msg,
                    const std::string& name);
};

#endif // EMESSAGEBOX_H
