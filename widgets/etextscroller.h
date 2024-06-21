#ifndef ETEXTSCROLLER_H
#define ETEXTSCROLLER_H

#include "ewidget.h"

class eLabel;
class eFramedWidget;
class eScrollWidgetComplete;

class eTextScroller : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setText(const std::string& text);
    void setTinyTextFontSize();
    void setSmallTextFontSize();
    void setTinyTextPadding();
private:
    eFramedWidget* mBg = nullptr;
    eLabel* mTextLabel = nullptr;
    eLabel* mScrollTextLabel = nullptr;
    eScrollWidgetComplete* mSW = nullptr;
};

#endif // ETEXTSCROLLER_H
