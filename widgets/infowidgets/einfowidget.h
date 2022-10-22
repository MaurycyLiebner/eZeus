#ifndef EINFOWIDGET_H
#define EINFOWIDGET_H

#include "../eframedwidget.h"

class eLabel;
class eOkButton;

class eInfoWidget : public eFramedWidget {
public:
    eInfoWidget(eMainWindow* const window,
                const bool narrow, const bool shrt);

    void initialize(const std::string& title);

    void setCloseAction(const eAction& closeAction);

    eWidget* addCentralWidget();
    eWidget* addFramedWidget(const int height);
    eWidget* addRegularWidget(const int height);

    void addText(const std::string& text);
    void addInfoWidget(eWidget* const w);
    void addInfoWidget(eWidget* const w, const int height);

    int widgetWidth() const;

    eWidget* centralWidget() const;
private:
    const bool mNarrow;
    const bool mShort;

    std::vector<eWidget*> mWidgets;

    eLabel* mTitleLabel = nullptr;
    eWidget* mCentralWidget = nullptr;
    eOkButton* mOk = nullptr;
};

#endif // EINFOWIDGET_H
