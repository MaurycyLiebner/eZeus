#ifndef ETABWIDGET_H
#define ETABWIDGET_H

#include "echeckablebutton.h"

class eTabWidget : public eWidget {
public:
    eTabWidget(eMainWindow* const window);
    void initialize();

    void addTab(const std::string& text,
                eWidget* const w);
private:
    std::vector<eCheckableButton*> mButtons;
    std::vector<eWidget*> mWidgets;
    eWidget* const mTabWidget;
};

#endif // ETABWIDGET_H
