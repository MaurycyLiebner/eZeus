#include "egod.h"

eGod::eGod(eGameBoard& board, const eGodType gt) :
    eCharacter(board, sGodToCharacterType(gt)),
    mType(gt) {

}

eGodType eGod::sCharacterToGodType(const eCharacterType type) {
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
    default: return eGodType::aphrodite;
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
