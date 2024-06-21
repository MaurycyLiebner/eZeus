#ifndef EWORLDTRIBUTEWIDGET_H
#define EWORLDTRIBUTEWIDGET_H

#include "ewidget.h"

#include "elabel.h"
#include "engine/eworldcity.h"

class eWorldTributeWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();
    void setCity(const stdsptr<eWorldCity>& c);
private:
    eLabel* mTitleLabel = nullptr;
    eLabel* mTypeIcon = nullptr;
    eLabel* mTextLabel = nullptr;
    eLabel* mAlliesLabel = nullptr;
};

#endif // EWORLDTRIBUTEWIDGET_H
