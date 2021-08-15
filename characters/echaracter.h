#ifndef ECHARACTER_H
#define ECHARACTER_H

#include "engine/eorientation.h"
#include "engine/etile.h"
#include "actions/echaracteraction.h"
#include "etexture.h"

class eGameBoard;

enum class eCharacterType {
    boar,

    lumberjack,
    bronzeMiner,
    silverMiner,

    hunter,

    gymnast,
    philosopher,

    taxCollector,
    watchman,
    waterDistributor,

    healer,

    demeter
};

class eCharacter {
public:
    eCharacter(eGameBoard& board, const eCharacterType type);
    virtual ~eCharacter();

    virtual eTexture getTexture(const eTileSize size) const = 0;
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

    bool defend(const int a);

    void setAttack(const int a);
    int attack() const { return mAttack; }
    void setHP(const int hp);
    int hp() const { return mHP; }
    bool dead() const { return mHP <= 0; }
    bool fighting() const;

    int playerId() const { return mPlayerId; }
    void setPlayerId(const int i) { mPlayerId = i; }

    eCharacterActionType actionType() const { return mActionType; }
    int actionStartTime() const { return mActionStartTime; }
    void setActionType(const eCharacterActionType t);

    eCharacterType type() const { return mType; }
private:
    eGameBoard& mBoard;
    eTile* mTile = nullptr;
    eCharacterType mType;
    eOrientation mOrientation{eOrientation::top};
    double mX = 0.5;
    double mY = 0.5;

    int mPlayerId{1}; // 0 - neutral

    int mTime = 0;

    int mHP = 1000;
    int mAttack = 1;

    eCharacterAction* mAction = nullptr;
    eCharacterActionType mActionType{eCharacterActionType::walk};
    int mActionStartTime{0};
};

#endif // ECHARACTER_H
