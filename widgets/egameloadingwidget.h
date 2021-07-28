#ifndef EGAMELOADINGWIDGET_H
#define EGAMELOADINGWIDGET_H

#include "ewidget.h"

class eGameLoadingWidget : public eWidget {
public:
    eGameLoadingWidget(eMainWindow* const window);

    void initialize();

    void setDoneAction(const eAction& a);
private:
    eAction mDoneAction;
};

#endif // EGAMELOADINGWIDGET_H
