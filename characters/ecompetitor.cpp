#include "ecompetitor.h"

#include "textures/egametextures.h"

eCompetitor::eCompetitor(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fCompetitor,
                   eCharacterType::competitor) {
    eGameTextures::loadCompetitor();
    setProvide(eProvide::competitorCurator, 10000);
}
