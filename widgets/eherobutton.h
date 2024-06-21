#ifndef EHEROBUTTON_H
#define EHEROBUTTON_H

#include "eframedbutton.h"

#include "characters/heroes/ehero.h"

class eGameBoard;

class eHeroButton : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    using eHeroAction = std::function<void(const eHeroType)>;
    void initialize(const eHeroAction& hact);

    eHeroType type() const { return mType; }
    void setType(const eHeroType type);
private:
    eHeroType mType;
};

#endif // EHEROBUTTON_H
