#ifndef ETRADEEDITWIDGET_H
#define ETRADEEDITWIDGET_H

#include "eframedwidget.h"
#include "engine/eworldcity.h"

class eTradeResourceButton;

class eTradeEditWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(std::vector<eResourceTrade>* const trade);
private:
    void updateVector();

    std::vector<eResourceTrade>* mTrade = nullptr;
    eWidget* mInnerWidget = nullptr;
    eWidget* mButtonsWidget = nullptr;
    std::vector<eTradeResourceButton*> mButtons;
};

#endif // ETRADEEDITWIDGET_H
