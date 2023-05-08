#ifndef EGODBUTTON_H
#define EGODBUTTON_H

#include "eframedbutton.h"

#include "characters/gods/egod.h"

class eGameBoard;

class eGodButton : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    using eGodAction = std::function<void(const eGodType)>;
    void initialize(const eGodAction& gact);

    eGodType type() const { return mType; }
    void setType(const eGodType type);
private:
    eGodType mType;
};

#endif // EGODBUTTON_H
