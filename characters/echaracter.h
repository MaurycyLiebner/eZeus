#ifndef ECHARACTER_H
#define ECHARACTER_H

#include "engine/eorientation.h"
#include "engine/etile.h"
#include "characters/echaracteraction.h"
#include "etexture.h"

class eCharacter {
public:
    eCharacter();

    virtual eTexture getTexture(const eTileSize size) const = 0;

    double x() const { return mX; }
    double y() const { return mY; }
    eTile* tile() const { return mTile; }
    int time() const { return mTime; }
    eOrientation orientation() const { return mOrientation; }

    void setTile(eTile* const t);
    void setX(const double x) { mX = x; }
    void setY(const double y) { mY = y; };
    void incTime();
    void setOrientation(const eOrientation o);
    void setCharAction(eCharacterAction* const a);
private:
    eTile* mTile = nullptr;
    eOrientation mOrientation{eOrientation::top};
    double mX = 0;
    double mY = 0;

    int mTime = 0;

    eCharacterAction* mCharAction = nullptr;
};

#endif // ECHARACTER_H
