#include "ecalydonianboar.h"

#include "textures/egametextures.h"

eCalydonianBoar::eCalydonianBoar(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fCalydonianBoar,
                  eMonsterType::calydonianBoar) {}

eCerberus::eCerberus(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fCerberus,
                  eMonsterType::cerberus) {}

eChimera::eChimera(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fChimera,
                  eMonsterType::chimera) {}

eCyclops::eCyclops(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fCyclops,
                  eMonsterType::cyclops) {}

eDragon::eDragon(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fDragon,
                  eMonsterType::dragon) {}

eEchidna::eEchidna(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fEchidna,
                  eMonsterType::echidna) {}

eHarpies::eHarpies(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fHarpies,
                  eMonsterType::harpies) {}

eHector::eHector(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fHector,
                  eMonsterType::hector) {}

eHydra::eHydra(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fHydra,
                  eMonsterType::hydra) {}

eKraken::eKraken(eGameBoard& board) :
    eWaterMonster(board, &eCharacterTextures::fKraken,
                  eMonsterType::kraken) {}

eMaenads::eMaenads(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fMaenads,
                  eMonsterType::maenads) {}

eMedusa::eMedusa(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fMedusa,
                  eMonsterType::medusa) {}

eMinotaur::eMinotaur(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fMinotaur,
                  eMonsterType::minotaur) {}

eScylla::eScylla(eGameBoard& board) :
    eWaterMonster(board, &eCharacterTextures::fScylla,
                  eMonsterType::scylla) {}

eSphinx::eSphinx(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fSphinx,
                  eMonsterType::sphinx) {}

eTalos::eTalos(eGameBoard& board) :
    eBasicMonster(board, &eCharacterTextures::fTalos,
                  eMonsterType::talos) {}
