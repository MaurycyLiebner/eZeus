#include "eathena.h"

#include "textures/egametextures.h"

eApollo::eApollo(eGameBoard& board) :
    eExtendedGod(board, &eGodTextures::fApollo, eGodType::apollo) {
    eGameTextures::loadApollo();
}

eArtemis::eArtemis(eGameBoard& board) :
    eExtendedGod(board, &eGodTextures::fArtemis, eGodType::artemis) {
    eGameTextures::loadArtemis();
}

eAthena::eAthena(eGameBoard& board) :
    eExtendedGod(board, &eGodTextures::fAthena, eGodType::athena) {
    eGameTextures::loadAthena();
}

eAtlas::eAtlas(eGameBoard& board) :
    eExtendedGod(board, &eGodTextures::fAtlas, eGodType::atlas) {
    eGameTextures::loadAtlas();
}

eZeus::eZeus(eGameBoard& board) :
    eExtendedGod(board, &eGodTextures::fZeus, eGodType::zeus) {
    eGameTextures::loadZeus();
}
