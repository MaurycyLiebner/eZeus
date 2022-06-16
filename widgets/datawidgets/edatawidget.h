#ifndef EDATAWIDGET_H
#define EDATAWIDGET_H

#include "../ewidget.h"

class eViewModeButton;
class eFramedWidget;
class eGameWidget;

class eDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    virtual void initialize();

    void setGameWidget(eGameWidget* const gw);
protected:
    void addViewButton(eViewModeButton* const b);
    eFramedWidget* innerWidget() const { return mInnerWidget; }
private:
    eFramedWidget* mInnerWidget = nullptr;
    std::vector<eViewModeButton*> mButtons;
};

#endif // EDATAWIDGET_H
