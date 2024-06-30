#include "egod.h"

#include "eathena.h"
#include "edemeter.h"
#include "edionysus.h"
#include "ehermes.h"

#include "elanguage.h"

#include "buildings/ebuilding.h"

eGod::eGod(eGameBoard& board, const eGodType gt) :
    eCharacter(board, sGodToCharacterType(gt)),
    mType(gt) {
    setAttack(0.5);
}

int sGodTextId(const eGodType type) {
    switch(type) {
    case eGodType::aphrodite:
        return 6;
    case eGodType::apollo:
        return 3;
    case eGodType::ares:
        return 5;
    case eGodType::artemis:
        return 4;
    case eGodType::athena:
        return 8;
    case eGodType::atlas:
        return 13;
    case eGodType::demeter:
        return 2;
    case eGodType::dionysus:
        return 10;
    case eGodType::hades:
        return 11;
    case eGodType::hephaestus:
        return 9;
    case eGodType::hera:
        return 12;
    case eGodType::hermes:
        return 7;
    case eGodType::poseidon:
        return 1;
    case eGodType::zeus:
    default:
        return 0;
    }
}

eGodType eGod::sCharacterToGodType(const eCharacterType type,
                                   bool* const valid) {
    if(valid) *valid = true;
    switch(type) {
    case eCharacterType::aphrodite: return eGodType::aphrodite;
    case eCharacterType::apollo: return eGodType::apollo;
    case eCharacterType::ares: return eGodType::ares;
    case eCharacterType::artemis: return eGodType::artemis;
    case eCharacterType::athena: return eGodType::athena;
    case eCharacterType::atlas: return eGodType::atlas;
    case eCharacterType::demeter: return eGodType::demeter;
    case eCharacterType::dionysus: return eGodType::dionysus;
    case eCharacterType::hades: return eGodType::hades;
    case eCharacterType::hephaestus: return eGodType::hephaestus;
    case eCharacterType::hera: return eGodType::hera;
    case eCharacterType::hermes: return eGodType::hermes;
    case eCharacterType::poseidon: return eGodType::poseidon;
    case eCharacterType::zeus: return eGodType::zeus;
    default:
        if(valid) *valid = false;
        return eGodType::aphrodite;
    }
}

eCharacterType eGod::sGodToCharacterType(const eGodType type) {
    switch(type) {
    case eGodType::aphrodite: return eCharacterType::aphrodite;
    case eGodType::apollo: return eCharacterType::apollo;
    case eGodType::ares: return eCharacterType::ares;
    case eGodType::artemis: return eCharacterType::artemis;
    case eGodType::athena: return eCharacterType::athena;
    case eGodType::atlas: return eCharacterType::atlas;
    case eGodType::demeter: return eCharacterType::demeter;
    case eGodType::dionysus: return eCharacterType::dionysus;
    case eGodType::hades: return eCharacterType::hades;
    case eGodType::hephaestus: return eCharacterType::hephaestus;
    case eGodType::hera: return eCharacterType::hera;
    case eGodType::hermes: return eCharacterType::hermes;
    case eGodType::poseidon: return eCharacterType::poseidon;
    case eGodType::zeus: return eCharacterType::zeus;
    default: return eCharacterType::aphrodite;
    }
}

stdsptr<eGod> eGod::sCreateGod(const eGodType type, eGameBoard& board) {
    switch(type) {
    case eGodType::aphrodite:
        return e::make_shared<eAphrodite>(board);
    case eGodType::apollo:
        return e::make_shared<eApollo>(board);
    case eGodType::ares:
        return e::make_shared<eAres>(board);
    case eGodType::artemis:
        return e::make_shared<eArtemis>(board);
    case eGodType::athena:
        return e::make_shared<eAthena>(board);
    case eGodType::atlas:
        return e::make_shared<eAtlas>(board);
    case eGodType::demeter:
        return e::make_shared<eDemeter>(board);
    case eGodType::dionysus:
        return e::make_shared<eDionysus>(board);
    case eGodType::hades:
        return e::make_shared<eHades>(board);
    case eGodType::hephaestus:
        return e::make_shared<eHephaestus>(board);
    case eGodType::hera:
        return e::make_shared<eHera>(board);
    case eGodType::hermes:
        return e::make_shared<eHermes>(board);
    case eGodType::poseidon:
        return e::make_shared<ePoseidon>(board);
    case eGodType::zeus:
        return e::make_shared<eZeus>(board);
    }
    return nullptr;
}

eGod::eTexPtr eGod::sGodMissile(const eGodType gt) {
    switch(gt) {
    case eGodType::aphrodite:
        eGameTextures::loadGodBlueMissile();
        return &eDestructionTextures::fGodBlueMissile;
    case eGodType::apollo:
        eGameTextures::loadGodOrangeArrow();
        return &eDestructionTextures::fGodOrangeArrow;
    case eGodType::ares:
        eGameTextures::loadGodOrangeMissile();
        return &eDestructionTextures::fGodOrangeMissile;
    case eGodType::artemis:
        eGameTextures::loadGodBlueArrow();
        return &eDestructionTextures::fGodBlueArrow;
    case eGodType::athena:
        eGameTextures::loadGodRedMissile();
        return &eDestructionTextures::fGodRedMissile;
    case eGodType::atlas:
        eGameTextures::loadGodPinkMissile();
        return &eDestructionTextures::fGodPinkMissile;
    case eGodType::demeter:
        eGameTextures::loadGodGreenMissile();
        return &eDestructionTextures::fGodGreenMissile;
    case eGodType::dionysus:
        eGameTextures::loadGodPurpleMissile();
        return &eDestructionTextures::fGodPurpleMissile;
    case eGodType::hades:
        eGameTextures::loadGodOrangeMissile();
        return &eDestructionTextures::fGodOrangeMissile;
    case eGodType::hephaestus:
        eGameTextures::loadGodOrangeMissile();
        return &eDestructionTextures::fGodOrangeMissile;
    case eGodType::hera:
        eGameTextures::loadGodRedMissile();
        return &eDestructionTextures::fGodRedMissile;
    case eGodType::hermes:
        eGameTextures::loadGodBlueMissile();
        return &eDestructionTextures::fGodBlueMissile;
    case eGodType::poseidon:
        eGameTextures::loadGodBlueMissile();
        return &eDestructionTextures::fGodBlueMissile;
    case eGodType::zeus:
        eGameTextures::loadGodBlueMissile();
        return &eDestructionTextures::fGodBlueMissile;
    }
    return nullptr;
}

std::map<std::pair<eGodType, eGodType>, eGodType> gFightWinner {
    {{eGodType::zeus, eGodType::zeus}, eGodType::zeus},
    {{eGodType::zeus, eGodType::poseidon}, eGodType::zeus},
    {{eGodType::zeus, eGodType::demeter}, eGodType::zeus},
    {{eGodType::zeus, eGodType::apollo}, eGodType::zeus},
    {{eGodType::zeus, eGodType::artemis}, eGodType::zeus},
    {{eGodType::zeus, eGodType::ares}, eGodType::zeus},
    {{eGodType::zeus, eGodType::aphrodite}, eGodType::zeus},
    {{eGodType::zeus, eGodType::hermes}, eGodType::zeus},
    {{eGodType::zeus, eGodType::athena}, eGodType::zeus},
    {{eGodType::zeus, eGodType::hephaestus}, eGodType::zeus},
    {{eGodType::zeus, eGodType::dionysus}, eGodType::zeus},
    {{eGodType::zeus, eGodType::hades}, eGodType::zeus},
    {{eGodType::zeus, eGodType::hera}, eGodType::hera},
    {{eGodType::zeus, eGodType::atlas}, eGodType::zeus},

    {{eGodType::poseidon, eGodType::zeus}, eGodType::zeus},
    {{eGodType::poseidon, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::demeter}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::apollo}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::artemis}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::ares}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::aphrodite}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::hermes}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::athena}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::hephaestus}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::dionysus}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::hades}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::hera}, eGodType::poseidon},
    {{eGodType::poseidon, eGodType::atlas}, eGodType::poseidon},

    {{eGodType::demeter, eGodType::zeus}, eGodType::zeus},
    {{eGodType::demeter, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::demeter, eGodType::demeter}, eGodType::demeter},
    {{eGodType::demeter, eGodType::apollo}, eGodType::demeter},
    {{eGodType::demeter, eGodType::artemis}, eGodType::demeter},
    {{eGodType::demeter, eGodType::ares}, eGodType::demeter},
    {{eGodType::demeter, eGodType::aphrodite}, eGodType::demeter},
    {{eGodType::demeter, eGodType::hermes}, eGodType::demeter},
    {{eGodType::demeter, eGodType::athena}, eGodType::demeter},
    {{eGodType::demeter, eGodType::hephaestus}, eGodType::demeter},
    {{eGodType::demeter, eGodType::dionysus}, eGodType::demeter},
    {{eGodType::demeter, eGodType::hades}, eGodType::hades},
    {{eGodType::demeter, eGodType::hera}, eGodType::hera},
    {{eGodType::demeter, eGodType::atlas}, eGodType::demeter},

    {{eGodType::apollo, eGodType::zeus}, eGodType::zeus},
    {{eGodType::apollo, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::apollo, eGodType::demeter}, eGodType::demeter},
    {{eGodType::apollo, eGodType::apollo}, eGodType::apollo},
    {{eGodType::apollo, eGodType::artemis}, eGodType::artemis},
    {{eGodType::apollo, eGodType::ares}, eGodType::apollo},
    {{eGodType::apollo, eGodType::aphrodite}, eGodType::apollo},
    {{eGodType::apollo, eGodType::hermes}, eGodType::apollo},
    {{eGodType::apollo, eGodType::athena}, eGodType::athena},
    {{eGodType::apollo, eGodType::hephaestus}, eGodType::apollo},
    {{eGodType::apollo, eGodType::dionysus}, eGodType::apollo},
    {{eGodType::apollo, eGodType::hades}, eGodType::hades},
    {{eGodType::apollo, eGodType::hera}, eGodType::hera},
    {{eGodType::apollo, eGodType::atlas}, eGodType::apollo},

    {{eGodType::artemis, eGodType::zeus}, eGodType::zeus},
    {{eGodType::artemis, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::artemis, eGodType::demeter}, eGodType::demeter},
    {{eGodType::artemis, eGodType::apollo}, eGodType::artemis},
    {{eGodType::artemis, eGodType::artemis}, eGodType::artemis},
    {{eGodType::artemis, eGodType::ares}, eGodType::artemis},
    {{eGodType::artemis, eGodType::aphrodite}, eGodType::artemis},
    {{eGodType::artemis, eGodType::hermes}, eGodType::artemis},
    {{eGodType::artemis, eGodType::athena}, eGodType::athena},
    {{eGodType::artemis, eGodType::hephaestus}, eGodType::artemis},
    {{eGodType::artemis, eGodType::dionysus}, eGodType::artemis},
    {{eGodType::artemis, eGodType::hades}, eGodType::hades},
    {{eGodType::artemis, eGodType::hera}, eGodType::hera},
    {{eGodType::artemis, eGodType::atlas}, eGodType::artemis},

    {{eGodType::ares, eGodType::zeus}, eGodType::zeus},
    {{eGodType::ares, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::ares, eGodType::demeter}, eGodType::demeter},
    {{eGodType::ares, eGodType::apollo}, eGodType::apollo},
    {{eGodType::ares, eGodType::artemis}, eGodType::artemis},
    {{eGodType::ares, eGodType::ares}, eGodType::ares},
    {{eGodType::ares, eGodType::aphrodite}, eGodType::aphrodite},
    {{eGodType::ares, eGodType::hermes}, eGodType::ares},
    {{eGodType::ares, eGodType::athena}, eGodType::athena},
    {{eGodType::ares, eGodType::hephaestus}, eGodType::ares},
    {{eGodType::ares, eGodType::dionysus}, eGodType::ares},
    {{eGodType::ares, eGodType::hades}, eGodType::hades},
    {{eGodType::ares, eGodType::hera}, eGodType::hera},
    {{eGodType::ares, eGodType::atlas}, eGodType::atlas},

    {{eGodType::aphrodite, eGodType::zeus}, eGodType::zeus},
    {{eGodType::aphrodite, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::aphrodite, eGodType::demeter}, eGodType::demeter},
    {{eGodType::aphrodite, eGodType::apollo}, eGodType::apollo},
    {{eGodType::aphrodite, eGodType::artemis}, eGodType::artemis},
    {{eGodType::aphrodite, eGodType::ares}, eGodType::aphrodite},
    {{eGodType::aphrodite, eGodType::aphrodite}, eGodType::aphrodite},
    {{eGodType::aphrodite, eGodType::hermes}, eGodType::aphrodite},
    {{eGodType::aphrodite, eGodType::athena}, eGodType::athena},
    {{eGodType::aphrodite, eGodType::hephaestus}, eGodType::aphrodite},
    {{eGodType::aphrodite, eGodType::dionysus}, eGodType::aphrodite},
    {{eGodType::aphrodite, eGodType::hades}, eGodType::hades},
    {{eGodType::aphrodite, eGodType::hera}, eGodType::hera},
    {{eGodType::aphrodite, eGodType::atlas}, eGodType::atlas},

    {{eGodType::hermes, eGodType::zeus}, eGodType::zeus},
    {{eGodType::hermes, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::hermes, eGodType::demeter}, eGodType::demeter},
    {{eGodType::hermes, eGodType::apollo}, eGodType::apollo},
    {{eGodType::hermes, eGodType::artemis}, eGodType::artemis},
    {{eGodType::hermes, eGodType::ares}, eGodType::ares},
    {{eGodType::hermes, eGodType::aphrodite}, eGodType::aphrodite},
    {{eGodType::hermes, eGodType::hermes}, eGodType::hermes},
    {{eGodType::hermes, eGodType::athena}, eGodType::athena},
    {{eGodType::hermes, eGodType::hephaestus}, eGodType::hephaestus},
    {{eGodType::hermes, eGodType::dionysus}, eGodType::hermes},
    {{eGodType::hermes, eGodType::hades}, eGodType::hades},
    {{eGodType::hermes, eGodType::hera}, eGodType::hera},
    {{eGodType::hermes, eGodType::atlas}, eGodType::atlas},

    {{eGodType::athena, eGodType::zeus}, eGodType::zeus},
    {{eGodType::athena, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::athena, eGodType::demeter}, eGodType::demeter},
    {{eGodType::athena, eGodType::apollo}, eGodType::athena},
    {{eGodType::athena, eGodType::artemis}, eGodType::athena},
    {{eGodType::athena, eGodType::ares}, eGodType::athena},
    {{eGodType::athena, eGodType::aphrodite}, eGodType::athena},
    {{eGodType::athena, eGodType::hermes}, eGodType::athena},
    {{eGodType::athena, eGodType::athena}, eGodType::athena},
    {{eGodType::athena, eGodType::hephaestus}, eGodType::athena},
    {{eGodType::athena, eGodType::dionysus}, eGodType::athena},
    {{eGodType::athena, eGodType::hades}, eGodType::hades},
    {{eGodType::athena, eGodType::hera}, eGodType::hera},
    {{eGodType::athena, eGodType::atlas}, eGodType::athena},

    {{eGodType::hephaestus, eGodType::zeus}, eGodType::zeus},
    {{eGodType::hephaestus, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::hephaestus, eGodType::demeter}, eGodType::demeter},
    {{eGodType::hephaestus, eGodType::apollo}, eGodType::apollo},
    {{eGodType::hephaestus, eGodType::artemis}, eGodType::artemis},
    {{eGodType::hephaestus, eGodType::ares}, eGodType::ares},
    {{eGodType::hephaestus, eGodType::aphrodite}, eGodType::aphrodite},
    {{eGodType::hephaestus, eGodType::hermes}, eGodType::hephaestus},
    {{eGodType::hephaestus, eGodType::athena}, eGodType::athena},
    {{eGodType::hephaestus, eGodType::hephaestus}, eGodType::hephaestus},
    {{eGodType::hephaestus, eGodType::dionysus}, eGodType::hephaestus},
    {{eGodType::hephaestus, eGodType::hades}, eGodType::hades},
    {{eGodType::hephaestus, eGodType::hera}, eGodType::hera},
    {{eGodType::hephaestus, eGodType::atlas}, eGodType::atlas},

    {{eGodType::dionysus, eGodType::zeus}, eGodType::zeus},
    {{eGodType::dionysus, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::dionysus, eGodType::demeter}, eGodType::demeter},
    {{eGodType::dionysus, eGodType::apollo}, eGodType::apollo},
    {{eGodType::dionysus, eGodType::artemis}, eGodType::artemis},
    {{eGodType::dionysus, eGodType::ares}, eGodType::ares},
    {{eGodType::dionysus, eGodType::aphrodite}, eGodType::aphrodite},
    {{eGodType::dionysus, eGodType::hermes}, eGodType::hermes},
    {{eGodType::dionysus, eGodType::athena}, eGodType::athena},
    {{eGodType::dionysus, eGodType::hephaestus}, eGodType::hephaestus},
    {{eGodType::dionysus, eGodType::dionysus}, eGodType::dionysus},
    {{eGodType::dionysus, eGodType::hades}, eGodType::hades},
    {{eGodType::dionysus, eGodType::hera}, eGodType::hera},
    {{eGodType::dionysus, eGodType::atlas}, eGodType::atlas},

    {{eGodType::hades, eGodType::zeus}, eGodType::zeus},
    {{eGodType::hades, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::hades, eGodType::demeter}, eGodType::hades},
    {{eGodType::hades, eGodType::apollo}, eGodType::hades},
    {{eGodType::hades, eGodType::artemis}, eGodType::hades},
    {{eGodType::hades, eGodType::ares}, eGodType::hades},
    {{eGodType::hades, eGodType::aphrodite}, eGodType::hades},
    {{eGodType::hades, eGodType::hermes}, eGodType::hades},
    {{eGodType::hades, eGodType::athena}, eGodType::hades},
    {{eGodType::hades, eGodType::hephaestus}, eGodType::hades},
    {{eGodType::hades, eGodType::dionysus}, eGodType::hades},
    {{eGodType::hades, eGodType::hades}, eGodType::hades},
    {{eGodType::hades, eGodType::hera}, eGodType::hades},
    {{eGodType::hades, eGodType::atlas}, eGodType::hades},

    {{eGodType::hera, eGodType::zeus}, eGodType::hera},
    {{eGodType::hera, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::hera, eGodType::demeter}, eGodType::hera},
    {{eGodType::hera, eGodType::apollo}, eGodType::hera},
    {{eGodType::hera, eGodType::artemis}, eGodType::hera},
    {{eGodType::hera, eGodType::ares}, eGodType::hera},
    {{eGodType::hera, eGodType::aphrodite}, eGodType::hera},
    {{eGodType::hera, eGodType::hermes}, eGodType::hera},
    {{eGodType::hera, eGodType::athena}, eGodType::hera},
    {{eGodType::hera, eGodType::hephaestus}, eGodType::hera},
    {{eGodType::hera, eGodType::dionysus}, eGodType::hera},
    {{eGodType::hera, eGodType::hades}, eGodType::hades},
    {{eGodType::hera, eGodType::hera}, eGodType::hera},
    {{eGodType::hera, eGodType::atlas}, eGodType::hera},

    {{eGodType::atlas, eGodType::zeus}, eGodType::zeus},
    {{eGodType::atlas, eGodType::poseidon}, eGodType::poseidon},
    {{eGodType::atlas, eGodType::demeter}, eGodType::demeter},
    {{eGodType::atlas, eGodType::apollo}, eGodType::apollo},
    {{eGodType::atlas, eGodType::artemis}, eGodType::artemis},
    {{eGodType::atlas, eGodType::ares}, eGodType::atlas},
    {{eGodType::atlas, eGodType::aphrodite}, eGodType::atlas},
    {{eGodType::atlas, eGodType::hermes}, eGodType::atlas},
    {{eGodType::atlas, eGodType::athena}, eGodType::athena},
    {{eGodType::atlas, eGodType::hephaestus}, eGodType::atlas},
    {{eGodType::atlas, eGodType::dionysus}, eGodType::atlas},
    {{eGodType::atlas, eGodType::hades}, eGodType::hades},
    {{eGodType::atlas, eGodType::hera}, eGodType::hera},
    {{eGodType::atlas, eGodType::atlas}, eGodType::atlas},
};

eGodType eGod::sFightWinner(const eGodType g1, const eGodType g2) {
    return gFightWinner[{g1, g2}];
}

std::string eGod::sFightResultString(const eGodType g1, const eGodType g2) {
    const auto w = sFightWinner(g1, g2);
    const auto l = g1 == w ? g2 : g1;
    const int wi = sGodTextId(w);
    const int li = sGodTextId(l);
    const int group = 332;
    const int string = 14*wi + li;
    return eLanguage::zeusText(group, string);
}

int sGodAttackSpriteLength(const eGodType gt) {
    switch(gt) {
    case eGodType::aphrodite: return eGodTextures::sAphroditeFBTime;
    case eGodType::apollo: return eGodTextures::sApolloFTime;
    case eGodType::ares: return eGodTextures::sAresFBTime;
    case eGodType::artemis: return eGodTextures::sArtemisFTime;
    case eGodType::athena: return eGodTextures::sAthenaFTime;
    case eGodType::atlas: return eGodTextures::sAtlasFTime;
    case eGodType::demeter: return eGodTextures::sDemeterFBTime;
    case eGodType::dionysus: return eGodTextures::sDionysusFBTime;
    case eGodType::hades: return eGodTextures::sHadesFBTime;
    case eGodType::hephaestus: return eGodTextures::sHephaestusFBTime;
    case eGodType::hera: return eGodTextures::sHeraFBTime;
    case eGodType::hermes: return eGodTextures::sHermesFBTime;
    case eGodType::poseidon: return eGodTextures::sPoseidonFBTime;
    case eGodType::zeus: return eGodTextures::sZeusFTime;
    }
    return 0;
}

int eGod::sGodAttackTime(const eGodType gt) {
    const int sl = sGodAttackSpriteLength(gt);
    return sl*eCharacter::sTextureTimeDivisor;
}

int sGodBlessSpriteLength(const eGodType gt) {
    switch(gt) {
    case eGodType::aphrodite: return eGodTextures::sAphroditeFBTime;
    case eGodType::apollo: return eGodTextures::sApolloBTime;
    case eGodType::ares: return eGodTextures::sAresFBTime;
    case eGodType::artemis: return eGodTextures::sArtemisBTime;
    case eGodType::athena: return eGodTextures::sAthenaBTime;
    case eGodType::atlas: return eGodTextures::sAtlasBTime;
    case eGodType::demeter: return eGodTextures::sDemeterFBTime;
    case eGodType::dionysus: return eGodTextures::sDionysusFBTime;
    case eGodType::hades: return eGodTextures::sHadesFBTime;
    case eGodType::hephaestus: return eGodTextures::sHephaestusFBTime;
    case eGodType::hera: return eGodTextures::sHeraFBTime;
    case eGodType::hermes: return eGodTextures::sHermesFBTime;
    case eGodType::poseidon: return eGodTextures::sPoseidonFBTime;
    case eGodType::zeus: return eGodTextures::sZeusBTime;
    }
    return 0;
}

int eGod::sGodBlessTime(const eGodType gt) {
    const int sl = sGodBlessSpriteLength(gt);
    return sl*eCharacter::sTextureTimeDivisor;
}

int sGodAppearSpriteLength(const eGodType gt) {
    switch(gt) {
    case eGodType::aphrodite: return eGodTextures::sAphroditeDTime;
    case eGodType::apollo: return eGodTextures::sApolloDTime;
    case eGodType::ares: return eGodTextures::sAresDTime;
    case eGodType::artemis: return eGodTextures::sArtemisDTime;
    case eGodType::athena: return eGodTextures::sAthenaDTime;
    case eGodType::atlas: return eGodTextures::sAtlasDTime;
    case eGodType::demeter: return eGodTextures::sDemeterDTime;
    case eGodType::dionysus: return eGodTextures::sDionysusATime;
    case eGodType::hades: return eGodTextures::sHadesDTime;
    case eGodType::hephaestus: return eGodTextures::sHephaestusDTime;
    case eGodType::hera: return eGodTextures::sHeraDTime;
    case eGodType::hermes: return 0;
    case eGodType::poseidon: return eGodTextures::sPoseidonDTime;
    case eGodType::zeus: return eGodTextures::sZeusDTime;
    }
    return 0;
}

int eGod::sGodAppearTime(const eGodType gt) {
    const int sl = sGodAppearSpriteLength(gt);
    return sl*eCharacter::sTextureTimeDivisor;
}

bool eGod::sTarget(const eGodType gt, const eBuildingType bt) {
    switch(gt) {
    case eGodType::aphrodite:
        return bt == eBuildingType::commonHouse ||
               bt == eBuildingType::fountain ||
               bt == eBuildingType::eliteHousing;
    case eGodType::apollo:
        return bt == eBuildingType::podium ||
               bt == eBuildingType::college ||
               bt == eBuildingType::dramaSchool ||
               bt == eBuildingType::theater ||
               bt == eBuildingType::stadium ||
               bt == eBuildingType::gymnasium ||
               bt == eBuildingType::bibliotheke ||
               bt == eBuildingType::inventorsWorkshop ||
               bt == eBuildingType::laboratory ||
               bt == eBuildingType::university ||
               bt == eBuildingType::observatory ||
               bt == eBuildingType::museum;
    case eGodType::ares:
        return true;
    case eGodType::artemis:
        return bt == eBuildingType::huntingLodge ||
               bt == eBuildingType::granary;
    case eGodType::athena:
        return bt == eBuildingType::growersLodge ||
               bt == eBuildingType::oliveTree ||
               bt == eBuildingType::olivePress ||
               bt == eBuildingType::oilVendor;
    case eGodType::atlas:
        return bt == eBuildingType::masonryShop ||
               bt == eBuildingType::artisansGuild ||
               bt == eBuildingType::timberMill ||
               bt == eBuildingType::sculptureStudio;
    case eGodType::demeter:
        return bt == eBuildingType::wheatFarm ||
               bt == eBuildingType::onionsFarm ||
               bt == eBuildingType::carrotsFarm ||
               bt == eBuildingType::cardingShed ||
               bt == eBuildingType::dairy ||
               bt == eBuildingType::corral ||
               bt == eBuildingType::growersLodge ||
               bt == eBuildingType::orangeTendersLodge ||
               bt == eBuildingType::foodVendor ||
               bt == eBuildingType::granary;
    case eGodType::dionysus:
        return bt == eBuildingType::growersLodge ||
               bt == eBuildingType::vine ||
               bt == eBuildingType::winery ||
               bt == eBuildingType::wineVendor;
    case eGodType::hades:
        return bt == eBuildingType::foundry ||
               bt == eBuildingType::mint;
    case eGodType::hephaestus:
        return bt == eBuildingType::foundry ||
               bt == eBuildingType::mint ||
               bt == eBuildingType::armory ||
               bt == eBuildingType::sculptureStudio;
    case eGodType::hera:
        return bt == eBuildingType::foodVendor ||
               bt == eBuildingType::fleeceVendor ||
               bt == eBuildingType::oilVendor ||
               bt == eBuildingType::wineVendor ||
               bt == eBuildingType::armsVendor ||
               bt == eBuildingType::horseTrainer ||
               bt == eBuildingType::chariotFactory ||
               bt == eBuildingType::orangeTendersLodge ||
               bt == eBuildingType::orangeTree;
    case eGodType::hermes:
        return bt == eBuildingType::tradePost ||
               bt == eBuildingType::pier;
    case eGodType::poseidon:
        return bt == eBuildingType::urchinQuay ||
               bt == eBuildingType::fishery ||
               bt == eBuildingType::pier ||
               bt == eBuildingType::triremeWharf;
    case eGodType::zeus:
        return true;
    }
    return false;
}

std::string eGod::sGodName(const eGodType gt) {
    const int group = 157;
    const int string = sGodTextId(gt);
    return eLanguage::zeusText(group, string);
}

void eGod::sGodStrings(std::vector<eGodType>& gods,
                       std::vector<std::string>& godNames) {
    gods.push_back(eGodType::aphrodite);
    gods.push_back(eGodType::apollo);
    gods.push_back(eGodType::ares);
    gods.push_back(eGodType::artemis);
    gods.push_back(eGodType::athena);
    gods.push_back(eGodType::atlas);
    gods.push_back(eGodType::demeter);
    gods.push_back(eGodType::dionysus);
    gods.push_back(eGodType::hades);
    gods.push_back(eGodType::hephaestus);
    gods.push_back(eGodType::hera);
    gods.push_back(eGodType::hermes);
    gods.push_back(eGodType::poseidon);
    gods.push_back(eGodType::zeus);
    for(const auto g : gods) {
        godNames.push_back(sGodName(g));
    }
}

void eGod::read(eReadStream& src) {
    eCharacter::read(src);
    src >> mAttitude;
}

void eGod::write(eWriteStream& dst) const {
    eCharacter::write(dst);
    dst << mAttitude;
}
