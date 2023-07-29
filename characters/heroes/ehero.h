#ifndef EHERO_H
#define EHERO_H

#include "characters/echaracter.h"

#include "textures/egametextures.h"

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
    static bool sRangedHero(const eHeroType ht);

    using eTexPtr = eTextureCollection eDestructionTextures::*;
    static eTexPtr sHeroMissile(const eHeroType gt);

    static eCharacterType sHeroToCharacterType(
            const eHeroType type);
    static stdsptr<eHero> sCreateHero(
            const eHeroType type, eGameBoard& board);
    static std::string sHeroName(const eHeroType ht);
    static void sHeroStrings(std::vector<eHeroType>& heroes,
                             std::vector<std::string>& heroNames);
};

#endif // EHERO_H
