#ifndef EHERO_H
#define EHERO_H

#include "characters/echaracter.h"

enum class eHeroType {
    achilles, // hector, maenads
    atalanta, // harpies, sphinx
    bellerophon, // chimera, echidna
    hercules, // cerberus, hydra
    jason, // dragon, talos
    odysseus, // cyclops, scylla
    perseus, // medusa, kraken
    theseus // calydonianBoar, minotaur
};

class eHero : public eCharacter {
public:
    eHero(eGameBoard& board, const eHeroType mt);

    static eHeroType sCharacterToHeroType(
            const eCharacterType type, bool* const valid = nullptr);
    static eCharacterType sHeroToCharacterType(
            const eHeroType type);
    static stdsptr<eHero> sCreateHero(
            const eHeroType type, eGameBoard& board);
    static std::string sHeroName(const eHeroType ht);
};

#endif // EHERO_H
