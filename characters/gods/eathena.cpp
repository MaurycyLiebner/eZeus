#include "eathena.h"

eApollo::eApollo(eGameBoard& board) :
    eExtendedGod(board, &eGodTextures::fApollo, eGodType::apollo) {}

eArtemis::eArtemis(eGameBoard& board) :
    eExtendedGod(board, &eGodTextures::fArtemis, eGodType::artemis) {}

eAthena::eAthena(eGameBoard& board) :
    eExtendedGod(board, &eGodTextures::fAthena, eGodType::athena) {}

eAtlas::eAtlas(eGameBoard& board) :
    eExtendedGod(board, &eGodTextures::fAtlas, eGodType::atlas) {}

eZeus::eZeus(eGameBoard& board) :
    eExtendedGod(board, &eGodTextures::fZeus, eGodType::zeus) {}
