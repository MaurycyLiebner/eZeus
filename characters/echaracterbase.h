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
    oxHandler,
    marbleMiner,
    lumberjack,
    bronzeMiner,
    silverMiner,

    hunter,

    gymnast,
    philosopher,
    actor,

    taxCollector,
    watchman,
    waterDistributor,
    fireFighter,

    archer,

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

    void setAttack(const int a);
    int attack() const { return mAttack; }
    void setHP(const int hp);
    int hp() const { return mHP; }
    bool dead() const { return mHP <= 0; }
    bool fighting() const;
    bool defend(const int a);

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

    int mHP = 1000;
    int mAttack = 1;
};

#endif // ECHARACTERBASE_H
