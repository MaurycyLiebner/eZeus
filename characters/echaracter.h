#ifndef ECHARACTER_H
#define ECHARACTER_H

#include "pointers/eobject.h"
#include "pointers/estdpointer.h"

#include "eoverlay.h"
#include "engine/eorientation.h"
#include "engine/etile.h"
#include "etexture.h"
#include "echaracterbase.h"
#include "engine/eprovide.h"

class eGameBoard;
class eCharacterAction;

class eCharacter : public eObject, public eCharacterBase {
public:
    eCharacter(eGameBoard& board, const eCharacterType type);
    virtual ~eCharacter();

    virtual std::shared_ptr<eTexture> getTexture(const eTileSize size) const = 0;
    virtual eOverlay getSecondaryTexture(const eTileSize size) const {
        (void)size;
        return eOverlay();
    }
    virtual bool canFight(eCharacter* const c);

    virtual void provideToBuilding(eBuilding* const b);

    void incTime(const int by);

    void fight(eCharacter* const c);
    void kill();
    void killWithCorpse();

    double x() const { return mX; }
    double y() const { return mY; }
    double absX() const;
    double absY() const;

    eTile* tile() const { return mTile; }
    int time() const { return mTime; }
    int textureTime() const { return time()/20; }
    eOrientation orientation() const { return mOrientation; }

    void changeTile(eTile* const t, const bool prepend = false);
    void setX(const double x) { mX = x; }
    void setY(const double y) { mY = y; };
    void setOrientation(const eOrientation o);

    void setAction(const stdsptr<eCharacterAction>& a);
    eCharacterAction* action() const { return mAction.get(); }

    virtual void setActionType(const eCharacterActionType t);
    int actionStartTime() const { return mActionStartTime; }

    bool hasSecondaryTexture() const { return mHasSecondaryTexture; }
    void setHasSecondaryTexture(const bool st);

    int provideCount() const { return mProvideCount; }
    void setProvide(const eProvide p, const int n);

    bool visible() const { return mVisible; }
    void setVisible(const bool v) { mVisible = v; }

    bool isSoldier() const;

    bool defend(const double a);
private:
    stdsptr<eCharacterAction> takeAction();

    bool mVisible = true;

    eProvide mProvide = eProvide::none;
    int mProvideCount = 0;

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
