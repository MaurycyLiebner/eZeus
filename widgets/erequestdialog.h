#ifndef EREQUESTDIALOG_H
#define EREQUESTDIALOG_H

#include "eframedwidget.h"

#include "engine/eworldcity.h"

class eRequestDialog : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eRequestFunction = std::function<void(eResourceType)>;
    void initialize(const stdsptr<eWorldCity>& c,
                    const eRequestFunction& func);
protected:
    bool keyPressEvent(const eKeyPressEvent& e);
    bool mousePressEvent(const eMouseEvent& e);
private:
    stdsptr<eWorldCity> mCity;
};

#endif // EREQUESTDIALOG_H
