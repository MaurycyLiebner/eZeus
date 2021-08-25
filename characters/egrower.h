#ifndef EGROWER_H
#define EGROWER_H

#include "echaracter.h"

class eGrower : public eCharacter {
public:
    eGrower(eGameBoard& board);

    int olives() const { return mOlives; }
    int grapes() const { return mGrapes; }

    void incGrapes();
    void incOlives();

    eTexture getTexture(const eTileSize size) const;
private:
    int mOlives = 0;
    int mGrapes = 0;
};

#endif // EGROWER_H
