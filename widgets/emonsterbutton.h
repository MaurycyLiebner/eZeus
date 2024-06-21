#ifndef EMONSTERBUTTON_H
#define EMONSTERBUTTON_H

#include "eframedbutton.h"

#include "characters/monsters/emonster.h"

class eGameBoard;

class eMonsterButton : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    using eMonsterAction = std::function<void(const eMonsterType)>;
    void initialize(const eMonsterAction& mact,
                    const bool withGodsOnly = false,
                    const bool showGodNames = true);

    eMonsterType type() const { return mType; }
    void setType(const eMonsterType type);
private:
    eMonsterType mType;
};

#endif // EMONSTERBUTTON_H
