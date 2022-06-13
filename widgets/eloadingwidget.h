#ifndef ELOADINGWIDGET_H
#define ELOADINGWIDGET_H

#include "ewidget.h"
#include "eprogressbar.h"
#include "eframedlabel.h"
#include "elabel.h"

class eLoadingWidget : public eWidget {
public:
    using eLoader = std::function<bool(std::string&)>;
    eLoadingWidget(const int size,
                   const eLoader& loader,
                   eMainWindow* const window,
                   const bool useTextures = true);

    void initialize();
    void setDoneAction(const eAction& a);

    void setLoadImage(const int id);
protected:
    void paintEvent(ePainter& p);
private:
    const bool mUseTextures;
    const int mSize;
    const eLoader mLoader;

    eLabel* mImageLabel = nullptr;
    eWidget* mLabelW = nullptr;
    eLabelBase* mLabel = nullptr;
    eProgressBar* mPB = nullptr;

    eAction mDoneAction;
};


#endif // ELOADINGWIDGET_H
