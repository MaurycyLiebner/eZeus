#ifndef EMONSTER_H
#define EMONSTER_H

#include "characters/echaracter.h"

enum class eGodType;
enum class eHeroType;

enum class eMonsterType {
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
    talos // hephaestus, jason
};

class eMonster : public eCharacter {
public:
    eMonster(eGameBoard& board, const eMonsterType mt);
    ~eMonster();

    static eMonsterType sCharacterToMonsterType(
            const eCharacterType type, bool* const valid = nullptr);
    static eCharacterType sMonsterToCharacterType(
            const eMonsterType type);
    static int sMonsterAttackTime(const eMonsterType type);
    static stdsptr<eMonster> sCreateMonster(
            const eMonsterType type, eGameBoard& board);
    static eGodType sMonsterSender(const eMonsterType type,
                                   bool* const valid);
    static eMonsterType sGodsMinion(const eGodType type);
    static eHeroType sSlayer(const eMonsterType type);

    static std::string sMonsterName(const eMonsterType type);

    static void sMonsterStrings(std::vector<eMonsterType>& mnstrs,
                                std::vector<std::string>& monsterStrs,
                                const bool withGodsOnly = false,
                                const bool showGodNames = true);
};

#endif // EMONSTER_H
