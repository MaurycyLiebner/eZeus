#include "edemeter.h"

eAphrodite::eAphrodite(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fAphrodite, eGodType::aphrodite) {}

eAres::eAres(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fAres, eGodType::ares) {}

eDemeter::eDemeter(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fDemeter, eGodType::demeter) {}

eHades::eHades(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fHades, eGodType::hades) {}

eHephaestus::eHephaestus(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fHephaestus, eGodType::hephaestus) {}

eHera::eHera(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fHera, eGodType::hera) {}

eHermes::eHermes(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fHermes, eGodType::hermes) {}

ePoseidon::ePoseidon(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fPoseidon, eGodType::poseidon) {}
