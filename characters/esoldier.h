#ifndef ESOLDIER_H
#define ESOLDIER_H

#include "echaracter.h"

class eSoldier : public eCharacter {
public:
    using eCharacter::eCharacter;

    bool selected() const { return mSelected; }
    void setSelected(const bool s) { mSelected = s; }
private:
    bool mSelected = false;
};

#endif // ESOLDIER_H
