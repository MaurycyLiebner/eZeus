#ifndef ECHARACTER_H
#define ECHARACTER_H

#include "pointers/estdselfref.h"
#include "pointers/estdpointer.h"

#include "eoverlay.h"
#include "engine/eorientation.h"
#include "engine/etile.h"
#include "etexture.h"
#include "echaracterbase.h"
#include "engine/eprovide.h"

class eGameBoard;
class eCharacterAction;

class eCharacter : public eStdSelfRef, public eCharacterBase {
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
    int textureTime() const { return time()/15; }
    eOrientation orientation() const { return mOrientation; }

    void changeTile(eTile* const t);
    void setX(const double x) { mX = x; }
    void setY(const double y) { mY = y; };
    void incTime(const int by);
    void setOrientation(const eOrientation o);

    void setAction(const stdsptr<eCharacterAction>& a);

    void setActionType(const eCharacterActionType t);
    int actionStartTime() const { return mActionStartTime; }

    eGameBoard& board() { return mBoard; }

    bool hasSecondaryTexture() const { return mHasSecondaryTexture; }
    void setHasSecondaryTexture(const bool st);

    int provideCount() const { return mProvideCount; }
    void setProvide(const eProvide p, const int n);
private:
    stdsptr<eCharacterAction> takeAction();

    eProvide mProvide = eProvide::none;
    int mProvideCount = 0;

    eGameBoard& mBoard;
    eTile* mTile = nullptr;
    eOrientation mOrientation{eOrientation::top};
    double mX = 0.5;
    double mY = 0.5;

    int mTime = 0;
    bool mHasSecondaryTexture = false;

    stdsptr<eCharacterAction> mAction;
    int mActionStartTime{0};
};

#endif // ECHARACTER_H
