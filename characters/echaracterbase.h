#ifndef ECHARACTERBASE_H
#define ECHARACTERBASE_H

#include "actions/echaracteractiontype.h"

enum class eCharacterType {
    none,

    settler,

    boar,
    deer,
    wolf,

    shepherd,
    goatherd,

    sheep,
    goat,
    cattle,

    grower,

    foodVendor,
    fleeceVendor,
    oilVendor,
    wineVendor,
    armsVendor,
    horseTrainer,

    trailer,
    ox,
    marbleMiner,
    lumberjack,
    bronzeMiner,
    silverMiner,

    artisan,

    hunter,

    gymnast,
    philosopher,
    actor,

    taxCollector,
    watchman,
    waterDistributor,
    fireFighter,

    archer,

    rockThrower,
    hoplite,
    horseman,

    healer,

    cartTransporter,

    aphrodite,
    apollo,
    ares,
    artemis,
    athena,
    atlas,
    demeter,
    dionysus,
    hades,
    hephaestus,
    hera,
    hermes,
    poseidon,
    zeus
};

class eCharacterBase {
public:
    eCharacterBase(const eCharacterType type);

    bool busy() const { return mBusy; }
    void setBusy(const bool b) { mBusy = b; }

    void setAttack(const double a);
    double attack() const { return mAttack; }
    void setHP(const double hp);
    double hp() const { return mHP; }
    bool dead() const { return mHP <= 0; }
    bool fighting() const;
    bool defend(const double a);

    double speed() const { return mSpeed; }
    void setSpeed(const double s) { mSpeed = s; }

    int playerId() const { return mPlayerId; }
    void setPlayerId(const int i) { mPlayerId = i; }

    eCharacterActionType actionType() const { return mActionType; }
    void setActionType(const eCharacterActionType t);

    void setType(eCharacterType type) { mType = type; }
    eCharacterType type() const { return mType; }
private:
    eCharacterType mType;
    eCharacterActionType mActionType{eCharacterActionType::none};

    int mPlayerId{1}; // 0 - neutral

    bool mBusy = false;

    double mHP = 1000;
    double mAttack = 1;
    double mSpeed = 1;
};

#endif // ECHARACTERBASE_H
