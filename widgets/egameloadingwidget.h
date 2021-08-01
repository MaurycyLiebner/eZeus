#ifndef EGAMELOADINGWIDGET_H
#define EGAMELOADINGWIDGET_H

#include "ewidget.h"
#include "textures/eterraintextures.h"
#include "textures/edemetertextures.h"
#include "textures/ebuildingtextures.h"
#include "textures/echaractertextures.h"
#include "eprogressbar.h"
#include "elabel.h"

class eGameLoadingWidget : public eWidget {
public:
    eGameLoadingWidget(eMainWindow* const window);

    void initialize();
    void setDoneAction(const eAction& a);
protected:
    void paintEvent(ePainter& p);
private:
    eLabel* mLabel = nullptr;
    eProgressBar* mPB = nullptr;

    eAction mDoneAction;
};

#endif // EGAMELOADINGWIDGET_H
