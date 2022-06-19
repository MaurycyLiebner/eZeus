#ifndef EINFOWIDGET_H
#define EINFOWIDGET_H

#include "../eframedwidget.h"

class eOkButton;

class eInfoWidget : public eFramedWidget {
public:
    eInfoWidget(eMainWindow* const window);

    void initialize(const std::string& title);

    void setCloseAction(const eAction& closeAction);
protected:
    eWidget* addFramedWidget(const int height);
    eWidget* centralWidget() const;
private:
    eWidget* mCentralWidget = nullptr;
    eOkButton* mOk = nullptr;
};

#endif // EINFOWIDGET_H
