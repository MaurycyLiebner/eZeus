#include "edemeter.h"

#include "textures/egametextures.h"

eAphrodite::eAphrodite(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fAphrodite, eGodType::aphrodite) {
    eGameTextures::loadAphrodite();
}

eAres::eAres(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fAres, eGodType::ares) {
    eGameTextures::loadAres();
}

eDemeter::eDemeter(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fDemeter, eGodType::demeter) {
    eGameTextures::loadDemeter();
}

eHades::eHades(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fHades, eGodType::hades) {
    eGameTextures::loadHades();
}

eHephaestus::eHephaestus(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fHephaestus, eGodType::hephaestus) {
    eGameTextures::loadHephaestus();
}

eHera::eHera(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fHera, eGodType::hera) {
    eGameTextures::loadHera();
}

ePoseidon::ePoseidon(eGameBoard& board) :
    eBasicGod(board, &eGodTextures::fPoseidon, eGodType::poseidon) {
    eGameTextures::loadPoseidon();
}
