#ifndef ESPINBOX_H
#define ESPINBOX_H

#include "elabel.h"

class eSpinBox : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setRange(const int min, const int max);
    void setIncrement(const int i);

    void setValue(const int v);
    int value() const { return mValue; }

    eLabel* label() const { return mValueLabel; }
private:
    int mIncrement = 1;
    int mMinValue = 0;
    int mMaxValue = 100;
    int mValue = 0;

    eLabel* mValueLabel = nullptr;
};

#endif // ESPINBOX_H
