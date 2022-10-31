#include "egod.h"

#include "eathena.h"
#include "edemeter.h"
#include "edionysus.h"
#include "ehermes.h"

#include "elanguage.h"

eGod::eGod(eGameBoard& board, const eGodType gt) :
    eCharacter(board, sGodToCharacterType(gt)),
    mType(gt) {

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
}

eGod::eTexPtr eGod::sGodMissile(const eGodType gt) {
    switch(gt) {
    case eGodType::aphrodite:
        return &eDestructionTextures::fGodBlueMissile;
    case eGodType::apollo:
        return &eDestructionTextures::fGodOrangeArrow;
    case eGodType::ares:
        return &eDestructionTextures::fGodOrangeMissile;
    case eGodType::artemis:
        return &eDestructionTextures::fGodBlueArrow;
    case eGodType::athena:
        return &eDestructionTextures::fGodRedMissile;
    case eGodType::atlas:
        return &eDestructionTextures::fGodPinkMissile;
    case eGodType::demeter:
        return &eDestructionTextures::fGodGreenMissile;
    case eGodType::dionysus:
        return &eDestructionTextures::fGodPurpleMissile;
    case eGodType::hades:
        return &eDestructionTextures::fGodOrangeMissile;
    case eGodType::hephaestus:
        return &eDestructionTextures::fGodOrangeMissile;
    case eGodType::hera:
        return &eDestructionTextures::fGodRedMissile;
    case eGodType::hermes:
        return &eDestructionTextures::fGodBlueMissile;
    case eGodType::poseidon:
        return &eDestructionTextures::fGodBlueMissile;
    case eGodType::zeus:
        return &eDestructionTextures::fGodBlueMissile;
    }
    return nullptr;
}

eGodType eGod::sFightWinner(const eGodType g1, const eGodType g2) {
    switch(g1) {
    case eGodType::zeus: {
        if(g2 == eGodType::hera) return eGodType::hera;
        return eGodType::zeus;
    } break;
    case eGodType::aphrodite: {
        if(g2 == eGodType::ares) return eGodType::aphrodite;
        if(g2 == eGodType::hermes) return eGodType::aphrodite;
        if(g2 == eGodType::dionysus) return eGodType::aphrodite;
        if(g2 == eGodType::hephaestus) return eGodType::aphrodite;
    } break;
    default:
        break;
    }
    if(rand() % 2) return g1;
    else return g2;
}

int eGod::sGodAttackTime(const eGodType gt) {
    switch(gt) {
    case eGodType::apollo:
    case eGodType::hades:
        return 300;
    case eGodType::demeter:
        return 700;
    default:
        return 500;
    }
}

std::string eGod::sGodName(const eGodType gt) {
    switch(gt) {
    case eGodType::aphrodite:
        return eLanguage::text("aphrodite");
    case eGodType::apollo:
        return eLanguage::text("apollo");
    case eGodType::ares:
        return eLanguage::text("ares");
    case eGodType::artemis:
        return eLanguage::text("artemis");
    case eGodType::athena:
        return eLanguage::text("athena");
    case eGodType::atlas:
        return eLanguage::text("atlas");
    case eGodType::demeter:
        return eLanguage::text("demeter");
    case eGodType::dionysus:
        return eLanguage::text("dionysus");
    case eGodType::hades:
        return eLanguage::text("hades");
    case eGodType::hephaestus:
        return eLanguage::text("hephaestus");
    case eGodType::hera:
        return eLanguage::text("hera");
    case eGodType::hermes:
        return eLanguage::text("hermes");
    case eGodType::poseidon:
        return eLanguage::text("poseidon");
    case eGodType::zeus:
        return eLanguage::text("zeus");
    }
    return "";
}
