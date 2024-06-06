#ifndef ECHARACTERBASE_H
#define ECHARACTERBASE_H

#include "actions/echaracteractiontype.h"

#include "fileIO/estreams.h"

enum class eCharacterType {
    none,

    settler,
    homeless,

    boar,
    deer,
    wolf,

    shepherd,
    goatherd,

    sheep,
    goat,
    cattle1,
    cattle2,
    cattle3,
    bull,
    horse,

    grower,

    peddler,

    trailer,
    ox,
    marbleMiner,
    lumberjack,
    bronzeMiner,
    silverMiner,

    trader,
    donkey,

    artisan,

    hunter,
    butcher,

    gymnast,
    philosopher,
    actor,
    competitor,

    scholar,
    astronomer,
    inventor,
    curator,

    taxCollector,
    watchman,
    waterDistributor,
    fireFighter,

    disgruntled,
    sick,

    archer,

    rockThrower,
    hoplite,
    horseman,
    // put new soldiers below

    hoplitePoseidon,
    chariotPoseidon,
    archerPoseidon,

    amazon,
    aresWarrior,

    trojanHoplite,
    trojanSpearthrower,
    trojanHorseman,

    centaurHorseman,
    centaurArcher,

    persianHoplite,
    persianArcher,
    persianHorseman,

    oceanidHoplite,
    oceanidSpearthrower,

    egyptianHoplite,
    egyptianArcher,
    egyptianChariot,

    atlanteanHoplite,
    atlanteanArcher,
    atlanteanChariot,

    phoenicianHorseman,
    phoenicianArcher,

    mayanHoplite,
    mayanArcher,

    // put new soldiers above
    greekRockThrower,
    greekHoplite,
    greekHorseman,

    healer,

    cartTransporter,
    porter,

    urchinGatherer,
    fishingBoat,
    tradeBoat,

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
    zeus,

    calydonianBoar, // artemis, theseus
    cerberus, // hades, hercules
    chimera, // atlas, bellerophon
    cyclops, // zeus, odysseus
    dragon, // ares, jason
    echidna, //  -, bellerophon
    harpies, // -, atalanta
    hector, // aphrodite, achilles
    hydra, // athena, hercules
    kraken, // poseidon, perseus
    maenads, // dionysus, achilles
    medusa, // demeter, perseus
    minotaur, // hermes, theseus
    scylla, // apollo, odysseus
    sphinx, // hera, atalanta
    talos, // hephaestus, jason

    achilles, // hector, maenads
    atalanta, // harpies, sphinx
    bellerophon, // chimera, echidna
    hercules, // cerberus, hydra
    jason, // dragon, talos
    odysseus, // cyclops, scylla
    perseus, // medusa, kraken
    theseus // calydonianBoar, minotaur
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
    bool dead() const { return mHP <= 0 ||
                        mActionType == eCharacterActionType::die; }
    bool fighting() const;

    double speed() const { return mSpeed; }
    void setSpeed(const double s) { mSpeed = s; }

    int playerId() const { return mPlayerId; }
    void setPlayerId(const int i) { mPlayerId = i; }

    eCharacterActionType actionType() const { return mActionType; }
    void setActionType(const eCharacterActionType t);

    void setType(eCharacterType type) { mType = type; }
    eCharacterType type() const { return mType; }

    bool isSoldier() const;
    bool isGod() const;
    bool isHero() const;
    bool isMonster() const;
    bool isImmortal() const;

    virtual void read(eReadStream& src);
    virtual void write(eWriteStream& dst) const;
private:
    eCharacterType mType;
    eCharacterActionType mActionType{eCharacterActionType::none};

    int mPlayerId{1}; // 0 - neutral

    bool mBusy = false;

    double mHP = 100;
    double mAttack = 0;
    double mSpeed = 1;
};

#endif // ECHARACTERBASE_H
