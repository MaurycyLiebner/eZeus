#ifndef ECHARACTER_H
#define ECHARACTER_H

#include "engine/eorientation.h"
#include "engine/etile.h"
#include "actions/echaracteraction.h"
#include "etexture.h"

class eGameBoard;

class eCharacter {
public:
    eCharacter(eGameBoard& board);
    virtual ~eCharacter();

    virtual eTexture getTexture(const eTileSize size) const = 0;

    double x() const { return mX; }
    double y() const { return mY; }
    eTile* tile() const { return mTile; }
    int time() const { return mTime; }
    int textureTime() const { return time()/10; }
    eOrientation orientation() const { return mOrientation; }

    void setTile(eTile* const t);
    void setX(const double x) { mX = x; }
    void setY(const double y) { mY = y; };
    void incTime(const int by);
    void setOrientation(const eOrientation o);
    void setCharAction(eCharacterAction* const a);
private:
    eGameBoard& mBoard;
    eTile* mTile = nullptr;
    eOrientation mOrientation{eOrientation::top};
    double mX = 0;
    double mY = 0;

    int mTime = 0;

    eCharacterAction* mCharAction = nullptr;
};

#endif // ECHARACTER_H
