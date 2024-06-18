#include "emonster.h"

#include "characters/gods/egod.h"
#include "characters/heroes/ehero.h"

#include "ecalydonianboar.h"
#include "engine/egameboard.h"

#include "elanguage.h"

eMonster::eMonster(eGameBoard& board, const eMonsterType mt) :
    eCharacter(board, sMonsterToCharacterType(mt)) {
    setAttack(0.5);
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
    case eCharacterType::satyr: return eMonsterType::satyr;
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
    case eMonsterType::satyr: return eCharacterType::satyr;
    default: return eCharacterType::calydonianBoar;
    }
}

int eMonster::sMonsterAttackTime(const eMonsterType type) {
    (void)type;
    return 500;
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
    case eMonsterType::satyr:
        return e::make_shared<eSatyr>(board);
    }
    return nullptr;
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
    case eMonsterType::satyr: return eGodType::dionysus;

    case eMonsterType::echidna:
    case eMonsterType::harpies:
        if(valid) *valid = false;
        return eGodType::artemis;
    }
    return eGodType::athena;
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
    return eMonsterType::talos;
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

std::string eMonster::sMonsterName(const eMonsterType type) {
    const int group = 190;
    int string = -1;
    switch(type) {
    case eMonsterType::calydonianBoar:
        string = 6;
        break;
    case eMonsterType::cerberus:
        string = 2;
        break;
    case eMonsterType::chimera:
        string = 13;
        break;
    case eMonsterType::cyclops:
        string = 3;
        break;
    case eMonsterType::dragon:
        string = 7;
        break;
    case eMonsterType::echidna:
        string = 15;
        break;
    case eMonsterType::harpies:
        string = 14;
        break;
    case eMonsterType::hector:
        string = 9;
        break;
    case eMonsterType::hydra:
        string = 0;
        break;
    case eMonsterType::kraken:
        string = 1;
        break;
    case eMonsterType::maenads:
        string = 11;
        break;
    case eMonsterType::medusa:
        string = 5;
        break;
    case eMonsterType::minotaur:
        string = 4;
        break;
    case eMonsterType::scylla:
        string = 10;
        break;
    case eMonsterType::sphinx:
        string = 12;
        break;
    case eMonsterType::talos:
        string = 8;
        break;
    case eMonsterType::satyr:
        string = 17;
        break;
    }
    return eLanguage::zeusText(group, string);
}

void eMonster::sMonsterStrings(
        std::vector<eMonsterType>& mnstrs,
        std::vector<std::string>& monsterStrs,
        const bool withGodsOnly,
        const bool showGodNames) {
    const int iMin = static_cast<int>(eMonsterType::calydonianBoar);
    const int iMax = static_cast<int>(eMonsterType::talos);
    std::vector<eMonsterType> allMonsters;
    for(int i = iMin; i <= iMax; i++) {
        const auto mi = static_cast<eMonsterType>(i);
        allMonsters.push_back(mi);
    }

    const std::vector<std::string> monsterGods {
        eGod::sGodName(eGodType::artemis),
        eGod::sGodName(eGodType::hades),
        eGod::sGodName(eGodType::atlas),
        eGod::sGodName(eGodType::zeus),
        eGod::sGodName(eGodType::ares),
        "-",
        "-",
        eGod::sGodName(eGodType::aphrodite),
        eGod::sGodName(eGodType::athena),
        eGod::sGodName(eGodType::poseidon),
        eGod::sGodName(eGodType::dionysus),
        eGod::sGodName(eGodType::demeter),
        eGod::sGodName(eGodType::hermes),
        eGod::sGodName(eGodType::apollo),
        eGod::sGodName(eGodType::hera),
        eGod::sGodName(eGodType::hephaestus)
    };
    const std::vector<std::string> monsterHeroes {
        eHero::sHeroName(eHeroType::theseus),
        eHero::sHeroName(eHeroType::hercules),
        eHero::sHeroName(eHeroType::bellerophon),
        eHero::sHeroName(eHeroType::odysseus),
        eHero::sHeroName(eHeroType::jason),
        eHero::sHeroName(eHeroType::bellerophon),
        eHero::sHeroName(eHeroType::atalanta),
        eHero::sHeroName(eHeroType::achilles),
        eHero::sHeroName(eHeroType::hercules),
        eHero::sHeroName(eHeroType::perseus),
        eHero::sHeroName(eHeroType::achilles),
        eHero::sHeroName(eHeroType::perseus),
        eHero::sHeroName(eHeroType::theseus),
        eHero::sHeroName(eHeroType::odysseus),
        eHero::sHeroName(eHeroType::atalanta),
        eHero::sHeroName(eHeroType::jason)
    };

    const int iMax2 = allMonsters.size();
    for(int i = 0; i < iMax2; i++) {
        const auto m = allMonsters[i];
        if(withGodsOnly) {
            if(m == eMonsterType::echidna || m == eMonsterType::harpies) {
                continue;
            }
        }
        const auto& g = monsterGods[i];
        const auto& h = monsterHeroes[i];
        mnstrs.push_back(m);
        std::string str = eMonster::sMonsterName(m);
        if(showGodNames) {
            str = str + " (" + g + ", " + h + ")";
        } else {
            str = str + " (" + h + ")";
        }
        monsterStrs.push_back(str);
    }
}
