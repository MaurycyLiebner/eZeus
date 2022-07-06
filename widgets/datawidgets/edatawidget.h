#ifndef EDATAWIDGET_H
#define EDATAWIDGET_H

#include "../ewidget.h"

class eViewModeButton;
class eFramedWidget;
class eGameWidget;
class eGameBoard;

class eDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    virtual void initialize();

    void setBoard(eGameBoard* const b);
    void setGameWidget(eGameWidget* const gw);
protected:
    void addViewButton(eViewModeButton* const b);
    eFramedWidget* innerWidget() const { return mInnerWidget; }

    eGameBoard* mBoard = nullptr;
private:
    eFramedWidget* mInnerWidget = nullptr;
    std::vector<eViewModeButton*> mButtons;
};

#endif // EDATAWIDGET_H
