#ifndef EVIEWMODEBUTTON_H
#define EVIEWMODEBUTTON_H

#include "widgets/echeckablebutton.h"
#include "widgets/egamewidget.h"
#include "widgets/eviewmode.h"

class eViewModeButton : public eCheckableButton {
public:
    eViewModeButton(const std::string& text,
                    const eViewMode vm,
                    eMainWindow* const window);

    void setGameWidget(eGameWidget* const gw);
protected:
    void paintEvent(ePainter& p);
private:
    const eViewMode mVM;
    eGameWidget* mGW = nullptr;
};

#endif // EVIEWMODEBUTTON_H
