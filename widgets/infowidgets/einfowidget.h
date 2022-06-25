#ifndef EINFOWIDGET_H
#define EINFOWIDGET_H

#include "../eframedwidget.h"

class eOkButton;

class eInfoWidget : public eFramedWidget {
public:
    eInfoWidget(eMainWindow* const window,
                const bool narrow, const bool shrt);

    void initialize(const std::string& title);

    void setCloseAction(const eAction& closeAction);
protected:
    eWidget* addFramedWidget(const int height);
    eWidget* centralWidget() const;
private:
    const bool mNarrow;
    const bool mShort;

    eWidget* mCentralWidget = nullptr;
    eOkButton* mOk = nullptr;
};

#endif // EINFOWIDGET_H
