#ifndef EDATEBUTTON_H
#define EDATEBUTTON_H

#include "eframedbutton.h"

#include "engine/edate.h"

class eDateButton : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    void initialize();

    void setDate(const eDate& d);
    const eDate& date() const { return mDate; }
private:
    eDate mDate;
};

#endif // EDATEBUTTON_H
