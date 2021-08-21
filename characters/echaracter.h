#ifndef ECHARACTER_H
#define ECHARACTER_H

#include "eoverlay.h"
#include "engine/eorientation.h"
#include "engine/etile.h"
#include "actions/echaracteraction.h"
#include "etexture.h"
#include "echaracterbase.h"

class eGameBoard;

class eCharacter : public eCharacterBase {
public:
    eCharacter(eGameBoard& board, const eCharacterType type);
    virtual ~eCharacter();

    virtual eTexture getTexture(const eTileSize size) const = 0;
    virtual eOverlay getSecondaryTexture(const eTileSize size) const {
        (void)size;
        return eOverlay();
    }
    virtual bool canFight(eCharacter* const c);

    void fight(eCharacter* const c);

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

    void setAction(eCharacterAction* const a);
    eCharacterAction* takeAction();
    eCharacterAction* action() const { return mAction; }

    void setActionType(const eCharacterActionType t);
    int actionStartTime() const { return mActionStartTime; }

    eGameBoard& board() { return mBoard; }

    bool hasSecondaryTexture() const { return mHasSecondaryTexture; }
    void setHasSecondaryTexture(const bool st);
private:
    eGameBoard& mBoard;
    eTile* mTile = nullptr;
    eOrientation mOrientation{eOrientation::top};
    double mX = 0.5;
    double mY = 0.5;

    int mTime = 0;
    bool mHasSecondaryTexture = false;

    eCharacterAction* mAction = nullptr;
    int mActionStartTime{0};
};

#endif // ECHARACTER_H
