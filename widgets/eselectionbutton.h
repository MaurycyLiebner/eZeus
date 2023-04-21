#ifndef ESELECTIONBUTTON_H
#define ESELECTIONBUTTON_H

#include "ewidget.h"

class eLabel;

class eSelectionButton : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const int value, const int id);

    int id() const { return mValue; }
    void setId(const int id);

    int value() const { return mValue; }
    void setValue(const int value) { mValue = value; }
private:
    int mId = -1;
    int mValue = -1;
    eLabel* mIdLabel = nullptr;
};

#endif // ESELECTIONBUTTON_H
