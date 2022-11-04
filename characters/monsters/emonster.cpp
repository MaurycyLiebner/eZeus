#include "emonster.h"

#include "characters/gods/egod.h"
#include "characters/heroes/ehero.h"

#include "ecalydonianboar.h"
#include "engine/egameboard.h"

eMonster::eMonster(eGameBoard& board, const eMonsterType mt) :
    eCharacter(board, sMonsterToCharacterType(mt)) {
    board.registerMonster(this);
}

eMonster::~eMonster() {
    auto& board = getBoard();
    board.unregisterMonster(this);
}

eMonsterType eMonster::sCharacterToMonsterType(const eCharacterType type,
                                               bool* const valid) {
    if(valid) *valid = true;
    switch(type) {
    case eCharacterType::calydonianBoar: return eMonsterType::calydonianBoar;
    case eCharacterType::cerberus: return eMonsterType::cerberus;
    case eCharacterType::chimera: return eMonsterType::chimera;
    case eCharacterType::cyclops: return eMonsterType::cyclops;
    case eCharacterType::dragon: return eMonsterType::dragon;
    case eCharacterType::echidna: return eMonsterType::echidna;
    case eCharacterType::harpies: return eMonsterType::harpies;
    case eCharacterType::hector: return eMonsterType::hector;
    case eCharacterType::hydra: return eMonsterType::hydra;
    case eCharacterType::kraken: return eMonsterType::kraken;
    case eCharacterType::maenads: return eMonsterType::maenads;
    case eCharacterType::medusa: return eMonsterType::medusa;
    case eCharacterType::minotaur: return eMonsterType::minotaur;
    case eCharacterType::scylla: return eMonsterType::scylla;
    case eCharacterType::sphinx: return eMonsterType::sphinx;
    case eCharacterType::talos: return eMonsterType::talos;
    default:
        if(valid) *valid = false;
        return eMonsterType::calydonianBoar;
    }
}

eCharacterType eMonster::sMonsterToCharacterType(const eMonsterType type) {
    switch(type) {
    case eMonsterType::calydonianBoar: return eCharacterType::calydonianBoar;
    case eMonsterType::cerberus: return eCharacterType::cerberus;
    case eMonsterType::chimera: return eCharacterType::chimera;
    case eMonsterType::cyclops: return eCharacterType::cyclops;
    case eMonsterType::dragon: return eCharacterType::dragon;
    case eMonsterType::echidna: return eCharacterType::echidna;
    case eMonsterType::harpies: return eCharacterType::harpies;
    case eMonsterType::hector: return eCharacterType::hector;
    case eMonsterType::hydra: return eCharacterType::hydra;
    case eMonsterType::kraken: return eCharacterType::kraken;
    case eMonsterType::maenads: return eCharacterType::maenads;
    case eMonsterType::medusa: return eCharacterType::medusa;
    case eMonsterType::minotaur: return eCharacterType::minotaur;
    case eMonsterType::scylla: return eCharacterType::scylla;
    case eMonsterType::sphinx: return eCharacterType::sphinx;
    case eMonsterType::talos: return eCharacterType::talos;
    default: return eCharacterType::calydonianBoar;
    }
}

stdsptr<eMonster> eMonster::sCreateMonster(const eMonsterType type, eGameBoard& board) {
    switch(type) {
    case eMonsterType::calydonianBoar:
        return e::make_shared<eCalydonianBoar>(board);
    case eMonsterType::cerberus:
        return e::make_shared<eCerberus>(board);
    case eMonsterType::chimera:
        return e::make_shared<eChimera>(board);
    case eMonsterType::cyclops:
        return e::make_shared<eCyclops>(board);
    case eMonsterType::dragon:
        return e::make_shared<eDragon>(board);
    case eMonsterType::echidna:
        return e::make_shared<eEchidna>(board);
    case eMonsterType::harpies:
        return e::make_shared<eHarpies>(board);
    case eMonsterType::hector:
        return e::make_shared<eHector>(board);
    case eMonsterType::hydra:
        return e::make_shared<eHydra>(board);
    case eMonsterType::kraken:
        return e::make_shared<eKraken>(board);
    case eMonsterType::maenads:
        return e::make_shared<eMaenads>(board);
    case eMonsterType::medusa:
        return e::make_shared<eMedusa>(board);
    case eMonsterType::minotaur:
        return e::make_shared<eMinotaur>(board);
    case eMonsterType::scylla:
        return e::make_shared<eScylla>(board);
    case eMonsterType::sphinx:
        return e::make_shared<eSphinx>(board);
    case eMonsterType::talos:
        return e::make_shared<eTalos>(board);
    }
}

eGodType eMonster::sMonsterSender(const eMonsterType type, bool* const valid) {
    if(valid) *valid = true;
    switch(type) {
    case eMonsterType::calydonianBoar: return eGodType::artemis;
    case eMonsterType::cerberus: return eGodType::hades;
    case eMonsterType::chimera: return eGodType::atlas;
    case eMonsterType::cyclops: return eGodType::zeus;
    case eMonsterType::dragon: return eGodType::ares;

    case eMonsterType::hector: return eGodType::aphrodite;
    case eMonsterType::hydra: return eGodType::athena;
    case eMonsterType::kraken: return eGodType::poseidon;
    case eMonsterType::maenads: return eGodType::dionysus;
    case eMonsterType::medusa: return eGodType::demeter;
    case eMonsterType::minotaur: return eGodType::hermes;
    case eMonsterType::scylla: return eGodType::apollo;
    case eMonsterType::sphinx: return eGodType::hera;
    case eMonsterType::talos: return eGodType::hephaestus;

    case eMonsterType::echidna:
    case eMonsterType::harpies:
        if(valid) *valid = false;
        return eGodType::artemis;
    }
}

eMonsterType eMonster::sGodsMinion(const eGodType type) {
    switch(type) {
    case eGodType::artemis: return eMonsterType::calydonianBoar;
    case eGodType::hades: return eMonsterType::cerberus;
    case eGodType::atlas: return eMonsterType::chimera;
    case eGodType::zeus: return eMonsterType::cyclops;
    case eGodType::ares: return eMonsterType::dragon;

    case eGodType::aphrodite: return eMonsterType::hector;
    case eGodType::athena: return eMonsterType::hydra;
    case eGodType::poseidon: return eMonsterType::kraken;
    case eGodType::dionysus: return eMonsterType::maenads;
    case eGodType::demeter: return eMonsterType::medusa;
    case eGodType::hermes: return eMonsterType::minotaur;
    case eGodType::apollo: return eMonsterType::scylla;
    case eGodType::hera: return eMonsterType::sphinx;
    case eGodType::hephaestus: return eMonsterType::talos;
    }
}

eHeroType eMonster::sSlayer(const eMonsterType type) {
    switch(type) {
    case eMonsterType::calydonianBoar: return eHeroType::theseus;
    case eMonsterType::cerberus: return eHeroType::hercules;
    case eMonsterType::chimera: return eHeroType::bellerophon;
    case eMonsterType::cyclops: return eHeroType::odysseus;
    case eMonsterType::dragon: return eHeroType::jason;
    case eMonsterType::echidna: return eHeroType::bellerophon;
    case eMonsterType::harpies: return eHeroType::atalanta;
    case eMonsterType::hector: return eHeroType::achilles;
    case eMonsterType::hydra: return eHeroType::hercules;
    case eMonsterType::kraken: return eHeroType::perseus;
    case eMonsterType::maenads: return eHeroType::achilles;
    case eMonsterType::medusa: return eHeroType::perseus;
    case eMonsterType::minotaur: return eHeroType::theseus;
    case eMonsterType::scylla: return eHeroType::odysseus;
    case eMonsterType::sphinx: return eHeroType::atalanta;
    case eMonsterType::talos: return eHeroType::jason;
    default: return eHeroType::jason;
    }
}
