#ifndef EDATEBUTTON_H
#define EDATEBUTTON_H

#include "eframedbutton.h"

#include "engine/edate.h"

class eDateButton : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    void initialize();

    using eDateChangeAction = std::function<void(const eDate&)>;
    void setDateChangeAction(const eDateChangeAction& a);

    void setDate(const eDate& d);
    const eDate& date() const { return mDate; }
private:
    eDateChangeAction mDateChangeAction;
    eDate mDate;
};

#endif // EDATEBUTTON_H
