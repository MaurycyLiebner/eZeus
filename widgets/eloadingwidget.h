#ifndef ELOADINGWIDGET_H
#define ELOADINGWIDGET_H

#include "ewidget.h"
#include "eprogressbar.h"
#include "elabel.h"

class eLoadingWidget : public eWidget {
public:
    using eLoader = std::function<bool(std::string&)>;
    eLoadingWidget(const int size,
                   const eLoader& loader,
                   eMainWindow* const window);

    void initialize();
    void setDoneAction(const eAction& a);
protected:
    void paintEvent(ePainter& p);
private:
    const int mSize;
    const eLoader mLoader;

    eLabel* mLabel = nullptr;
    eProgressBar* mPB = nullptr;

    eAction mDoneAction;
};


#endif // ELOADINGWIDGET_H
