#ifndef ENUMLINEEDIT_H
#define ENUMLINEEDIT_H

#include "elineedit.h"

class eNumLineEdit : public eLineEdit {
public:
    eNumLineEdit(eMainWindow* const window);

    int value() const;
    int clampedValue() const;
    void setValue(const int value);
    void setRange(const int min, const int max);
    void clamp();

    bool keyPressEvent(const eKeyPressEvent& e);
private:
    int mMin = (-__INT_MAX__ - 1);
    int mMax = __INT_MAX__;
};

#endif // ENUMLINEEDIT_H
