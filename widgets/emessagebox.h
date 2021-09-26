#ifndef EMESSAGEBOX_H
#define EMESSAGEBOX_H

#include "eframedwidget.h"

#include "emessage.h"

class eMessageBox : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const std::shared_ptr<eMessage>& msg,
                    const std::string& name);
};

#endif // EMESSAGEBOX_H
