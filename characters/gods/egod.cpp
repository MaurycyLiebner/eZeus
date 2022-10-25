#include "egod.h"

#include "eathena.h"
#include "edemeter.h"
#include "edionysus.h"
#include "ehermes.h"

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
