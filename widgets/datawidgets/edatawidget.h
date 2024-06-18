#ifndef EDATAWIDGET_H
#define EDATAWIDGET_H

#include "../ewidget.h"

class eViewModeButton;
class eGameWidget;
class eGameBoard;
class eBasicButton;

class eDataWidget : public eWidget {
public:
    eDataWidget(eGameBoard& b, eMainWindow* const w);

    virtual void initialize();

    void setGameWidget(eGameWidget* const gw);
protected:
    virtual void openMoreInfoWiget() {}

    void addViewButton(eViewModeButton* const b);
    eWidget* innerWidget() const { return mInnerWidget; }
    eGameWidget* gameWidget() const { return mGW; }
    int spacing() const;
    void showMoreInfoButton();

    static int sCoverageToText(const int c);

    eGameBoard& mBoard;
private:
    eGameWidget* mGW = nullptr;
    eBasicButton* mMoreInfo = nullptr;
    eWidget* mInnerWidget = nullptr;
    std::vector<eViewModeButton*> mButtons;
};

#endif // EDATAWIDGET_H
