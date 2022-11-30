#include "ecalydonianboar.h"

#include "textures/egametextures.h"

eCalydonianBoar::eCalydonianBoar(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fCalydonianBoar,
                  eMonsterType::calydonianBoar) {
    eGameTextures::loadCalydonianBoar();
}

eCerberus::eCerberus(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fCerberus,
                  eMonsterType::cerberus) {
    eGameTextures::loadCerberus();
}

eChimera::eChimera(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fChimera,
                  eMonsterType::chimera) {
    eGameTextures::loadChimera();
}

eCyclops::eCyclops(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fCyclops,
                  eMonsterType::cyclops) {
    eGameTextures::loadCyclops();
}

eDragon::eDragon(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fDragon,
                  eMonsterType::dragon) {
    eGameTextures::loadDragon();
}

eEchidna::eEchidna(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fEchidna,
                  eMonsterType::echidna) {
    eGameTextures::loadEchidna();
}

eHarpies::eHarpies(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fHarpies,
                  eMonsterType::harpies) {
    eGameTextures::loadHarpie();
}

eHector::eHector(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fHector,
                  eMonsterType::hector) {
    eGameTextures::loadHector();
}

eHydra::eHydra(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fHydra,
                  eMonsterType::hydra) {
    eGameTextures::loadHydra();
}

eKraken::eKraken(eGameBoard& board) :
    eWaterMonster(board, &eCharacterTextures::fKraken,
                  eMonsterType::kraken) {
    eGameTextures::loadKraken();
}

eMaenads::eMaenads(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fMaenads,
                  eMonsterType::maenads) {
    eGameTextures::loadMaenads();
}

eMedusa::eMedusa(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fMedusa,
                  eMonsterType::medusa) {
    eGameTextures::loadMedusa();
}

eMinotaur::eMinotaur(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fMinotaur,
                  eMonsterType::minotaur) {
    eGameTextures::loadMinotaur();
}

eScylla::eScylla(eGameBoard& board) :
    eWaterMonster(board, &eCharacterTextures::fScylla,
                  eMonsterType::scylla) {
    eGameTextures::loadScylla();
}

eSphinx::eSphinx(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fSphinx,
                  eMonsterType::sphinx) {
    eGameTextures::loadSphinx();
}

eTalos::eTalos(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fTalos,
                  eMonsterType::talos) {
    eGameTextures::loadTalos();
}
